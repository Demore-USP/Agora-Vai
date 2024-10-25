typedef struct {
    char *nome;
} usuario;

typedef struct no_fila {
    usuario *ponteiro_usuario;
    struct no_fila *prox;
} No_fila;

typedef struct Fila {
    No_fila *inicio;
    No_fila *fim;
} Fila;