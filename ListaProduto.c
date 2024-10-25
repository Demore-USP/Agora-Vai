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

void inicializar_lista_produto(Lista_produto *L)
{
    L->ini = NULL;
    L->fim = NULL;
}

void inserir_lista_produto(Lista_produto *L, char *nome_produto, int *erro)
{
    No_ListaProduto *novo = (No_ListaProduto *)malloc(sizeof(No_ListaProduto)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do produto
    novo->nome_produto = (char *)malloc((strlen(nome_produto) + 1) * sizeof(char));
    if (novo->nome_produto == NULL)
    {
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
    }

    // Copia o nome do produto
    strcpy(novo->nome_produto, nome_produto);

    inicializar_pilha(&novo->lances); // Inicializa a pilha de lances

    novo->prox = NULL; // Seta o ponteiro para nulo, até encontrar a posição correta

    // Cria dois ponteiros auxiliares, para achar qual posição
    // o novo produto assumirá
    No_ListaProduto *ant = NULL;
    No_ListaProduto *aux = L->ini;

    // Percorre a lista até encontrar a posição correta de inserir o produto.
    // Quando a condição for quebrada, 'aux' apontará para o elemento à frente do novo produto,
    // e 'ant' apontará para o anterior
    while (aux != NULL && strcmp(aux->nome_produto, nome_produto) < 0)
    {
        ant = aux;
        aux = aux->prox;
    }

    // Verifica se o produto já existe
    if (aux != NULL && strcmp(aux->nome_produto, nome_produto) == 0)
    {
        *erro = 3;
        free(novo->nome_produto);
        free(novo);
        return;
    }

    // Se for o primeiro da lista
    if (ant == NULL)
    {
        novo->prox = L->ini;
        L->ini = novo; // Ajustando os ponteiros
    }
    else
    {
        ant->prox = novo;
        novo->prox = aux; // Ajustando os ponteiros
    }

    if (aux == NULL)
    { // Se for o último da lista
        L->fim = novo;
    }
    *erro = 0; // Seta o erro
}

void inserir_lance_produto(Lista_produto *LP, Lista_usuario *LU, char *nome_usuario, float *valor, char *nome_produto, int *erro)
{
    No_ListaProduto *aux = LP->ini;
    Lista temp;
    float topo;
    while (aux != NULL && (strcmp(aux->nome_produto, nome_produto)) != 0)
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        *erro = 2;
        return;
    }

    if (!esta_na_lista_usuario(LU, nome_usuario))
    { // se o usuario não esta na lista insere ele na lista e o produto na lista dele
        inserir_lista_usuario(LU, nome_usuario, nome_produto, erro);
    }

    else
    {
        temp = devolver_lista_produtos(LU, nome_usuario, erro); // se estiver, insere apenas o produto
        inserir_produto_no_usuario(&temp, nome_usuario, erro);
    }

    topo = retorna_topo_pilha(&aux->lances, erro);
    if (*valor < topo)
    {
        *erro = 4;
        return;
    }
    if (*valor == topo)
    {
        inserir_na_fila(&aux->lances.topo->fila_usuarios, nome_usuario, erro);
    }
    else
    {
        empilhar(&aux->lances, *valor, erro);
        inicializar_fila(&aux->lances.topo->fila_usuarios);
        inserir_na_fila(&aux->lances.topo->fila_usuarios, nome_usuario, erro);
    }

    *erro = 0;
    return;
}

char *devolver_nome_produto(Lista_produto *L, int indice, int *erro)
{
    No_ListaProduto *aux = L->ini;
    for (int i = 0; i < indice; i++)
    {
        aux = aux->prox;
    }

    return aux->nome_produto;
}

Pilha *pilha_especifica(Lista_produto *LP, char *nome_produto, int *erro)
{
    No_ListaProduto *aux = LP->ini;
    while (aux != NULL && (strcmp(aux->nome_produto, nome_produto)) != 0)
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        *erro = 2;
        return NULL;
    }
    return &aux->lances;
}

int vencedor_produto(Lista_produto *LP, char *nome_produto, char *nome_usuario)
{
    No_ListaProduto *aux = LP->ini;
    char **vencedor;

    while (aux != NULL && (strcmp(aux->nome_produto, nome_produto)) != 0)
    {
        aux = aux->prox;
    }

    vencedor = aux->lances.topo->fila_usuarios.inicio->ponteiro_usuario;

    if (nome_usuario == *vencedor)
    {
        return 1;
    }

    return 0;
}

void excluir_lista_produto(Lista_produto *L, int *erro)
{
    No_ListaProduto *aux = L->ini;
    No_ListaProduto *temp = NULL;

    while (aux != NULL)
    {
        temp = aux;      // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó

        // Se a pilha não estiver vazia, é excluída
        if (!pilha_vazia(&temp->lances))
            excluir_pilha(&temp->lances, erro);

        free(temp->nome_produto); // Libera o produto
        free(temp);               // Libera o nó atual
    }

    // Ajustando os ponteiros
    L->ini = NULL;
    L->fim = NULL;
    *erro = 0; // Setando o erro
}