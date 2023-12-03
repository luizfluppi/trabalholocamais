#ifndef LOCACAO_H_INCLUDED
#define LOCACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "cliente.h"
#include "validacao.h"

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

typedef struct tData data;
typedef struct tCliente cliente;
typedef struct tLocacao locacao;

int validarData(data d){
    /*
    Função que valida uma data armazenada em uma estrutura do tipo tData

    Parâmetros:
        data d: a estrutura contendo a data a ser validada

    Retorno:
        Data inválida: -1
        Data válida: 0
    */
    time_t t = time(NULL);

    struct tm data;

    localtime_r(&t, &data);
    
    if (d.ano < data.tm_year){ //Só aceita anos iguais ou maiores ao ano atual
        return -1;
    }
    if (d.mes < 1 ){ //Só aceita meses positivos
        return -1;
    }
    if (d.mes != 2 ){ 
        if ((d.mes % 2 == 0) && (d.dia > 30)){ //Se o mês possuir 30 dias, o valor dia não pode ser mais do que 30
            return -1;
        }
        else if ((d.mes % 2 == 1) && (d.dia > 31)){ //Se o mês possuir 31 dias, o valor dia não pode ser mais do que 31
            return -1;
        }
    }
    else if (d.dia > 29){ //Se o mês for Fevereiro, o valor dia não pode ultrapassar 29
        return -1;
    }
    
}
int buscarNomeCliente(char *nome, FILE *f){
    /*
    Função que determina se um cliente com deternimado nome existe no registro

    Parâmetros:
        FILE *f: O arquivo onde a busca será realizada
        char *nome: String contendo o nome do cliente a buscar

    Retorno:
        Caso seja encontrado o nome do cliente: retorna o código do cliente
        Caso contrário: 1
    */
    cliente c;

    fseek(f,0,SEEK_SET);

    while (!feof(f)){
        fread(&c,sizeof(c),1,f);
        if (strcmp(nome,c.nome) == 0){
            return c.codigo;
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
    
    printf("Digite o nome do cliente: ");
    fgets(temp,50,stdin);

    while (buscarNomeCliente(temp, arqClientes) != 1){
        printf("Cliente não encontrado!\n");
        printf("Digite o nome do cliente:");
        fgets(temp,50,stdin);
    }

    l.codigoCliente = buscarNomeCliente(temp,arqClientes);

    printf("Digite a data de retirada desejada (formato dd/mm/aaaa): ");

    scanf("%2i/%2i/%4i",&l.dataRetirada.dia,&l.dataRetirada.mes,&l.dataRetirada.ano);
    
    while(){
        limparBuffer();
    }
    limparBuffer();



}

#endif //LOCACAO_H_INCLUDED