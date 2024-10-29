#ifndef LISTAPRODUTO_H
#define LISTAPRODUTO_H

#include "PilhaLances.h"
#include "Fila.h"
#include "produto.h"
#include "ListaUsuario.h"

/* Struct que armazena o nome do produto (alocado dinamicamente), junto a sua descrição
e os produtos que ele deu lance (armazena ponteiros para esses produtos)*/ 
typedef struct no
{
    
    produto nome_produto; // Declaração da struct produto (contém o nome de fato e não um ponteiro)
    char *descricao; // String que armazena a descrição do produto
    Pilha lances; // Declaração da struct pilha (cada nó guarda um valor e uma fila
    // de ponteiros para os usuários que deram lances daquele valor)
    struct no *prox;
} No_ListaProduto;

// Ponteiros de início e fim da lista de produtos
typedef struct Lista_produto
{
    No_ListaProduto *ini;
    No_ListaProduto *fim;
} Lista_produto;

// Protótipos das funções utilizadas
void inicializar_lista_produto(Lista_produto *);
int lista_produtos_vazia(Lista_produto *);
void inserir_lista_produto(Lista_produto *, char *, char *, int *);
void inserir_lance_produto(Lista_produto *, Lista_usuario *, char *, float *, char *, int *);
char *devolver_nome_produto(Lista_produto *, int);
char *devolver_descricao_produto(Lista_produto *, int, int *);
Pilha *pilha_especifica(Lista_produto *, char *, int *);
int vencedor_produto(Lista_produto *, char *, char *);
void excluir_lista_produto(Lista_produto *, int *);

#endif