#ifndef LOCACAO_H_INCLUDED
#define LOCACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "cliente.h"
#include "estruturas.h"
#include "validacao.h"
#include "veiculo.h"



typedef struct tVeiculo veiculo;
typedef struct tData data;
typedef struct tCliente cliente;
typedef struct tLocacao locacao;

int temVeiculosDisponiveis(FILE *arqVeiculos, int capacidade){
    /*
        Função que determina se existem veículos disponíveis que atendem o número de passageiros desejado

        Parâmetros:
            FILE *arqVeiculos: Arquivo onde se encontra o cadastro dos veículos
            int capacidade: número de passageiros desejado

        Retorno:
            Caso exista pelo menos um veículo que atende os critérios: 1
            Caso contrário: 0
    */

    veiculo v;

    fseek(arqVeiculos,0,SEEK_SET);


    while (!feof(arqVeiculos)){
        fread(&v,sizeof(v),1,arqVeiculos);
        if ((v.status == 'D') && (v.ocupantes >= capacidade)){
            return 1;
        }
    }

    return 0;
}

void exibeVeiculosDisponiveis(FILE *arqVeiculos, int capacidade){
    /*
        Função que exibe na tela a lista dos veículos disponíveis que atendem a capacidade de passageiros desejada

        Parâmetros:
            FILE *arqVeiculos: Arquivo onde se encontra o cadastro dos veículos
            int capacidade: número de passageiros desejado
    */

    veiculo v;

    fseek(arqVeiculos,0,SEEK_SET);


    while (!feof(arqVeiculos)){
        fread(&v,sizeof(v),1,arqVeiculos);
        if ((v.status == 'D') && (v.ocupantes >= capacidade)){
            printf("Código: %i\n",v.codigo);
            printf("Modelo: %s\n",v.modelo);
            printf("Cor: %s\n",v.cor);
            printf("Placa: %s\n",v.placa);
            printf("Valor diária: R$ %.2f\n",v.valor);
            printf("Capacidade de ocupantes: %i\n",v.ocupantes);
            printf("\n");
        }
    }
}
void atualizaStatusVeiculo(FILE *arqVeiculos, int codigo, char status){
    /*
        Função que atualiza o status de um veículo
        
        Parâmetros:
            FILE *arqVeiculos: Arquivo onde se encontra o cadastro dos veículos
            int codigo: código do veículo cujo status será alterado
            char status: o status novo do veículo, representado por um caractere
    */
    veiculo v;

    fseek(arqVeiculos,0,SEEK_SET);

    while (!feof(arqVeiculos)){
        fread(&v,sizeof(v),1,arqVeiculos);
        if (v.codigo == codigo){
            v.status = status;
            fwrite(&v,sizeof(v),1,arqVeiculos);
        }
    }
}

float calcValorTotal(FILE *arqVeiculos, locacao l){
    /*
        Função que calcula o vator total de uma locação

        Parâmetros:
            FILE *arqVeiculos: arquivo onde se encontra o cadastro dos veículos
            locacao l: estrutura de dados contendo dados sobre a locação cujo valor será calculado

        Retorno:
            float valor: valor total da locação
    */
    veiculo v;

    float valor = 0;

    fseek(arqVeiculos,0,SEEK_SET);
    while (!feof(arqVeiculos)){
        fread(&v,sizeof(v),1,arqVeiculos);
        if (v.codigo == l.codigoVeiculo){
            valor = v.valor * (diferencaData(l.dataRetirada,l.dataDevolucao));
            return valor;
        }
    }
}

void cadastraLocacao(FILE *arqLocacao, FILE *arqClientes, FILE *arqVeiculos){
    /*
    Função que cadastra uma locação a partir de dados lidos do teclado

    Parâmetros:

    FILE *arqLocacao: O arquivo onde será salvo o cadastro da locação
    FILE *arqClientes: O arquivo onde se encontra o cadastro do cliente
    FILE *arqVeiculos: O arquivo onde se encontra o cadastro dos veículos
    */

    int ocupantes = 0;
    char temp[50];

    locacao l;
    
    printf("Digite o nome do cliente: ");
    fgets(temp,50,stdin);

    while (validaNomeCliente(temp,arqClientes) != 1){
        printf("Cliente não encontrado!\n");
        printf("Digite o nome do cliente:");
        fgets(temp,50,stdin);
    }

    l.codigoCliente = validaNomeCliente(temp,arqClientes);

    printf("Digite a data de retirada desejada (formato d-m-aaaa): ");

    scanf("%i %i %i",&l.dataRetirada.dia,&l.dataRetirada.mes,&l.dataRetirada.ano);
    
    while(validarData(l.dataRetirada) != 0){
        limparBuffer();
        printf("Data inválida! Verifique se a data foi digitada corretamente.\n");
        printf("Digite a data de retirada desejada (formato d-m-aaaa): ");
        scanf("%i %i %i",&l.dataRetirada.dia,&l.dataRetirada.mes,&l.dataRetirada.ano);
    }
    limparBuffer();

    printf("Digite a data de devolução desejada (formato d-m-aaaa): ");

    scanf("%i %i %i",&l.dataDevolucao.dia,&l.dataDevolucao.mes,&l.dataDevolucao.ano);
    while((validarData(l.dataDevolucao) != 0) || (comparaData(l.dataRetirada,l.dataDevolucao) != 2)){
        limparBuffer();
        printf("Data inválida! Verifique se a data foi digitada corretamente.\n");
        printf("Digite a data de retirada desejada (formato d-m-aaaa): ");
        scanf("%i %i %i",&l.dataRetirada.dia,&l.dataRetirada.mes,&l.dataRetirada.ano);
    }
    limparBuffer();

    printf("Digite o número de ocupantes desejado: ");
    
    scanf("%i",&ocupantes);
    limparBuffer();
    
    if (temVeiculosDisponiveis(arqVeiculos,ocupantes) == 1){
        
        exibeVeiculosDisponiveis(arqVeiculos,ocupantes);

        int codigoSelecionado;

        printf("Digite o código do veículo desejado: ");
        scanf("%i",&codigoSelecionado);

        while (validaCodigoVeiculo(arqVeiculos,codigoSelecionado) != 1){
            limparBuffer();
            printf("Código inválido!\n");
            printf("Digite o código do veículo desejado: ");
            scanf("%i",&codigoSelecionado);
        }
        limparBuffer();
        
        l.valorTotal = calcValorTotal(arqVeiculos,l);

        int seguroOuNao;
        printf("Deseja contratar seguro por R$50,00?\n1) Sim\n2) Não\n");
        scanf("%i",&seguroOuNao);
        while ((seguroOuNao != 1) && (seguroOuNao != 0)){
            limparBuffer();
            printf("Deseja contratar seguro por R$50,00?\n1) Sim\n2) Não\n");
            scanf("%i",&seguroOuNao);
        }
        limparBuffer();

        l.seguro = seguroOuNao;
        if (seguroOuNao == 1){
            l.valorTotal = l.valorTotal + 50.0;
        }

        fseek(arqLocacao,0,SEEK_END);
        fwrite(&l,sizeof(l),1,arqLocacao);
        fflush(arqLocacao);

        atualizaStatusVeiculo(arqVeiculos,codigoSelecionado,'A');

        printf("\nLocação cadastrada com sucesso!\n");
    }
    else {
        printf("Não foram encontrados veículos disponíveis.\n");
    }
}

void buscaLocacao(FILE *arqLocacao, int codigo){
    /*
        Função que exibe as locações de um determinado cliente pelo seu código

        Parâmetros:
            FILE *arqLocacao: o arquivo onde se encontram as locações
            int codigo: O código do cliente
    */
    locacao l;
    int contadorLocacoes = 0;

    fseek(arqLocacao,0,SEEK_SET);


    while (!feof(arqLocacao)){
        fread(&l,sizeof(l),1,arqLocacao);
        if (l.codigoCliente == codigo){
            printf("Código da locação: %i\n",l.codigoLocacao);
            printf("Código do veículo: %i\n",l.codigoVeiculo);
            printf("Data de retirada: %i/%i/%i\n",l.dataRetirada.dia,l.dataRetirada.mes,l.dataRetirada.ano);
            printf("Data de devolução: %i/%i/%i\n",l.dataDevolucao.dia,l.dataDevolucao.mes,l.dataDevolucao.ano);
            if (l.seguro == 1){
                printf("Possui seguro?: Sim\n");
            }
            else { printf("Possui seguro?: Não\n"); }
            printf("Valor total: R$ %.2f\n",l.valorTotal);
            printf("\n");
            contadorLocacoes++;
        }
    }

    if (contadorLocacoes < 1){
        printf("Não foram encontrados veículos disponíveis.\n");
    }
}
#endif //LOCACAO_H_INCLUDED