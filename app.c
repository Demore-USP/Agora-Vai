#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrar_produto(Lista_produto *lista_produtos, int *erro);
void dar_lance(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *erro);
void listar_produtos_lances(Lista_produto *lista_produtos, int *qtd_produtos, int *erro);

int main()
{

    Lista_produto lista_produtos;
    Lista_usuario lista_usuarios;
    int erro = 0, opcao = 0, qtd_produtos = 0;

    inicializar_lista_produto(&lista_produtos);
    inicializar_lista_usuario(&lista_usuarios);

    while (opcao != 6)
    {
        printf("\n");
        printf("Caro usuário, suas opcoes sao:\n");
        printf("1) Cadastrar um produto\n");
        printf("2) Listar produtos e lances\n");
        printf("3) Dar um lance\n");
        printf("4) Listar outros produtos disponiveis\n");
        printf("5) Remover produto\n");
        printf("6) Encerrar leilao\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            cadastrar_produto(&lista_produtos, &erro);
        }
        else if (opcao == 2)
        {
            listar_produtos_lances(&lista_produtos, &erro);
            if (erro)
                printf("Erro ao listar produtos e lances\n");
        }
        else if (opcao == 3)
        {
            dar_lance(&lista_produtos, &erro);
            
        }
        else if (opcao == 4)
        {

            listar_outros_produtos(&lista_produtos, &erro);
        }
        else if (opcao == 5)
        {

            remover_produto(&lista_produtos, &erro);
            
        }
        else if (opcao == 6)
        {
            encerrar_leilao(&lista_produtos, &erro);
        }
        else
        {
            printf("Opcao invalida! Digite uma das opcoes disponiveis\n");
        }
    }

    return 0;
}

void cadastrar_produto(Lista_produto *lista_produtos, int *qtd_produtos, int *erro) {
    char nome_produto[100];
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_lista_produto(lista_produtos, nome_produto, erro);

    if(*erro)
        return;

    printf("Produto cadastrado com sucesso!");
    (*qtd_produtos)++;
    return;
}

void dar_lance(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *erro) {
    char nome_usuario[100], nome_produto[100];
    float valor;

    printf("\nEntre com seu nome: ");
    scanf("%s", nome_usuario);
    printf("\nEntre com o valor do lance: R$ ");
    scanf("%f", &valor);
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_lance_produto(lista_produtos, lista_usuarios, nome_usuario, &valor, nome_produto, erro);

    if(*erro)   
        //tratar erro
        return;
    
    printf("Lance dado com sucesso!");
    return;
}

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

    for(int i=0; i<qtd_produtos; i++){
        nome_produto = devolver_nome_produto(lista_produtos, i, erro);
        printf("%s", nome_produto);
        pilha_aux = pilha_especifica(lista_produtos, nome_produto, erro);
        if(pilha_vazia(pilha_aux)) {
            printf("Nenhum lance foi dado para esse produto\n");
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
            copiar_fila(fila_especifica(pilha_copia, valor, erro), &fila_copia, erro);
            num = tamanho_fila(fila_copia, erro);
            printf("%d lances de R$%.2f: ", num, valor);
            for(int j = 0; j < num; j++) {
                if(j < num-1)
                    printf("%s, ", remover_fila(&fila_copia, erro));
                    if (*erro != 0)
                        {
                            free(nome_produto);
                            excluir_fila(&fila_copia, erro);
                            excluir_pilha(&pilha_copia, erro);
                            return; // Retorna se houver erro ao remover da fila
                        }
                else 
                    printf("%s\n", remover_fila(&fila_copia, erro));
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