#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

// Retorna os ponteiros início e fim da lista
void inicializar_lista(Lista *L)
{
    L->inicio = NULL;
    L->fim = NULL;
}

// Verifica se a lista de produtos está vazia, retornando 1 se estiver e 0 caso contrário
int lista_vazia(Lista *L)
{
    return (L->inicio == NULL);
}

// Insere um produto na lista de produtos que o usuário deu lance
void inserir_produto_no_usuario(Lista *L, char *nome_produto, int *erro)
{
    // Aloca memória para um novo nó
    No_Lista *novo = (No_Lista *)malloc(sizeof(No_Lista)); 
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o ponteiro
    novo->ponteiro_produto = (produto *)malloc(sizeof(produto));
    if (novo->ponteiro_produto == NULL)
    {
        *erro = 1;
        free(novo); // Libera 'novo' em caso de falha
        return;
    }

    // Faz o ponteiro apontar para o nome do produto
    novo->ponteiro_produto->nome = nome_produto;

    novo->prox = NULL; // Ajusta o próximo

    // Ponteiro auxiliar para não modificar 'ini'
    No_Lista *aux = L->inicio;

    // Verifica se o produto já está na lista; 
    // se estiver, não o insere
    while (aux != NULL)
    {
        if (strcmp(aux->ponteiro_produto->nome, nome_produto) == 0)
        {
            *erro = 3;
            free(novo->ponteiro_produto); // Libera o ponteiro
            free(novo); // Libera o nó
            return;
        }
        aux = aux->prox; // Avança para o próximo nó
    }

    if (L->inicio == NULL) // Se a lista estiver vazia, é o primeiro e o último
    { 
        L->inicio = novo;
        L->fim = novo;
    }
    else
    { // Se não, adiciona ao final da lista
        L->fim->prox = novo;
        L->fim = novo;
    }

    *erro = 0;
}

// Conta quantos produtos o usuário deu lance
int tamanho_lista(Lista *L)
{
    // Variáveis auxiliares
    int contador = 0;
    No_Lista *aux = L->inicio;

    // Percorre a lista
    while (aux != NULL)
    {
        contador++; // Itera o contador
        aux = aux->prox; // Avança para o próximo nó
    }

    return contador; // Retorna quantos produtos o usuário deu lance 
}

// Retorna o nome do produto pelo índice passado
char *devolver_produto(Lista *L, int indice, int *erro)
{
    // Ponteiro auxiliar para não modificar 'inicio'
    No_Lista *aux = L->inicio;

    // Percorre a lista até o índice 
    for (int i = 0; i < indice; i++)
    {
        aux = aux->prox; // Avança para o próximo nó
    }

    return aux->ponteiro_produto->nome; // Retorna o produto
}

// Exclui todos os nós da lista de produtos que o usuário deu lance
void excluir_lista(Lista *L, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1;
        return; // Se a lsita estiver vazia, atualiza o erro e retorna
    }

    // Ponteiros auxiliares
    No_Lista *aux = L->inicio;
    No_Lista *temp = NULL;

    // Percorre a lista e libera cada nó
    while (aux != NULL)
    {
        temp = aux; // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp->ponteiro_produto); // Libera o ponteiro
        free(temp); // Libera o nó atual
    }

    // Ajusta os ponteiros
    L->inicio = NULL;
    L->fim = NULL;
    *erro = 0; 
}