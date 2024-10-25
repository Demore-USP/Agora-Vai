#ifndef LISTAUSUARIO_H
#define LISTAUSUARIO_H

#include "ListaProduto.h"
#include "Lista.h"


// Struct que armazena o nome do usuario e os produtos em que ele deu lance 
typedef struct no_usuario {
    usuario nome_usuario;
    Lista produtos;
    struct no_usuario *prox;
} No_Usuario;


// Ponteiros de início e fim da lista geral
typedef struct Lista_usuario {
    No_Usuario *inicio;
    No_Usuario *fim;
} Lista_usuario;

void inicializar_lista_usuario(Lista_usuario *);
int esta_na_lista_usuario(Lista_usuario *, char *);
int lista_usuario_vazia(Lista_usuario *);
void inserir_lista_usuario(Lista_usuario *, char *, char*, int *);
char *devolver_nome_usuario(Lista_usuario *, int , int *);
Lista devolver_lista_produtos(Lista_usuario *, char *, int *);
void excluir_lista_usuario(Lista_usuario *, int *);

#endif