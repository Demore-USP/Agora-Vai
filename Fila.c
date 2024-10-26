#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que inicializa a fila
void inicializar_fila(Fila *F) {
    F->inicio = NULL;
    F->fim = NULL;
}

// Função que verifica se a fila está vazia
// (retorna 1 se estiver vazia ou 0 se não estiver)
int fila_vazia(Fila *F) {
    return (F->inicio == NULL);
}

void inserir_na_fila(Fila *F, usuario *nome_usuario, int *erro) {
    No_fila *novo = (No_fila *)malloc(sizeof(No_fila)); // Aloca memória para um novo Nó
    if (novo == NULL) {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    novo->ponteiro_usuario = nome_usuario; //o ponteiro para o nome do usuario aponta para o endereço do nome

    novo->prox = NULL; // Sempre aponta para NULL, pois sempre é inserido no fim

    if (fila_vazia(F)) {
        F->inicio = novo; // Se a fila estiver vazia, novo usuario é o primeiro
    } else {
        F->fim->prox = novo; // Ajusta o ponteiro do "antigo" último elemento para apontar para o "novo" último elemento
    }
    F->fim = novo; // 'fim' sempre apontará para o novo elemento inserido
    *erro = 0;
}

// Função que verifica se um nome está na fila
// (retorna 1 se estiver ou 0 se não estiver)
int esta_na_fila(Fila *F, char *nome, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return 0; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar 'ini'
    No_fila *aux = F->inicio;

    // Percorre toda a fila
    while (aux != NULL) {
        if (strcmp(aux->ponteiro_usuario->nome, nome) == 0) {
            *erro = 0;
            return 1; // Se encontrar o nome, retorna 1 (positivo)
        }
        aux = aux->prox;
    }

    *erro = 0;
    return 0; // Se não encontrar, retorna 0 (negativo)
}

// Função que remove o primeiro usuário da fila e devolve seu nome
char *remover_da_fila(Fila *F, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return NULL;
    }
    
    char *nome;
    nome = F->inicio->ponteiro_usuario->nome;
    

    // Ponteiro auxiliar pra não modificar 'ini'
    No_fila *aux = F->inicio;
    F->inicio = aux->prox;

    if (F->inicio == NULL) {
        F->fim = NULL; // Se a fila ficar vazia, atualiza o 'fim'
    }

    free(aux); // Libera o nó

    *erro = 0; // Setando o erro
    return nome;
}

char *retorna_inicio_fila(Fila F, int *erro) {
    if (fila_vazia(&F)) {
        *erro = 1;
        return NULL;
    }
    *erro = 0;
    return F.inicio->ponteiro_usuario->nome;
}

int tamanho_fila(Fila *F) {
    No_fila *aux = F->inicio;
    int tamanho = 0;
    while(aux != NULL) {
        tamanho++;
        aux = aux->prox;
    }
    return tamanho;
}

void copiar_fila(Fila *fila_origem, Fila *fila_destino, int *erro) {
    if (fila_vazia(fila_origem)) {
        *erro = 1;
        return; // Verifica se a fila original está vazia
    }

    if (!fila_vazia(fila_destino)) {
        *erro = 2;
        return; // Verifica se a fila de destino contém algum elemento
    }

    // Ponteiro auxiliar para não alterar 'ini'
    No_fila *no_aux = fila_origem->inicio;

    // Percorre a fila original e copia os elementos para a fila destino
    while (no_aux != NULL) {
        inserir_na_fila(fila_destino, no_aux->ponteiro_usuario, erro);
        if (*erro) {
            *erro = 3;
            return; // Verifica se houve erro na alocação 
        } 
        no_aux = no_aux->prox;
    }
}

// Função que exclui todos os nós da fila
void excluir_fila(Fila *F, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_fila *aux = F->inicio;
    No_fila *temp = NULL;

    while (aux != NULL) {
        temp = aux; // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp);      // Libera o nó
    }

    // Ajustando os ponteiros
    F->inicio = NULL;
    F->fim = NULL; 
    *erro = 0;
}

