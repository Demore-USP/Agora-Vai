// Includes padrão
#include <stdio.h>
#include <stdlib.h>
#include "PilhaLances.h"

// Retorna o ponteiro topo da pilha
void inicializar_pilha(Pilha *P)
{
    P->topo = NULL;
}

// Verifica se a pilha está vazia, retornando 1 se estiver e 0 caso contrário
int pilha_vazia(Pilha *P)
{
    if (P->topo == NULL)
        return 1;
    return 0;
}

// Empilha um novo lance na pilha, associando-o a uma fila de usuários (caso fornecida)
void empilhar(Pilha *P, Fila *F, float valor, int *erro)
{
    No_Pilha *novo = (No_Pilha *)malloc(sizeof(No_Pilha)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // O novo lance aponta para o antigo topo, e o ponteiro 'topo'
    // passa a apontar para o novo lance
    novo->valor = valor;
    novo->prox = P->topo;
    inicializar_fila(&novo->fila_usuarios); // Inicializa a fila de usuários do novo lance

    if (!(F == NULL)) // Verifica se uma fila foi fornecida
    {
        copiar_fila(F, &novo->fila_usuarios, erro); // Copia a fila fornecida para o novo lance
        if (*erro != 0)
        {
            free(novo);
            return; // Retorna se houver erro ao copiar a fila
        }
    }

    P->topo = novo; // Atualiza o topo da pilha para o novo nó
    *erro = 0;
}

// Desempilha o lance no topo da pilha e retorna seu valor
float desempilhar(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return 0; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }

    // Buffer que retornará o valor
    float valor = P->topo->valor;
    // Variável auxiliar para apagar o nó
    No_Pilha *aux = P->topo;

    excluir_fila(&P->topo->fila_usuarios, erro); // Exclui a fila associada ao lance
    P->topo = P->topo->prox; // Ajustando o ponteiro

    free(aux); // Desalocando o nó
    *erro = 0; 
    return valor;
}

// Retorna o valor do topo da pilha sem removê-lo
float retorna_topo_pilha(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return 0; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }
    *erro = 0;
    return P->topo->valor; // Retorna o valor
}

// Copia todos os elementos da pilha original para uma pilha de cópia
// (ambas passadas no parâmetro da função)
void copiar_pilha(Pilha *PO, Pilha *PC, int *erro)
{
    // Declara e inicializa uma pilha temporária para auxiliar a cópia
    Pilha temp;
    inicializar_pilha(&temp); 

    if (pilha_vazia(PO))
    {
        *erro = 1;
        return; // Caso a pilha original esteja vazia, retorna e o erro é atualizado
    }

    // Variável auxiliar para percorrer a pilha original
    No_Pilha *aux = PO->topo;
    // Variável para armazenar o valor do lance
    float valor;

    // Copia os valores da pilha original para a pilha temporária
    while (aux != NULL)
    {
        valor = aux->valor;
        empilhar(&temp, &aux->fila_usuarios, valor, erro);
        aux = aux->prox;
    }

    aux = temp.topo; // Redefine 'aux' para copiar da temporária para a pilha de cópia

    // Copia da pilha temporária para a pilha de cópia, mantendo a ordem original
    while (aux != NULL)
    {
        valor = aux->valor;
        empilhar(PC, &aux->fila_usuarios, valor, erro);
        aux = aux->prox;
    }

    excluir_pilha(&temp, erro); // Libera a pilha temporária
    *erro = 0;
}

// Retorna a fila de usuários associada ao lance de valor específico na pilha
Fila fila_especifica(Pilha *P, float valor, int *erro)
{
    // Cria e inicializa uma fila e uma pilha auxiliares
    Pilha aux;
    Fila temp = {NULL, NULL};
    inicializar_fila(&temp); 
    inicializar_pilha(&aux);

    copiar_pilha(P, &aux, erro); // Copia a pilha principal para auxiliar
    if (*erro != 0)
    {
        excluir_pilha(&aux, erro);
        return temp; // Retorna fila vazia caso ocorra erro na cópia
    }

    // Percorre a pilha auxiliar para encontrar o lance com valor especificado
    while (!pilha_vazia(&aux))
    {
        if (valor == retorna_topo_pilha(&aux, erro)) // Se encontrar o lance especificado
        {
            copiar_fila(&aux.topo->fila_usuarios, &temp, erro); // Copia a fila de usuários
            if (*erro != 0)
            {
                excluir_pilha(&aux, erro); // Libera a pilha auxiliar em caso de erro
                return temp;
            }
            excluir_pilha(&aux, erro); // Libera a pilha auxiliar
            return temp; // Retorna a fila associada ao valor
        }
        desempilhar(&aux, erro); // Remove o topo da pilha auxiliar
        if (*erro != 0)
        {
            excluir_pilha(&aux, erro); // Libera a pilha auxiliar em caso de erro
            return temp;
        }
    }

    excluir_pilha(&aux, erro); // Libera a pilha auxiliar após a busca
    *erro = 1; // Define erro como 1, indicando que o valor não foi encontrado
    return temp; // Retorna fila vazia se o valor não for encontrado
}

// Exclui todos os elementos da pilha, liberando a memória utilizada
void excluir_pilha(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_Pilha *atual = P->topo;
    No_Pilha *temp = NULL;

    // Percorre a pilha e libera cada nó
    while (atual != NULL)
    {
        temp = atual; // Guarda o nó atual para liberar
        atual = atual->prox; // Avança para o próximo nó
        excluir_fila(&temp->fila_usuarios, erro); // Libera a fila associada ao nó
        free(temp); // Libera o nó
    }

    P->topo = NULL; // Ajusta o topo para NULL, indicando que a pilha está vazia
    *erro = 0;      
}