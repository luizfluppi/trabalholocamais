#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
struct tData {
    int dia;
    int mes;
    int ano;
};
typedef struct tData data;

struct tEndereco {
    char rua[50];
    int numero;
    char cep[8];

};
typedef struct tEndereco endereco;

struct tCliente {
    int codigo;
    char nome[50];
    char telefone[12];
    int pontosfidelidade;
    char kitLocaMais[10];
    struct tEndereco endereco;
};
typedef struct tCliente cliente;

struct tVeiculo {
    int codigo;
    char descricao[100];
    char modelo[50];
    char cor[50];
    char placa[15];
    float valor;
    int ocupantes;
    char status;
};
typedef struct tVeiculo veiculo;

struct tLocacao {
    int codigoLocacao;
    struct tData dataRetirada;
    struct tData dataDevolucao;
    int seguro;
    int codigoCliente;
    int codigoVeiculo;
    float valorTotal;
};
typedef struct tLocacao locacao;

#endif //ESTRUTURAS_H_INCLUDED