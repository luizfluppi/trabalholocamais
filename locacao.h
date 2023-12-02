#ifndef LOCACAO_H_INCLUDED
#define LOCACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cliente.h"

struct tData {
    int dia;
    int mes;
    int ano;
};

struct tLocacao {
    int codigoLocacao;
    struct tData dataRetirada;
    struct tData dataDevolucao;
    int seguro;
    int dias;
    int codigoCliente;
    int codigoVeiculo;
};

typedef struct tCliente cliente;
typedef struct tLocacao locacao;

int buscarNomeCliente(char *nome, FILE *f){
    /*
    Função que determina se um cliente com deternimado nome existe no registro

    Parâmetros:
        FILE *f: O arquivo onde a busca será realizada
        char *nome: String contendo o nome do cliente a buscar

    Retorno:
        Caso seja encontrado o nome do cliente: 0
        Caso contrário: 1
    */
    cliente c;

    fseek(f,0,SEEK_SET);

    while (!feof(f)){
        fread(&c,sizeof(c),1,f);
        if (strcmp(nome,c.nome) == 0){
            return 0;
        }
    }

    return 1;
}

void cadastraLocacao(FILE *arqLocacao, FILE *arqClientes){
    /*
    Função que cadastra uma locação a partir de dados lidos do teclado

    Parâmetros:

    FILE *f: O arquivo onde será salvo o cadastro do cliente
    */

    char temp[50];

    locacao l;
    
    printf("Digite o nome do cliente:");
    fgets(temp,50,stdin);

    while (buscarNomeCliente(temp, ) )


}

#endif //LOCACAO_H_INCLUDED