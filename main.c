
//função main para teste
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "cadastrocliente.h"
#include "ProcurarCodigo.h"

int main(){
    setlocale(LC_ALL,"Portuguese");

    FILE *clientes;

    int opcao = 1;

    while (opcao != 0){
        printf("1) Cadastrar cliente\n");
        printf("2) Buscar cliente\n");
        printf("0) Sair\n");
        scanf("%i",&opcao);
        limparBuffer();

        switch (opcao){
            case 0:
                printf("Finalizando execução\n");
                break;
            case 1:
                clientes = fopen("clientes.dat","w+b");
                cadastrarCliente(clientes);
                fclose(clientes);
                break;
            case 2:
                clientes = fopen("clientes.dat","r+b");
                Localize_CodigoCliente(clientes);
                fclose(clientes);
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }
    
    return 0;
}