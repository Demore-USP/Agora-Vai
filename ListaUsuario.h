#ifndef LISTA_USUARIO_H
#define LISTA_USUARIO_H

// Struct que armazena os nomes de todos 
typedef struct no_usuario {
    char *nome;
    struct no_usuario *prox;
} No_usuario;

// Ponteiros de início e fim da lista geral
typedef struct Lista_usuario {
    No *ini;
    No *fim;
} Lista_usuario;

void inicializar_lista_usuario(Lista_usuario *);
int lista_simples_usuario(Lista_usuario *);
void inserir_lista_usuario(Lista_usuario *, char *, int *);
void excluir_lista_usuario(Lista_usuario *, int *);

#endif