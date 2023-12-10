
//função main para teste
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "veiculo.h"
#include "cliente.h"
#include "locacao.h"

int main(){
    setlocale(LC_ALL,"pt_BR.utf8");
    srand(time(0));
    
    FILE *clientes;
    FILE *veiculos;
    FILE *locacoes;

    int opcao = 1;
    int codigoCliente = 0;

    while (opcao != 0){
        printf("1) Cadastrar cliente\n");
        printf("2) Buscar clientes\n");
        printf("3) Cadastrar locação\n");
        printf("4) Buscar locações\n");
        printf("5) Cadastrar veículo\n");
        printf("6) Buscar veículos\n");
        printf("7) Calcular pontos de fidelidade\n");
        printf("0) Sair\n");
        scanf("%i",&opcao);
        limparBuffer();

        switch (opcao){
            case 0:
                printf("Finalizando execução\n");
                break;
            case 1:
                if ((clientes = fopen("clientes.dat","r+b")) == NULL){ //Cria o registro de clientes caso não exista
                    printf("Criando registro de clientes...\n");
                    clientes = fopen("clientes.dat","w+b");
                }
                cadastrarCliente(clientes);
                fclose(clientes);
                break;
            case 2:
                if ((clientes = fopen("clientes.dat","r+b")) == NULL){
                    printf("Registro de clientes não encontrado!\n");
                    break;
                }
                buscarCodigoCliente(clientes);
                fclose(clientes);
                break;
            case 3: 
                if ((locacoes = fopen("locacoes.dat","r+b")) == NULL){ //Cria o registro de locações caso não exista
                    printf("Criando registro de locações...\n");
                    locacoes = fopen("locacoes.dat","w+b");
                }
                if ((clientes = fopen("clientes.dat","r+b")) == NULL){
                    printf("Registro de clientes não encontrado!\n");
                    fclose(locacoes);
                    break;
                }
                if ((veiculos = fopen("veiculos.dat","r+b")) == NULL){
                    printf("Registro de veículos não encontrado!\n");
                    fclose(locacoes);
                    fclose(clientes);
                    break;
                }
                
                cadastraLocacao(locacoes,clientes,veiculos);

                fclose(locacoes);
                fclose(clientes);
                fclose(veiculos);
                break;
            case 4:
                if ((locacoes = fopen("locacoes.dat","r+b")) == NULL){ 
                    printf("Registro de locações não encontrado!\n");
                    break;
                }
                if ((clientes = fopen("clientes.dat","r+b")) == NULL){
                    printf("Registro de clientes não encontrado!\n");
                    fclose(locacoes);
                    break;
                }

                printf("Digite o código do cliente: ");
                scanf("%i",&codigoCliente);
                limparBuffer();

                if (validaCodigoCliente(clientes,codigoCliente) == 0){
                    buscaLocacao(locacoes,codigoCliente);
                }
                else {
                    printf("Código inválido!\n");
                }

                fclose(locacoes);
                fclose(clientes);

                break;
            case 5:
                if ((veiculos = fopen("veiculos.dat","r+b")) == NULL){ //Cria o registro de veículos caso não exista
                    printf("Criando registro de veículos...\n");
                    veiculos = fopen("veiculos.dat","w+b");
                }

                cadastrarVeiculo(veiculos);

                fclose(veiculos);
                break;
            case 6: 
                if ((veiculos = fopen("veiculos.dat","r+b")) == NULL){
                    printf("Registro de veículos não encontrado!\n");
                    break;
                }

                CarroCliente(veiculos);

                fclose(veiculos);

                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }
    
    return 0;
}