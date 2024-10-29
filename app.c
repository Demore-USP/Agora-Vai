#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "ListaProduto.h"
#include "ListaUsuario.h"
#include "PilhaLances.h"
#include "Fila.h"
#include "Lista.h"

// Todas essas funções estão explicadas junto à sua implementação, abaixo da main
void cadastrar_produto(Lista_produto *lista_produtos, int *qtd_produtos, int *erro);
void listar_produtos_lances(Lista_produto *lista_produtos, int *qtd_produtos, int *erro);
void dar_lance(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *erro);
void recomendar_produtos(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro);
void informacoes_leilao(Lista_produto *lista_produtos, int *qtd_produtos, int *erro);
void encerrar_leilao(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro);
void fechar_programa(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_produtos, int *erro);

int main()
{
    // Configurando a biblioteca que permite acentuação
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Declarando as listas que são utilizadas para armazenar tudo,
    // junto a algumas variáveis de controle / auxiliares
    Lista_produto lista_produtos;
    Lista_usuario lista_usuarios;
    int erro = 0, opcao = 0, qtd_produtos = 0, qtd_usuarios = 0;

    // Inicializando as listas
    inicializar_lista_produto(&lista_produtos);
    inicializar_lista_usuario(&lista_usuarios);

    // Loop que "roda o leilão"
    while (opcao != 7)
    {
        // Tela de opções do usuário
        printf("\n");
        printf("      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("      |          Caro usuário, suas opções são:      |\n");
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
        printf("~~~~~~~~~~~~~~~~~~~               ~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("| 5)  Informações |               | 6) Encerrar leilão |\n");
        printf("~~~~~~~~~~~~~~~~~~~               ~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("| 7)  Fechar programa |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            cadastrar_produto(&lista_produtos, &qtd_produtos, &erro);
        }
        else if (opcao == 2)
        {
            listar_produtos_lances(&lista_produtos, &qtd_produtos, &erro);
            if (erro)
                printf("Ops! Parece que houve um erro ao listar produtos e lances\n");
        }
        else if (opcao == 3)
        {
            dar_lance(&lista_produtos, &lista_usuarios, &qtd_usuarios, &erro); // a fila é feita e ela existe, n é problema em como cadastra a fila
        }
        else if (opcao == 4)
        {
            recomendar_produtos(&lista_produtos, &lista_usuarios, &qtd_usuarios, &qtd_produtos, &erro);
        }
        else if (opcao == 5)
        {
            informacoes_leilao(&lista_produtos, &qtd_produtos, &erro);
        }
        else if (opcao == 6)
        {
            encerrar_leilao(&lista_produtos, &lista_usuarios, &qtd_usuarios, &qtd_produtos, &erro);
            printf("Leilão encerrado!\n");
        }
        else if (opcao == 7)
        {
            fechar_programa(&lista_produtos, &lista_usuarios, &qtd_produtos, &erro);
            break;
        }
        else
        {
            printf("Opção inválida! Por favor, digite uma das opções disponíveis!\n");
        }
    }

    printf("Programa encerrado!");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cadastrar_produto(Lista_produto *lista_produtos, int *qtd_produtos, int *erro)
{
    // Variáveis auxilares
    char nome_produto[100];
    char resposta;
    char descricao[200] = "";
    printf("\n\n");
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);
    getchar();

    printf("\nDeseja inserir descrição? (s para sim, n para não): ");
    scanf("%c", &resposta);
    getchar();

    if (resposta == 's') // Se houver descrição
    {
        fgets(descricao, sizeof(descricao), stdin); // Lê até 199 caracteres (o último é reservado para '\0')

        // Remove o '\n' caso seja inserido no final da string
        descricao[strcspn(descricao, "\n")] = '\0';
        // Insere o produto e sua descrição na lista
        inserir_lista_produto(lista_produtos, nome_produto, descricao, erro);
    }
    else // Se não houver descrição
    {
        // Insere apenas o produto na lista (descrição passada como NULL)
        inserir_lista_produto(lista_produtos, nome_produto, NULL, erro);
    }

    // Tratamento de erros
    if (*erro == 1)
    {
        printf("\nErro ao alocar memória!\n");
        return;
    }
    if (*erro == 3)
    {
        printf("\nProduto já cadastrado anteriormente!\n");
        return;
    }

    // Produto cadastrado e contador iterado
    printf("\nProduto cadastrado com sucesso!");
    (*qtd_produtos)++;
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void dar_lance(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *erro)
{
    // Variáveis auxiliares
    char nome_usuario[100], nome_produto[100];
    float valor;

    printf("\n\n");
    printf("\nEntre com seu nome: ");
    scanf("%s", nome_usuario);
    printf("\nEntre com o valor do lance: R$ ");
    scanf("%f", &valor);
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);

    // Se o usuário não estiver na lista, itera o contador de usuários
    if (!esta_na_lista_usuario(lista_usuarios, nome_usuario))
        (*qtd_usuarios)++;

    // Insere o lance em questão
    inserir_lance_produto(lista_produtos, lista_usuarios, nome_usuario, &valor, nome_produto, erro);

    // Tratamento de erros
    if (*erro == 1)
    {
        printf("\nErro ao alocar memória!\n");
        return;
    }
    if (*erro == 4)
    {
        printf("\nSeu lance pelo(a) %s não foi aceito. Você precisa de um lance maior!\n", nome_produto);
        return;
    }
    if (*erro == 2)
    {
        printf("\nOps! parece que este produto não existe!\n");
        return;
    }

    // Lance concluído
    printf("\nLance dado com sucesso!");
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void listar_produtos_lances(Lista_produto *lista_produtos, int *qtd_produtos, int *erro)
{
    // Variáveis auxiliares
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

    if (*qtd_produtos == 0)
    {
        printf("\nSem produtos! Não gostaria de cadastrar um produto?\n");
    }

    // Para cada produto na lista de produtos
    for (int i = 0; i < *qtd_produtos; i++)
    {
        nome_produto = devolver_nome_produto(lista_produtos, i);          // Pega o nome do produto
        printf("%s: ", nome_produto);                                     // Printa o nome
        pilha_aux = pilha_especifica(lista_produtos, nome_produto, erro); // Pega a pilha de lances do produto
        if (pilha_vazia(pilha_aux))                                       // Se não houver lances
        {
            printf("nenhum lance para este produto!\n");
            continue; // Passa para o próximo produto
        }
        copiar_pilha(pilha_aux, &pilha_copia, erro); // Copia a pilha de lances
        while (!pilha_vazia(&pilha_copia))           // Percorre a pilha
        {
            valor = desempilhar(&pilha_copia, erro); // Pega o valor e mata o nó
            if (*erro)
            {
                free(nome_produto);
                excluir_pilha(&pilha_copia, erro);
                return; // Se der erro, sai da função
            }

            fila_aux = fila_especifica(pilha_aux, valor, erro); // Pega a fila de usuários que deram o lance
            copiar_fila(&fila_aux, &fila_copia, erro);          // Copia a fila de usuários
            excluir_fila(&fila_aux, erro);                      // Exclui a fila, deixando apenas a cópia
            num = tamanho_fila(&fila_copia);                    // Pega o tamanho da fila de usuários
            if (num > 1)                                        // se o tamanho da fila for maior que 1, printa no singular
                printf("%d lances de R$%.2f: ", num, valor);    // Printa os lances
            else
                printf("%d lance de R$%.2f: ", num, valor);
            for (int j = 0; j < num; j++) // Para cada usuário
            {
                if (j < num - 1)
                {
                    printf("%s, ", remover_da_fila(&fila_copia, erro)); // Printa o nome do usuário
                    if (*erro != 0)
                    {
                        // Libera o que não será mais usado
                        free(nome_produto);
                        excluir_fila(&fila_copia, erro);
                        excluir_pilha(&pilha_copia, erro);
                        return; // Retorna se houver erro ao remover da fila
                    }
                }
                else
                {
                    printf("%s\n", remover_da_fila(&fila_copia, erro)); // Printa o nome do usuário sem vírgula
                    if (*erro != 0)
                    {
                        // Libera o que não será mais usado
                        free(nome_produto);
                        excluir_fila(&fila_copia, erro);
                        excluir_pilha(&pilha_copia, erro);
                        return; // Retorna se houver erro ao remover da fila
                    }
                }
            }
        }
    }

    if (*erro)
        return;

    // Listagem concluída
    printf("\nListagem completa!");
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void recomendar_produtos(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro)
{
    // Variáveis auxiliares
    char *nome_usuario, *nome_produto1, *nome_produto2;
    int tam, flag1, flag2 = 0;
    Lista *lista_produtos_usuario = NULL;

    // Para cada usuário
    for (int i = 0; i < (*qtd_usuarios); i++)
    {
        nome_usuario = devolver_nome_usuario(lista_usuarios, i, erro); // Pega o nome do usuário
        // Pega a lista de produtos do usuário
        lista_produtos_usuario = devolver_lista_produtos(lista_usuarios, nome_usuario, erro);
        tam = tamanho_lista(lista_produtos_usuario); // Pega quantos produtos o usuário deu lance
        flag1 = 0;                                   // Ajusta a flag

        // Para cada produto deste usuário
        for (int j = 0; j < tam; j++)
        {
            nome_produto1 = devolver_produto(lista_produtos_usuario, j, erro); // Pega o nome do produto]
            // Verifica se o usuário é o vencedor deste produto
            if (!vencedor_produto(lista_produtos, nome_produto1, nome_usuario))
            {
                flag1 = 1;
                break;
            }
        }

        // Verificações para saber se o usuário tem algo a ser recomendado
        if (flag1 == 0 || tam == *qtd_produtos)
            continue;

        // Printa o nome do usuário
        printf("\nPara %s: não gostaria de dar um lance por:\n", nome_usuario);
        // Para cada produto que foi cadastrado
        for (int j = 0; j < (*qtd_produtos); j++)
        {
            nome_produto2 = devolver_nome_produto(lista_produtos, j); // Pega o nome do produto
            flag2 = 0;                                                // Ajusta a flag

            for (int k = 0; k < tam; k++) // Para cada produto que o usuário deu lance
            {
                // Pega o nome do produto que o usuário deu lance
                nome_produto1 = devolver_produto(lista_produtos_usuario, k, erro);
                if (strcmp(nome_produto1, nome_produto2) == 0) // Compara com o nome do produto cadastrado
                {
                    flag2 = 1;
                    break;
                }
            }
            // Verifica se o usuário não deu lance no produto
            if (flag2 == 0)
            {
                printf("- %s\n", nome_produto2); // Recomenda o produto
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Essa função dá instruções ao usuário
void informacoes_leilao(Lista_produto *lista_produtos, int *qtd_produtos, int *erro)
{
    char *nome_produto, *descricao_produto;
    printf("Bem vindo ao leilão! ");
    printf("Seguem as instruções a respeito de seu funcionamento:\n");
    printf("Você, como usuário, receberá abaixo os nomes dos produtos e, caso se interesse, poderá dar um lance nesse produto.\n");
    printf("Ao dar um lance, o usuário concorre ao produto escolhido. Outros usuários podem dar um lance de valor igual ou maior.\n");
    printf("Cada usuário pode dar quantos lances quiser. Ao fim, vence quem der o maior lance!\n");
    printf("Obs: Em caso de empate entre dois lances, o usuário vencedor será aquele que deu o lance primeiro.\n");

    if (lista_produtos_vazia(lista_produtos))
    {
        printf("Nenhum produto cadastrado até o momento\n");
        return;
    }

    printf("Produtos ofertados no leilão:\n");
    for (int i = 0; i < *qtd_produtos; i++)
    {
        nome_produto = devolver_nome_produto(lista_produtos, i);
        descricao_produto = devolver_descricao_produto(lista_produtos, i, erro);
        if (descricao_produto == NULL)
        {
            printf("- %s: sem descrição\n", nome_produto);
            continue;
        }
        printf("- %s: ", nome_produto);
        printf("%s\n", descricao_produto);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void encerrar_leilao(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_usuarios, int *qtd_produtos, int *erro)
{
    // Variáveis auxiliares
    char *nome_produto;
    char *vencedor;
    float valor;
    Pilha *pilha_aux;
    Fila fila_aux;

    // Para cada produto
    for (int i = 0; i < *qtd_produtos; i++)
    {
        nome_produto = devolver_nome_produto(lista_produtos, i);          // Pega o nome do produto
        printf("%s: ", nome_produto);                                     // Printa o produto
        pilha_aux = pilha_especifica(lista_produtos, nome_produto, erro); // Pega a pilha deste produto
        if (pilha_vazia(pilha_aux))                                       // Se não houver lances
        {
            printf("nenhum lance para este produto!\n");
            continue; // Avança para o próximo produto
        }

        valor = retorna_topo_pilha(pilha_aux, erro);        // Pega o maior lance
        fila_aux = fila_especifica(pilha_aux, valor, erro); // Pega a fila de usuários que deram este lance
        if (!fila_vazia(&fila_aux))
        {
            vencedor = retorna_inicio_fila(fila_aux, erro); // Pega o primeiro usuário que deu este lance
            excluir_fila(&fila_aux, erro);
            printf("%s comprou por R$%.2f\n", vencedor, valor); // Printa o usuário e o valor do seu lance
        }
    }

    excluir_lista_produto(lista_produtos, erro); // Exclui tudo
    excluir_lista_usuario(lista_usuarios, erro); // Exclui tudo
    *qtd_usuarios = 0;                           // Zera o contador de usuários
    *qtd_produtos = 0;                           // Zera o contador de produtos
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fechar_programa(Lista_produto *lista_produtos, Lista_usuario *lista_usuarios, int *qtd_produtos, int *erro)
{
    // Variáveis auxiliares
    char *nome_produto;
    Pilha *pilha_aux;
    Fila fila_aux;
    // Para cada produto
    for (int i = 0; i < *qtd_produtos; i++)
    {
        nome_produto = devolver_nome_produto(lista_produtos, i);          // Pega o nome do produto
        pilha_aux = pilha_especifica(lista_produtos, nome_produto, erro); // Pega a pilha de lances do produto
        if (pilha_vazia(pilha_aux))                                       // Se não houver lances
        {
            continue;
        }
        fila_aux = fila_especifica(pilha_aux, retorna_topo_pilha(pilha_aux, erro), erro); //
        excluir_fila(&fila_aux, erro);
    }
    excluir_lista_produto(lista_produtos, erro); // Exclui tudo
    excluir_lista_usuario(lista_usuarios, erro); // Exclui tudo
}
