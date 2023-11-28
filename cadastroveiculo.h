#ifndef CADASTROVEICULO_H_INCLUDED
#define CADASTROVEICULO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "veiculo.h"

typedef struct tVeiculo veiculo;

int gerarCodigoVeiculo(void){
    srand(time(0)); 
    int codigo;

    codigo = (rand() % 100000 );
    
    return codigo;
}

int buscarCodigoVeiculo(FILE *f, int codigo){
    veiculo v;

    fseek(f,0,SEEK_SET);

    while (!feof(f)){
        fread(&v,sizeof(v),1,f);

        if (v.codigo == codigo){
            return 1;
        }
    }

    return 0;
}

int buscarPeriodoVeiculo(FILE *f, char *dataretirada, char *datadevolucao){
    veiculo v;

    fseek(f,0,SEEK_SET);

    while (!feof(f)){
        fread(&v,sizeof(v),1,f);

        if (v.dataretirada == dataretirada && v.datadevolucao == datadevolucao){
            return 1;
        }
    }

    return 0;
}


void cadastrarCliente(FILE *f){
    setlocale(LC_ALL, "");
    char temp[30];
    
    veiculo v;

    printf("Digite a descrição do veículo: ");
    fgets(v.descricao,100,stdin);
    printf("Digite o modelo do veículo: ");
    fgets(v.modelo,50,stdin);
    printf("Digite a cor do veículo: ");
    fgets(v.cor,50,stdin);
    printf("Digite a placa do veículo: ");
    fgets(v.placa,15,stdin);
    printf("Digite a data de retirada do veículo: ");
    fgets(v.dataretirada,15,stdin);
    printf("Digite a data de devolução do veículo: ");
    fgets(v.datadevolucao,15,stdin);
    printf("Digite o status do veículo, tem que ser alugado, disponível ou em manutenção: ");
    fgets(v.status,50,stdin);
    printf("Digite o valor do veículo: ");
    fgets(temp,sizeof(temp),stdin);
    v.valor = atof(temp);
    printf("Digite o número de ocupantes do veículo: ");
    fgets(temp,sizeof(temp),stdin);
    v.ocupantes = atoi(temp);

    buscarPeriodoVeiculo(f, v.dataretirada, v.datadevolucao);
    
    v.codigo = gerarCodigoVeiculo();

    while (buscarCodigoVeiculo(f,v.codigo) != 0){ 
        v.codigo = gerarCodigoVeiculo();
    }

    fseek(f,0,SEEK_END);
    fwrite(&v,sizeof(v),1,f);
    fflush(f);

    printf("Veículo de código %i cadastrado com sucesso!",v.codigo);
}

#endif // CADASTROVEICULO_H_INCLUDED