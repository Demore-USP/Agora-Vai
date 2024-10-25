#ifndef LISTA_H
#define LISTA_H
typedef struct no_lista {
    char **nome_produto;
    struct no_lista *prox;
} No_Lista;
typedef struct {
    No_Lista *inicio;
    No_Lista *fim;
} Lista;
#endif