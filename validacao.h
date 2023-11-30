#ifndef VALIDACAO_H_INCLUDED
#define VALIDACAO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

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
    setlocale(LC_ALL,"Portuguese");

    for (int i = 0; i < strlen(string); i++){
        if (isalpha(string[i]) == 0){
            return 1;
        }
    }

    return 0;
}

#endif //VALIDACAO_H_INCLUDED