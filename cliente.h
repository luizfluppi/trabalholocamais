#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "validacao.h"
#include "estruturas.h"

typedef struct tCliente cliente;

int gerarCodigoCliente(void){
    /*
    Função que gera e retorna um código de cliente aleatório entre 0 e 99999
    */
    int codigo;

    codigo = (rand() % 100000 );
    
    return codigo;
}

void buscarCodigoCliente(FILE *f){
    /*
    Descricao: O procedimento tem como objetivo de achar o cliente e
     verificar se deu positiva na locadora ou não, com alguns do 
     seus dados.
    Entrada:
     Parametros:
       int Codigo: O codigo que quer ser procurado;
       Saida:
        Informações do struct do cliente e do endereço;
        Error:
        Escrever Codigo não encontrado.
    */
    int codigo;
    int resultados = 0;
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
            resultados++;
            printf("Codigo: %d\n",c.codigo);
            printf("Nome: %s\n",c.nome);
            printf("Telefone: %s\n",c.telefone);
            printf("Rua: %s\n",c.endereco.rua);
            printf("Numero de casa: %d\n",c.endereco.numero);
            printf("CEP: %s\n",c.endereco.cep);
        }
    }
    if (resultados < 1){
        printf("Codigo nao encontrado\n");
    }

}
/* Buscar e printar de acordo com o codigo da pessoa */


int validarCodigoCliente(FILE *f, int codigo){
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
    
    char temp[100]; 
    char cep[8];

    cliente c;

    printf("Digite o nome do cliente: ");
    scanf(" %s",temp);
    
    while (temSoLetra(temp) != 0){
        limparBuffer();
        printf("Nome inválido! O nome não conter caracteres não-alfabéticos.\n");
        printf("Digite o nome do cliente: ");
        scanf(" %s",temp);
    }
    limparBuffer();
    strcpy(c.nome,temp);

    printf("Digite o número de telefone do cliente: ");
    scanf(" %s",c.telefone);
    
    while ((atoi(c.telefone) == 0) || (strlen(c.telefone) < 11)){
        limparBuffer();
        printf("Número inválido! Digite um número com DDD, sem símbolos ou espaços.\n");
        printf("Digite o número de telefone do cliente: ");
        scanf(" %s",c.telefone);
    }
    limparBuffer();


    printf("Digite o endereço do cliente:\n");

    printf("Rua: ");
    scanf("%[^\n]",c.endereco.rua);
    limparBuffer();

    printf("Número: ");
    scanf("%i",&c.endereco.numero);
    limparBuffer();

    printf("CEP: ");
    scanf(" %s",cep);
    limparBuffer();

    while (atoi(cep) == 0){
        limparBuffer();
        printf("CEP inválido! Digite um CEP de 8 dígitos, sem hífen.\n");
        printf("CEP: ");
        scanf(" %s",cep);
    }
    limparBuffer();

    strcpy(c.endereco.cep,cep);
    
    printf("Realizando o cadastro do cliente...\n");
    c.codigo = gerarCodigoCliente();
    
    //Verifica se o código gerado já existe no arquivo
    //Caso exista, gera outro código e verifica novamente
    while (validarCodigoCliente(f,c.codigo) != 0){ 
        c.codigo = gerarCodigoCliente();
    }

    //Adiciona os dados do cliente ao fim do arquivo
    fseek(f,0,SEEK_END);
    fwrite(&c,sizeof(c),1,f);
    fflush(f);

    printf("\nCliente de código %i cadastrado com sucesso!\n\n",c.codigo);
}

#endif // CLIENTE_H_INCLUDED