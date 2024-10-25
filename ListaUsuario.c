#include "ListaProduto.h"
#include "ListaUsuario.h"
#include "fila.h"
#include "PilhaLances.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função que inicializa a lista
void inicializar_lista_usuario(Lista_usuario *L){
    L->inicio = NULL;
    L->fim = NULL;
}

// Função que verifica se a lista está vazia
// (retorna 1 se está vazia ou 0 se não está)
int lista_vazia(Lista_usuario *L) {
    return (L->inicio == NULL);
}


int lista_simples_usuario(Lista_usuario *L){

}

// FUNÇÃO ABAIXO PRECISA DE VERIFICAÇÃO NOS PARAMETROS
// Função que insere um novo usuário na lista de usuários
void inserir_lista_usuario(Lista_usuario *L, char *nome_usuario, char *nome_produto, int *erro){
    No_Usuario *novo = (No_Usuario *)malloc(sizeof(No_Usuario)); // Aloca memória para um novo Nó
    if (novo == NULL) {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do produto
    novo->nome_usuario.nome = (char *)malloc((strlen(nome_usuario) + 1) * sizeof(char));
    if (novo->nome_usuario.nome == NULL) {
        free(novo);
        *erro = 2;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
    }

    // Copia o nome do produto 
    strcpy(novo->nome_usuario.nome, nome_usuario);

    inicializar_lista(&novo->produtos); // Inicializa a lista de produtos para este usuário
    //inserir_produto_no_usuario()  //insere o nome_produto na lista de produtos deste novo usuario


    novo->prox = NULL; // Seta o ponteiro para nulo, até encontrar a posição correta

    // Verifica se a lista de usuários está vazia e insere como primeiro nó
    if (L->inicio == NULL) {
        L->inicio = novo;
    } else {
        L->fim->prox = novo; // Adiciona no final da lista
    }

    L->fim = novo; // Atualiza o ponteiro 'fim' da lista para o novo usuário
    *erro = 0; // Define erro como 0 (sem erro)
}



void excluir_lista_usuario(Lista_usuario *L, int *erro){
    
    
}

