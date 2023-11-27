
//função main para teste
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cadastrocliente.h"

int main(){
    setlocale(LC_ALL,"Portuguese");

    FILE *clientes;

    clientes = fopen("clientes.dat","w+b");
    cadastrarCliente(clientes);
    

    return 0;
}