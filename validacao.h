#ifndef VALIDACAO_H_INCLUDED
#define VALIDACAO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "estruturas.h"


void limparBuffer(){
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int temSoLetra(char *string){
    /*
        Verifica se uma string contém algum caractere que não faz parte
        do alfabeto padrão da língua portuguesa.

        PARÂMETROS:

        char *string: Ponteiro para a string a ser verificada

        RETORNOS:
        
        Caso a string contenha algum caractere não-alfabético: 1
        Caso contrário: 0
    */
    setlocale(LC_ALL,"pt_BR.utf8");
    
    for (int i = 0; string[i] != '\0' ; i = i+1){
        if ((isdigit(string[i]) != 0) || (ispunct(string[i]) != 0)){
            return 1;
        }
    }

    return 0;
}

int validaCodigoVeiculo(FILE *arqVeiculo, int codigo){
    /*
    
    */

    fseek(arqVeiculo,0,SEEK_SET);
    
    veiculo v;
    

    while (!feof(arqVeiculo)){
        fread(&v,sizeof(v),1,arqVeiculo);

        if (v.codigo == codigo){
            if (v.status == 'D'){
                return 1;
            }
            else {
                return -1;
            }
        }
    }

    return -1;
}

int validaNomeCliente(char *nome, FILE *arqClientes){
    /*
    Função que determina se um cliente com deternimado nome existe no registro

    Parâmetros:
        FILE *f: O arquivo onde a busca será realizada
        char *nome: String contendo o nome do cliente a buscar

    Retorno:
        Caso seja encontrado o nome do cliente: retorna o código do cliente
        Caso contrário: 1
    */
    setlocale(LC_ALL,"Portuguese");
    cliente c;

    fseek(arqClientes,0,SEEK_SET);

    while (!feof(arqClientes)){
        fread(&c,sizeof(c),1,arqClientes);
        if (strcmp(nome,c.nome) == 0){
            return c.codigo;
        }
    }

    return 1;
}

int validaCodigoCliente(FILE *arqClientes, int codigo){
    /*
    Função que determina se um cliente com determinado código existe no registro

    Parâmetros:
        FILE *arqClientes: O arquivo onde a busca será realizada
        int codigo: inteiro contendo o código do cliente a buscar

    Retorno:
        Caso seja encontrado um cliente com o código: 0
        Caso contrário: -1
    */
    cliente c;

    fseek(arqClientes,0,SEEK_SET);

    while (!feof(arqClientes)){
        fread(&c,sizeof(c),1,arqClientes);
        if (c.codigo == codigo){
            return 0;
        }
    }

    return -1;
}

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

#endif //VALIDACAO_H_INCLUDED