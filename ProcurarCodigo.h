
#ifndef PESQUISAPORCLIENTE_H_INCLUDED
#define PESQUISAPORCLIENTE_H_INCLUDED
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"

typedef struct tCliente cliente;
typedef struct tEndereco endereco;

void Localize_CodigoCliente(FILE *f){
    int codigo;
    cliente c;
    
    printf("Digite o codigo a seguir...\n");
    scanf("%d",&codigo);
    limparBuffer();
    fseek(f,0,SEEK_SET);
    //Loop para buscar codigo no arquivo
    while(fread(&c,sizeof(c),1,f) == 1)
    {
     //acho o codigo
        if (c.codigo == codigo)
        {
            printf("Codigo: %d\n",c.codigo);
            printf("Nome: %s\n",c.nome);
            printf("Telefone: %s\n",c.telefone);
            printf("Rua: %s\n",c.endereco.rua);
            printf("Numero de casa: %d\n",c.endereco.numero);
            printf("CEP: %d\n",c.endereco.cep);
        }
    }

}
/* Buscar e printar de acordo com o codigo da pessoa */


#endif // PESQUISAPORCLIENTE_H_INCLUDED
