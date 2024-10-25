#ifndef LISTAPRODUTO_H
#define LISTAPRODUTO_H

#include "pilhalances.h"
#include "fila.h"

// Struct que armazena o produto, com seus respectivos lances
typedef struct no_lista {
    char *produto;
    Pilha lances;
    struct no_lista *prox;
} No_ListaProduto;

// Ponteiros de início e fim da lista de produtos
typedef struct Lista {
    No_Lista *ini;
    No_Lista *fim;
} Lista_Produto;


#endif