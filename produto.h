#ifndef PRODUTO_H
#define PRODUTO_H

/* Struct que guarda apenas o nome do produto:
usamos para poder abstrair a lógica e facilitar
o raciocínio / manutenção do código*/ 
typedef struct
{
    char *nome; // String
} produto;

#endif