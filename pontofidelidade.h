#ifndef PONTOFIDELIDADE_H_INCLUDED
#define PONTOFIDELIDADE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "cliente.h"

typedef struct tCliente cliente;

int numclientes = 0;

void adicionarPontosFidelidade(char *nomecliente) {
    cliente c;

    if (strcmp(c.nome, nomecliente) == 0) {
        c.pontosfidelidade += 10;
    }

}

void kitLocamais() {
    cliente c;

    if (c.pontosfidelidade  >= 500) {
        strcpy(c.kitLocaMais,"SIM");
    } else {
        strcpy(c.kitLocaMais,"NAO");
    }

}

#endif // PONTOFIDELIDADE_H_INCLUDED