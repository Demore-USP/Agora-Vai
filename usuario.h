#ifndef USUARIO_H
#define USUARIO_H

/* Struct que guarda apenas o nome do usuário:
usamos para poder abstrair a lógica e facilitar
o raciocínio / manutenção do código*/ 
typedef struct
{
    char *nome; // String
} usuario;

#endif