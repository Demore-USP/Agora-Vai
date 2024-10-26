#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

void inicializar_lista(Lista *L) {
    L->inicio = NULL;
    L->fim = NULL;
}

int lista_vazia(Lista *L) {
    return (L->inicio == NULL);
}

void inserir_produto_no_usuario(Lista *L, char *nome_produto, int *erro) {

    No_Lista *novo = (No_Lista *)malloc(sizeof(No_Lista)); // Aloca memória para um novo Nó
    if (novo == NULL) {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }


    // Faz o ponteiro da lista de ponteiros para produtos apontar para o produto a ser inserido na lista de produtos do usuario
    novo->ponteiro_produto = &nome_produto;

    novo->prox = NULL; // Ajusta o ponteiro

    // Ponteiro auxiliar para não modificar 'ini'
    No_Lista *aux = L->inicio;

    // Compara o nome a inserir com os outros da lista
    // Caso a lista já tenha o nome, não insere e libera a memória
    while (aux != NULL) {
        if (aux->ponteiro_produto == &nome_produto) { 
            *erro = 3;  
            free(novo); 
            return;
        }
        aux = aux->prox; 
    }

    if (L->inicio == NULL) { // Se a lista estiver vazia, é o primeiro e o último
        L->inicio = novo;
        L->fim = novo; 
    } else { // Se não, adiciona ao final da lista
        L->fim->prox = novo;
        L->fim = novo; 
    }

    *erro = 0; // Setando o erro
}

int tamanho_lista(Lista *L) {
    int contador = 0;
    No_Lista *aux = L->inicio;

    while(aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}


char *devolver_produto(Lista *L, int indice, int *erro) {
    No_Lista *aux = L->inicio;
    char **nome;

    for(int i = 0; i < indice; i++) {
        aux = aux->prox;
    }
    nome = aux->ponteiro_produto;

    return *nome;
}

void excluir_lista(Lista *L, int *erro) {
    if(lista_vazia(L)) {
        *erro = 1;
        return;
    }
    
    // Ponteiros auxiliares
    No_Lista *aux = L->inicio;
    No_Lista *temp = NULL;

    // Percorre a lista e libera cada nó
    while (aux != NULL) {
        temp = aux; // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp); // Libera o nó atual
    }

    // Ajustando os ponteiros
    L->inicio = NULL;
    L->fim = NULL;
    *erro = 0; // Setando o erro
}