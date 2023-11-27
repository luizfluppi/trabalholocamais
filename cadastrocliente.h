#ifndef CADASTROCLIENTE_H_INCLUDED
#define CADASTROCLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"

typedef struct tCliente cliente;

int gerarCodigoCliente(void){
    /*
    Função que gera e retorna um código de cliente aleatório entre 0 e 99999
    */
    srand(time(0)); 
    int codigo;

    codigo = (rand() % 100000 );
    
    return codigo;
}

int buscarCodigoCliente(FILE *f, int codigo){
    /*
    Função que verifica se um código de cliente já existe em um arquivo
    
    Se o código for encontrado no arquivo, retorna 1
    Caso contrário, retorna 0

    Parâmetros:
    FILE *f: O arquivo onde o código será procurado
    int codigo: O código de cliente que será procurado

    */

    cliente c;

    fseek(f,0,SEEK_SET);

    while (!feof(f)){
        fread(&c,sizeof(c),1,f);

        if (c.codigo == codigo){
            return 1;
        }
    }

    return 0;
}
void cadastrarCliente(FILE *f){
    /*
    Função que cadastra um cliente a partir de dados lidos do teclado

    Parâmetros:
    FILE *f: O arquivo onde será salvo o cadastro do cliente

    */

    char temp[30]; 
    
    cliente c;

    printf("Digite o nome do cliente: ");
    fgets(c.nome,50,stdin);
    printf("Digite o número de telefone do cliente: ");
    fgets(c.telefone,12,stdin);
    printf("Digite o endereço do cliente:\n");
    printf("Rua: ");
    fgets(c.endereco.rua,50,stdin);
    printf("Número: ");
    fgets(temp,sizeof(temp),stdin);
    c.endereco.numero = atoi(temp);
    printf("CEP: ");
    fgets(temp,sizeof(temp),stdin);
    c.endereco.cep = atoi(temp);
    
    c.codigo = gerarCodigoCliente();
    
    //Verifica se o código gerado já existe no arquivo
    //Caso exista, gera outro código e verifica novamente
    while (buscarCodigoCliente(f,c.codigo) != 0){ 
        c.codigo = gerarCodigoCliente();
    }

    //Adiciona os dados do cliente ao fim do arquivo
    fseek(f,0,SEEK_END);
    fwrite(&c,sizeof(c),1,f);
    fflush(f);

    printf("Cliente de código %i cadastrado com sucesso!",c.codigo);
}

#endif // CADASTROCLIENTE_H_INCLUDED