#ifndef LISTA_H
#define LISTA_H

typedef struct no_lista {
    char **ponteiro_produto;
    struct no_lista *prox;
} No_Lista;

typedef struct {
    No_Lista *inicio;
    No_Lista *fim;
} Lista;

void inicializar_lista(Lista *);
int lista_vazia(Lista *);
void inserir_produto_no_usuario(Lista *, char *, int *);
int tamanho_lista(Lista *);
char *devolver_produto(Lista *, int, int *);
void excluir_lista(Lista *, int *);

#endif