#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Retorna os ponteiros início e fim da fila
void inicializar_fila(Fila *F)
{
    F->inicio = NULL;
    F->fim = NULL;
}

// Verifica se a fila está vazia, retornando 1 se estiver e 0 caso contrário
int fila_vazia(Fila *F)
{
    return (F->inicio == NULL);
}

// Insere um usuário na fila
void inserir_na_fila(Fila *F, char *nome_usuario, int *erro)
{
    // Aloca memória para um novo nó
    No_fila *novo = (No_fila *)malloc(sizeof(No_fila)); 
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o ponteiro
    novo->ponteiro_usuario = (usuario *)malloc(sizeof(usuario));
    if (novo->ponteiro_usuario == NULL)
    {
        *erro = 1;
        free(novo); // Caso a alocação falhe, retorna e o erro é atualizado
        return;
    }

    novo->ponteiro_usuario->nome = nome_usuario; // Ponteiro aponta para o nome do usuário
    novo->prox = NULL; // O próximo é NULL, pois sempre é inserido no fim

    if (fila_vazia(F)) // Se a fila estiver vazia, novo usuario é o primeiro
    {
        F->inicio = novo; 
    }
    else // Se não estiver vazia, é inserido no fim
    {
        F->fim->prox = novo; // Ajusta o ponteiro do "antigo" último elemento para apontar para o "novo" último elemento
    }

    F->fim = novo; // Faz "fim" apontar para o elemento inserido
    *erro = 0;
}

// Verifica se um nome está na fila, retornando 1 se estiver ou 0 caso contrário
int esta_na_fila(Fila *F, char *nome, int *erro)
{
    if (fila_vazia(F))
    {
        *erro = 1;
        return 0; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar 'ini'
    No_fila *aux = F->inicio;

    // Percorre a fila, comparando o nome fornecido com os nomes da fila
    while (aux != NULL)
    {
        if (strcmp(aux->ponteiro_usuario->nome, nome) == 0)
        {
            *erro = 0;
            return 1; // Se encontrar o nome, retorna 1 
        }
        aux = aux->prox; // Avança para o próximo nó
    }

    *erro = 0;
    return 0; // Se não encontrar, retorna 0 
}

// Função que retorna o nome do primeiro usuário da fila e apaga seu nó
char *remover_da_fila(Fila *F, int *erro)
{
    if (fila_vazia(F))
    {
        *erro = 1;
        return NULL; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Variável auxiliar para retornar o nome 
    char *nome;
    // Pega o nome do usuário
    nome = F->inicio->ponteiro_usuario->nome;

    // Ponteiro 'aux' para não modificar 'ini'
    No_fila *aux = F->inicio;
    // Atualiza o ínicio da fila
    F->inicio = aux->prox;

    if (F->inicio == NULL)
    {
        F->fim = NULL; // Se a fila ficar vazia, atualiza o fim
    }
    free(aux->ponteiro_usuario); // Libera o ponteiro
    free(aux); // Libera o nó

    *erro = 0; 
    return nome; // Retorna o nome do usuário
}

// Retorna o nome do primeiro usuário 
char *retorna_inicio_fila(Fila F, int *erro)
{
    if (fila_vazia(&F))
    {
        *erro = 1;
        return NULL; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    *erro = 0;
    return F.inicio->ponteiro_usuario->nome; // Retorna o nome do usuário
}

// Conta quantos usuários a fila possui
int tamanho_fila(Fila *F)
{
    // Ponteiro 'aux' para não modificar 'ini'
    No_fila *aux = F->inicio;
    // Variável contadora
    int tamanho = 0;

    // Percorre a lista
    while (aux != NULL)
    {
        tamanho++; // Itera o contador
        aux = aux->prox; // Avança para o próximo nó
    }

    return tamanho; // Retorna o tamanho da fila
}

// Copia todos os elementos da fila original para uma fila cópia
// (ambas passadas no parâmetro da função)
void copiar_fila(Fila *fila_origem, Fila *fila_destino, int *erro) {
    if (fila_vazia(fila_origem))
    {
        *erro = 1;
        return; // Se a fila original estiver vazia, retorna e o erro é atualizado
    }

    if (!fila_vazia(fila_destino))
    {
        *erro = 2;
        return; // Se a fila destino contém algum elemento, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não alterar 'ini'
    No_fila *no_aux = fila_origem->inicio;

    // Percorre a fila original e copia os elementos para a fila destino
    while (no_aux != NULL)
    {
        inserir_na_fila(fila_destino, no_aux->ponteiro_usuario->nome, erro);
        if (*erro)
        {
            *erro = 3;
            return; // Verifica se houve erro na alocação
        }
        no_aux = no_aux->prox;
    }
}

// Função que exclui todos os nós da fila
void excluir_fila(Fila *F, int *erro)
{
    if (fila_vazia(F))
    {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_fila *aux = F->inicio;
    No_fila *temp = NULL;

    while (aux != NULL)
    {
        temp = aux; // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        if (temp->ponteiro_usuario != NULL) 
        {
            free(temp->ponteiro_usuario);  // Libera o ponteiro (se necessário)
        }
        free(temp); // Libera o nó
    }

    // Ajusta os ponteiros
    F->inicio = NULL;
    F->fim = NULL;
    *erro = 0;
}