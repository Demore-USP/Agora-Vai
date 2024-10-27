#include "ListaProduto.h"
#include "ListaUsuario.h"
#include "Fila.h"
#include "PilhaLances.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que inicializa a lista
void inicializar_lista_usuario(Lista_usuario *L)
{
    L->inicio = NULL;
    L->fim = NULL;
}

// Função que verifica se a lista está vazia
// (retorna 1 se está vazia ou 0 se não está)
int lista_usuario_vazia(Lista_usuario *L)
{
    return (L->inicio == NULL);
}

int esta_na_lista_usuario(Lista_usuario *L, char *nome_usuario)
{
    No_Usuario *aux = L->inicio;

    while (aux != NULL)
    {
        if (strcmp(aux->nome_usuario.nome, nome_usuario) == 0)
            return 1;
        aux = aux->prox;
    }

    return 0;
}

// FUNÇÃO ABAIXO PRECISA DE VERIFICAÇÃO NOS PARAMETROS
// Função que insere um novo usuário na lista de usuários
void inserir_lista_usuario(Lista_usuario *L, char *nome_usuario, char *nome_produto, int *erro)
{
    No_Usuario *novo = (No_Usuario *)malloc(sizeof(No_Usuario)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do usuario
    novo->nome_usuario.nome = nome_usuario;

    inicializar_lista(&novo->produtos); // Inicializa a lista de produtos para este usuário

    inserir_produto_no_usuario(&novo->produtos, nome_produto, erro); // Insere o endereço do nome do produto na lista de produtos deste novo usuario

    novo->prox = NULL; // Seta o ponteiro para nulo, até encontrar a posição correta

    // Verifica se a lista de usuários está vazia e insere como primeiro nó
    if (L->inicio == NULL)
    {
        L->inicio = novo;
    }
    else
    {
        L->fim->prox = novo; // Adiciona no final da lista
    }

    L->fim = novo; // Atualiza o ponteiro 'fim' da lista para o novo usuário
    *erro = 0;     // Define erro como 0 (sem erro)
}

No_Usuario *comparar_nomes(Lista_usuario *L, char *nome_usuario, int *erro) {
    No_Usuario *aux = L->inicio;
    while(aux != NULL && strcmp(aux->nome_usuario.nome, nome_usuario) != 0) {
        aux = aux->prox;
    }
    return aux;
}

char *devolver_nome_usuario(Lista_usuario *L, int indice, int *erro)
{
    No_Usuario *aux = L->inicio;
    int i = 0;
    while (i != indice && aux != NULL)
    {
        i++;
        aux = aux->prox;
    }
    if (aux != NULL)
    {
        *erro = 0;
        return aux->nome_usuario.nome;
    }
    *erro = 1;
    return NULL;
}

Lista devolver_lista_produtos(Lista_usuario *L, char *nome_usuario, int *erro)
{
    No_Usuario *aux = L->inicio;

    while (aux != NULL)
    {
        if (strcmp(aux->nome_usuario.nome, nome_usuario) == 0)
        {
            *erro = 0;
            return aux->produtos;
        }
    }

    *erro = 1;
    return aux->produtos;
}

void excluir_lista_usuario(Lista_usuario *L, int *erro)
{
    if (lista_usuario_vazia(L))
    {
        *erro = 1;
        return; // Caso a lista esteja vazia, atualiza o erro e retorna
    }

    // Ponteiros auxiliares
    No_Usuario *aux = L->inicio;
    No_Usuario *temp = NULL;

    // Percorre a lista e libera cada nó
    while (aux != NULL)
    {
        temp = aux; // Guarda o nó atual para liberar
        excluir_lista(&aux->produtos, erro);
        aux = aux->prox;               // Avança para o próximo nó
        free(temp->nome_usuario.nome); // Libera o nome
        free(temp);                    // Libera o nó atual
    }

    // Ajustando os ponteiros
    L->inicio = NULL;
    L->fim = NULL;
    *erro = 0; // Setando o erro
}