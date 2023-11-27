#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
struct tEndereco {
    char rua[50];
    int numero;
    int cep;

};
struct tCliente {
    int codigo;
    char nome[50];
    char telefone[12];
    struct tEndereco endereco;
};

#endif // CLIENTE_H_INCLUDED