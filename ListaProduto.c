#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaProduto.h"
#include "produto.h"
#include "PilhaLances.h"
#include "ListaUsuario.h"
#include "usuario.h"
#include "Fila.h"
#include "Lista.h"

// Retorna os ponteiros início e fim da lista
void inicializar_lista_produto(Lista_produto *L)
{
    L->ini = NULL;
    L->fim = NULL;
}

// Verifica se a lista de produtos está vazia, retornando 1 se estiver e 0 caso contrário
int lista_produtos_vazia(Lista_produto *L) {
    return (L->ini == NULL);
}

// Insere um produto (e sua descrição) na lista de produtos,
// já em ordem alfabética pelo nome do produto
void inserir_lista_produto(Lista_produto *L, char *nome_produto, char *descricao, int *erro)
{
    // Aloca memória para um novo nó
    No_ListaProduto *novo = (No_ListaProduto *)malloc(sizeof(No_ListaProduto)); 
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do produto
    novo->nome_produto.nome = (char *)malloc((strlen(nome_produto) + 1) * sizeof(char));
    if (novo->nome_produto.nome == NULL)
    {
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
    }

    // Copia o nome do produto do buffer para seu campo definitivo
    strcpy(novo->nome_produto.nome, nome_produto);

    // Se a descrição foi fornecida 
    if (descricao != NULL)
    {
        // Aloca memória para a descrição
        novo->descricao = (char *)malloc((strlen(descricao) + 1) * sizeof(char));
        if (novo->descricao == NULL)
        {
            free(novo);
            *erro = 1;
            return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
        }
        // Copia a descrição do buffer para seu campo definitivo
        strcpy(novo->descricao, descricao);
    }

    else
    {
        novo->descricao = NULL; // Define a descrição como NULL se não for fornecida.
    }

    inicializar_pilha(&novo->lances); // Inicializa a pilha de lances do novo produto

    novo->prox = NULL; // Seta 'prox' para nulo, até encontrar a posição de inserção correta

    // Cria dois ponteiros auxiliares, para encontrar a posição do produto 
    No_ListaProduto *ant = NULL;
    No_ListaProduto *aux = L->ini;

    // Percorre a lista até encontrar a posição correta de inserir o produto;
    // Quando a condição for quebrada, 'aux' apontará para o elemento à frente do novo produto,
    // e 'ant' apontará para o anterior
    while (aux != NULL && strcmp(aux->nome_produto.nome, nome_produto) < 0)
    {
        ant = aux;
        aux = aux->prox; // Avança para o próximo nó
    }

    // Se o produto já existir na lista, libera memória e ajusta o erro
    if (aux != NULL && strcmp(aux->nome_produto.nome, nome_produto) == 0)
    {
        *erro = 3;
        free(novo->nome_produto.nome);
        free(novo);
        return;
    }

    if (ant == NULL) // Se for o primeiro da lista
    {
        novo->prox = L->ini;
        L->ini = novo; // Ajusta o ponteiro
    }
    else // Se estiver no meio da lista
    {
        ant->prox = novo;
        novo->prox = aux; // Ajusta os ponteiros
    }

    if (aux == NULL) // Se for o último da lista
    { 
        L->fim = novo; // Ajusta o ponteiro
    }

    *erro = 0; 
}

// Insere um lance para um produto específico (via nome)
void inserir_lance_produto(Lista_produto *LP, Lista_usuario *LU, char *nome_usuario, float *valor, char *nome_produto, int *erro)
{
    // Declarações de variáveis que auxiliam a inserção
    No_ListaProduto *aux = LP->ini;
    No_Usuario *aux2 = NULL;
    Lista *temp = NULL;
    float topo;
    char *nome;

    // Percorre a lista buscando o produto pelo nome
    while (aux != NULL && (strcmp(aux->nome_produto.nome, nome_produto)) != 0)
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        *erro = 2;
        return; // Se chegar ao fim e não encontrar o produto, ajusta o erro e retorna 
    }

    // Verifica se o usuário em questão está na lista, se não, insere;
    // O produto também é inserido em sua lista pessoal 
    if (!esta_na_lista_usuario(LU, nome_usuario))
    { 
        // Aloca memória para o nome do usuário
        nome = (char *)malloc((strlen(nome_usuario) + 1) * sizeof(char));
        if (nome == NULL)
        {
            *erro = 1;
            return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
        }
        // Copia o nome do buffer para o campo definitivo
        strcpy(nome, nome_usuario);
        // Insere o produto na lista do usuário em questão
        inserir_lista_usuario(LU, nome, aux->nome_produto.nome, erro);
    }
    else // Se o usuário já estiver na lista
    {
        // Pega a lista de produtos do usuário em questão
        temp = devolver_lista_produtos(LU, nome_usuario, erro); 
        // Insere o produto na lista
        inserir_produto_no_usuario(temp, aux->nome_produto.nome, erro);
    }

    // Pega o lance do topo da pilha
    topo = retorna_topo_pilha(&aux->lances, erro);
    if (*valor < topo)
    {
        *erro = 4;
        return; // Se o lance for menor que o topo, atualiza o erro e retorna
    }

    // Pega o nó do usuário
    aux2 = comparar_nomes(LU, nome_usuario, erro);

    if (*valor == topo)
    {
        // Se já existir um lance do valor em questão, insere o usuário na fila deste lance
        inserir_na_fila(&aux->lances.topo->fila_usuarios, aux2->nome_usuario.nome, erro); 
    }
    else
    {
        // Se o lance for maior que qualquer um existente, empilha o novo valor 
        empilhar(&aux->lances, NULL, *valor, erro); 
        // E insere o usuário na fila do lance em questão
        inserir_na_fila(&aux->lances.topo->fila_usuarios, aux2->nome_usuario.nome, erro);
    }

    *erro = 0;
    return;
}

// Retorna o nome do produto no índice especificado
char *devolver_nome_produto(Lista_produto *L, int indice)
{
    // Ponteiro 'aux' para não modificar 'ini'
    No_ListaProduto *aux = L->ini;

    // Percorre a lista até chegar no índice
    for (int i = 0; i < indice; i++)
    {
        aux = aux->prox; // Avança para o próximo nó
    }

    return aux->nome_produto.nome; // Retorna o nome do produto
}

// Retorna a descrição do produto no índice especificado
char *devolver_descricao_produto(Lista_produto *L, int indice, int *erro)
{
    // Ponteiro 'aux' para não modificar 'ini'
    No_ListaProduto *aux = L->ini;

    // Percorre a lista até chegar no índice
    for (int i = 0; i < indice; i++)
    {
        aux = aux->prox; // Avança para o próximo nó
    }

    return aux->descricao; // Retorna a descrição
}

// Retorna a pilha de lances de um produto específico (via nome)
Pilha *pilha_especifica(Lista_produto *LP, char *nome_produto, int *erro)
{
    // Ponteiro 'aux' para não modificar 'ini'
    No_ListaProduto *aux = LP->ini;

    // Percorre a lista comparando o nome fornecido com os nomes dos produtos
    while (aux != NULL && (strcmp(aux->nome_produto.nome, nome_produto)) != 0)
    {
        aux = aux->prox; // Avança para o próximo nó
    }
    if (aux == NULL)
    {
        *erro = 2;
        return NULL; // Produto não encontrado, retorna NULL
    }
    return &aux->lances; // Produto encontrado, retorna sua pilha de lances
}

// Verifica se o usuário foi o vencedor de um produto
// Retorna 1 se foi o vencedor e 0 caso contrário
int vencedor_produto(Lista_produto *LP, char *nome_produto, char *nome_usuario)
{
    // Ponteiro 'aux' para não modificar 'ini'
    No_ListaProduto *aux = LP->ini;

    // Variável auxiliar
    char *vencedor;

    // Percorre a lista comparando o nome fornecido com os nomes dos produtos
    while (aux != NULL && (strcmp(aux->nome_produto.nome, nome_produto)) != 0)
    {
        aux = aux->prox; // Avança para o próximo nó
    }

    // Recebe o nome do vencedor do produto 
    vencedor = aux->lances.topo->fila_usuarios.inicio->ponteiro_usuario->nome;

    // Compara com o nome fornecido na função
    if (strcmp(nome_usuario, vencedor) == 0)
    {
        return 1; // Se é o vencedor, retorna 1
    }

    return 0; // Se não é, retorna 0
}

// Exclui todos os nós da lista de produtos
void excluir_lista_produto(Lista_produto *L, int *erro)
{
    // Ponteiros auxiliares
    No_ListaProduto *aux = L->ini;
    No_ListaProduto *temp = NULL;

    // Percorre a lista
    while (aux != NULL)
    {
        temp = aux; // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó

        if (temp->descricao != NULL) 
            free(temp->descricao); // Desaloca a descrição do produto (se necessário)

        // Se a pilha não estiver vazia, é excluída
        if (!pilha_vazia(&temp->lances))
            excluir_pilha(&temp->lances, erro);

        free(temp->nome_produto.nome); // Libera o nome do produto
        free(temp); // Libera o nó atual
    }

    // Ajusta os ponteiros
    L->ini = NULL;
    L->fim = NULL;
    *erro = 0; 
}