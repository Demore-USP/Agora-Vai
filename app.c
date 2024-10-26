#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "ListaProduto.h"
#include "ListaUsuario.h"
#include "PilhaLances.h"
#include "Fila.h"
#include "Lista.h"

// Erros:
// 1- Erro ao alocar memória
// 2- Produto não existente
// 3- Produto já existente
// 4- Lance não válido

// Todas essas funções estão explicadas junto à sua implementação
void cadastrar_produto(Lista_produto *lista_produtos, int *qtd_produtos, int *erro);
void listar_produtos_lances(Lista_produto *lista_produtos, int *qtd_produtos, int *erro);
void dar_lance(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *erro);
void recomendar_produtos(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro);
void encerrar_leilao(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro);

int main() {
    // Configurando a biblioteca que permite acentuação
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Declarando as listas que são utilizadas para armazenar tudo 
    Lista_produto lista_produtos;
    Lista_usuario lista_usuarios;
    int erro = 0, opcao = 0, qtd_produtos = 0, qtd_usuarios = 0;

    // Inicializando as listas
    inicializar_lista_produto(&lista_produtos);
    inicializar_lista_usuario(&lista_usuarios);

    // Loop que "roda o leilão"
    while (opcao != 6) {
        // Tela de opções do usuário
        printf("\n");
        printf("      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("      |        Caro usuário, suas opções são:        |\n");
        printf("      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("| 1) Cadastrar um produto |       | 2) Listar produtos e lances |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("| 3) Dar um lance |               | 4) Receber recomendações de produtos |\n");
        printf("~~~~~~~~~~~~~~~~~~~               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~            ~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("| 5) Remover produto |            | 6) Encerrar leilão |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~            ~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);


        if (opcao == 1) {
            cadastrar_produto(&lista_produtos, &qtd_produtos, &erro);

        } else if (opcao == 2) {
            listar_produtos_lances(&lista_produtos, &qtd_produtos, &erro);
            if (erro)
                printf("Ops! Parece que houve um erro ao listar produtos e lances\n");

        } else if (opcao == 3) {
            dar_lance(&lista_produtos, &lista_usuarios, &qtd_usuarios, &erro);
            
        } else if (opcao == 4) {
            recomendar_produtos(&lista_produtos, &lista_usuarios, &qtd_usuarios, &qtd_produtos, &erro);

        } else if (opcao == 5) {
            
            
        } else if (opcao == 6) {
            encerrar_leilao(&lista_produtos, &lista_usuarios, &qtd_usuarios, &qtd_produtos, &erro);
            break;

        } else {
            printf("Opção inválida! Por favor, digite uma das opções disponíveis!\n");
        }
    }

    printf("Leilão encerrado!");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cadastrar_produto(Lista_produto *lista_produtos, int *qtd_produtos, int *erro) {
    char nome_produto[100];
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_lista_produto(lista_produtos, nome_produto, erro);

    if(*erro) {
        printf("Produto já cadastrado anteriormente!\n");
        return;
    }
    printf("Produto cadastrado com sucesso!");
    (*qtd_produtos)++;
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dar_lance(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *erro) {
    char nome_usuario[100], nome_produto[100];
    float valor;

    printf("\nEntre com seu nome: ");
    scanf("%s", nome_usuario);
    printf("\nEntre com o valor do lance: R$ ");
    scanf("%f", &valor);
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_lance_produto(lista_produtos, lista_usuarios, nome_usuario, &valor, nome_produto, erro);

    if(*erro==4) { 
        printf("Seu lance pelo(a) %s não foi aceito. Você precisa de um lance maior!", nome_produto);
        return;
    }
    if(!esta_na_lista_usuario(lista_usuarios, nome_usuario)) 
        (*qtd_usuarios)++;
    if(*erro == 2) {
        printf("Ops! parece que este produto não existe!\n");
        return;
    }
    printf("Lance dado com sucesso!");
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void listar_produtos_lances(Lista_produto *lista_produtos, int *qtd_produtos, int *erro) {
    // Declarações
    char *nome_produto;
    float valor;
    int num;

    // Declarando e inicializando cópias de pilha e fila,
    // pois vamos destruí-las (não queremos mudar a original)
    Pilha pilha_copia;
    inicializar_pilha(&pilha_copia);
    Fila fila_copia;
    inicializar_fila(&fila_copia);
    Pilha *pilha_aux;
    Fila fila_aux;

    for(int i=0; i<*qtd_produtos; i++){
        nome_produto = devolver_nome_produto(lista_produtos, i, erro);
        printf("%s", nome_produto);
        pilha_aux = pilha_especifica(lista_produtos, nome_produto, erro);
        if(pilha_vazia(pilha_aux)) {
            printf("Nenhum lance para este produto!\n");
            continue;
        }
        copiar_pilha(pilha_aux, &pilha_copia, erro);
        while(!pilha_vazia(&pilha_copia)) {
            valor = desempilhar(&pilha_copia, erro);
            if(*erro) {
                free(nome_produto);
                excluir_pilha(&pilha_copia, erro);
                return;
            }
            fila_aux = fila_especifica(pilha_aux, valor, erro);
            copiar_fila(&fila_aux, &fila_copia, erro);
            num = tamanho_fila(&fila_copia);
            printf("%d lances de R$%.2f: ", num, valor);
            for(int j = 0; j < num; j++) {
                if(j < num-1)
                    printf("%s, ", remover_da_fila(&fila_copia, erro));
                    if (*erro != 0)
                        {
                            free(nome_produto);
                            excluir_fila(&fila_copia, erro);
                            excluir_pilha(&pilha_copia, erro);
                            return; // Retorna se houver erro ao remover da fila
                        }
                else 
                    printf("%s\n", remover_da_fila(&fila_copia, erro));
                    if (*erro != 0)
                        {
                            free(nome_produto);
                            excluir_fila(&fila_copia, erro);
                            excluir_pilha(&pilha_copia, erro);
                            return; // Retorna se houver erro ao remover da fila
                        }
            }
        }
    }

    if(*erro)
        return;

    printf("Listagem completa!\n");
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void recomendar_produtos(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro) {
    char *nome_usuario, **nome_produto1, *nome_produto2;
    int tam, flag1, flag2 = 0;
    Lista lista_produtos_usuario;
    inicializar_lista(&lista_produtos_usuario);

    for(int i = 0; i < (*qtd_usuarios); i++) {
        nome_usuario = devolver_nome_usuario(lista_usuarios, i, erro);
        lista_produtos_usuario = devolver_lista_produtos(lista_usuarios, nome_usuario, erro);
        tam = tamanho_lista(&lista_produtos_usuario);
        flag1 = 0;

        for(int j = 0; j < tam; j++) {
            *nome_produto1 = devolver_produto(&lista_produtos_usuario, j, erro); // Devolver a string de fato, derreferenciado
            if(vencedor_produto(lista_produtos, *nome_produto1, nome_usuario)) 
                continue;
            else {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0)
            continue;
        printf("Para %s: não gostaria de dar um lance por:\n", nome_usuario);
        for(int j = 0; j < (*qtd_produtos); j++) {
            nome_produto2 = devolver_nome_produto(lista_produtos, j, erro);
            flag2 = 0;

            for(int k = 0; k < tam; k++) {
                *nome_produto1 = devolver_produto(&lista_produtos_usuario, k, erro);
                if(strcmp(*nome_produto1, nome_produto2) == 0) {
                    flag2 = 1;
                    break;
                }
            }
            if (flag2 == 0) {
                printf("- %s\n", nome_produto2);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void encerrar_leilao(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro){
    char *nome_produto;
    char *vencedor;
    float valor;
    Pilha *pilha_aux;
    inicializar_pilha(pilha_aux);

    Fila fila_aux;
    inicializar_fila(&fila_aux);

    for(int i = 0; i < qtd_produtos; i++) {
        nome_produto = devolver_nome_produto(lista_produtos, i, erro);
        printf("%s: ", nome_produto);
        pilha_aux = pilha_especifica(lista_produtos, nome_produto, erro);
        valor = retorna_topo_pilha(pilha_aux, erro);
        fila_aux = fila_especifica(pilha_aux, valor, erro);
        vencedor = retorna_inicio_fila(fila_aux, erro);
        printf("%s comprou por R$%.2f\n", vencedor, valor);
    }

    excluir_lista_produto(lista_produtos, erro);
    excluir_lista_usuario(lista_usuarios, erro);
}