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
    if (d.dia < 1){ //Só aceita dias positivos
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
    
    return 0;
}

int diferencaData(data d1, data d2){
    /*
        Função que determina a diferença, em dias, entre duas datas

        Parâmetros:
            data d1: estrutura do tipo data contendo a primeira data
            data d2: estrutura do tipo data contendo a segunda data 

        Retorno:
            Diferença em dias entre as duas datas:
                Se d1 > d2, será um número negativo
                Se d2 > d1, será um número positivo
                Se d1 = d2, será exatamente 0
    */
    
    int data1 = d1.dia + (d1.mes * 30) + (d1.ano * 365);
    int data2 = d2.dia + (d2.mes * 30) + (d2.ano * 365);

    int diferenca = data2 - data1;

    return diferenca;
}
int comparaData(data d1, data d2){
    /*
        Função que compara duas datas e determina qual delas é posterior em relação à outra

        Parâmetros:
            data d1: estrutura do tipo data contendo a primeira data a ser comparada
            data d2: estrutura do tipo data contendo a segunda data a ser comparada

        Retorno:
            Quando d1 é posterior a d2: 1
            Quando d2 é posterior a d1: 2
            Quando as datas são iguais: 0

    */

    if (d1.ano == d2.ano){
        if (d1.mes == d2.mes){
            if (d1.dia == d2.dia){
                return 0;
            }
            else if (d1.dia > d2.dia){
                return 1;
            }
            else {
                return 2;
            }
        }
        else if (d1.mes > d2.mes){
            return 1;
        }
        else {
            return 2;
        }
    }
    else if (d1.ano > d2.ano){
        return 1;
    }
    else {
        return 2;
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

    FILE *arqLocacao: O arquivo onde será salvo o cadastro da locação
    FILE *arqClientes: O arquivo onde se encontra o cadastro do cliente
    */

    int ocupantes = 0;
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
    
    while(validarData(l.dataRetirada) != 0){
        limparBuffer();
        printf("Data inválida! Verifique se a data foi digitada corretamente.\n");
        printf("Digite a data de retirada desejada (formato dd/mm/aaaa): ");
        scanf("%2i/%2i/%4i",&l.dataRetirada.dia,&l.dataRetirada.mes,&l.dataRetirada.ano);
    }
    limparBuffer();

    printf("Digite a data de devolução desejada (formato dd/mm/aaaa): ");

    scanf("%2i/%2i/%4i",&l.dataDevolucao.dia,&l.dataDevolucao.mes,&l.dataDevolucao.ano);
    while((validarData(l.dataDevolucao) != 0) || (comparaData(l.dataRetirada,l.dataDevolucao) != 2)){
        limparBuffer();
        printf("Data inválida! Verifique se a data foi digitada corretamente.\n");
        printf("Digite a data de retirada desejada (formato dd/mm/aaaa): ");
        scanf("%2i/%2i/%4i",&l.dataRetirada.dia,&l.dataRetirada.mes,&l.dataRetirada.ano);
    }
    limparBuffer();

    printf("Digite o número de ocupantes desejado: ");
    
    scanf("%i",&ocupantes);
    while (ocupantes < 1){
        limparBuffer();
        printf("Número de ocupantes inválido!\n");
        printf("Digite o número de ocupantes desejado: ");
        scanf("%i",&ocupantes);
    }
    limparBuffer();

    
}

#endif //LOCACAO_H_INCLUDED