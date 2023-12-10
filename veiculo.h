#ifndef VEICULO_H_INCLUDED
#define VEICULO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estruturas.h"
#include "validacao.h"

int gerarCodigoVeiculo(void){
    int codigo;

    codigo = (rand() % 100000 );
    
    return codigo;
}

int buscarCodigoVeiculo(FILE *f, int codigo){
    veiculo v;

    fseek(f,0,SEEK_SET);

    while (!feof(f)){
        fread(&v,sizeof(v),1,f);

        if (v.codigo == codigo){
            return 1;
        }
    }

    return 0;
}

void cadastrarVeiculo(FILE *f){
    char temp[30];
    
    veiculo v;

    printf("Digite a descrição do veículo: ");
    fgets(v.descricao,100,stdin);
    
    printf("Digite o modelo do veículo: ");
    fgets(v.modelo,50,stdin);
    
    printf("Digite a cor do veículo: ");
    fgets(v.cor,50,stdin);
    
    printf("Digite a placa do veículo: ");
    fgets(v.placa,15,stdin);
    
    printf("Digite o status do veículo: \n");
    printf("A - Alugado\n");
    printf("D - Disponível\n");
    printf("M - Em manutenção\n");

    v.status = getchar();
    limparBuffer();

    printf("Digite o valor da diária do veículo: ");
    fgets(temp,sizeof(temp),stdin);
    v.valor = atof(temp);
    
    printf("Digite o número de ocupantes do veículo: ");
    fgets(temp,sizeof(temp),stdin);
    v.ocupantes = atoi(temp);

    v.codigo = gerarCodigoVeiculo();

    while (buscarCodigoVeiculo(f,v.codigo) != 0){ 
        v.codigo = gerarCodigoVeiculo();
    }

    fseek(f,0,SEEK_END);
    fwrite(&v,sizeof(v),1,f);
    fflush(f);

    printf("Veículo de código %i cadastrado com sucesso!\n\n",v.codigo);
}

void CarroCliente(FILE *f){
    int codigo;
    veiculo v;
    printf("Digite o codigo a seguir...\n");
    scanf("%d",&codigo);
    limparBuffer();
    //limpar o buffer.
    fseek(f,0,SEEK_SET);
    while(fread(&v,sizeof(v),1,f) == 1)
    {
     if (v.codigo == codigo)
     {
        printf("codigo: %d\n",v.codigo);
        printf("descricao: %s\n",v.descricao);
        printf("modelo: %s\n",v.modelo);
        printf("cor: %s\n",v.cor);
        printf("placa: %s\n",v.placa);
        printf("valor: %f\n",v.valor);
        printf("ocupantes: %d\n",v.ocupantes);
        printf("status: %s\n",v.status);
     }
     else
     {
       printf("Codigo Nao encontrado...\n");
     }
    }
}

void ConfirmacaoDeMudanca(FILE *f,int codigo)
{
  int Confirmacao;
  veiculo v;
  printf("Dar Baixo No Veiculo?\n");
  printf("1.Sim\n");
  printf("2.Nao\n");
  scanf("%d",&Confirmacao);
  limparBuffer();
  while (Confirmacao != 1 || Confirmacao != 2)
  {
  if(Confirmacao == 1)
  {
   atualizaStatusVeiculo(f,codigo,'D');
  }
  else if (Confirmacao != 2)
  {
   printf("Numero Invalido...\n");
  }
  }

}

#endif // VEICULO_H_INCLUDED