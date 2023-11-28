#ifndef VEICULO_H_INCLUDED
#define VEICULO_H_INCLUDED

struct tVeiculo {
    int codigo;
    char descricao[100];
    char modelo[50];
    char cor[50];
    char placa[15];
    char dataretirada[15];
    char datadevolucao[15];
    float valor;
    int ocupantes;
    char status[50];
};

#endif // VEICULO_H_INCLUDED