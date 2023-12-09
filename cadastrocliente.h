#ifndef CADASTROCLIENTE_H_INCLUDED
#define CADASTROCLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"
#include "validacao.h"

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

    char temp[9]; 
    
    cliente c;

    printf("Digite o nome do cliente: ");
    scanf("%s",&c.nome);
    
    while (temSoLetra(c.nome) != 0){
        limparBuffer();
        printf("Nome inválido! O nome não pode ter mais de 50 caracteres nem conter caracteres não-alfabéticos.\n");
        printf("Digite o nome do cliente: ");
        scanf("%s",&c.nome);
    }

    limparBuffer();

    printf("Digite o número de telefone do cliente: ");
    scanf("%s",&c.telefone);
    limparBuffer();
    
    while ((atoi(c.telefone) == 0) || (strlen(c.telefone) < 11)){
        printf("Número inválido! Digite um número com DDD, sem símbolos ou espaços.\n");
        printf("Digite o número de telefone do cliente: ");
        scanf("%s",&c.telefone);
        limparBuffer();
    }

    printf("Digite o endereço do cliente:\n");

    printf("Rua: ");
    fgets(c.endereco.rua,sizeof(c.endereco.rua),stdin);

    printf("Número: ");
    fgets(temp,sizeof(temp),stdin);

    while (atoi(temp) == 0){
        printf("Número inválido! Digite apenas caracteres numéricos.\n");
        printf("Número: ");
        fgets(temp,sizeof(temp),stdin);
    }
    c.endereco.numero = atoi(temp);

    printf("CEP: ");
    fgets(temp,9,stdin);

    while ((atoi(temp) == 0)){
        printf("CEP inválido! Digite um CEP de 8 dígitos, sem hífen.\n");
        printf("CEP: ");
        fgets(temp,9,stdin);
    }
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

    printf("\nCliente de código %i cadastrado com sucesso!\n\n",c.codigo);
}

#endif // CADASTROCLIENTE_H_INCLUDED