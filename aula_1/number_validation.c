#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validation_number(char arr[]) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (isdigit(arr[i])) {  //validacao do tipo numero
            return 1;
        }
        if (arr[0] == '-' || arr[i] == '.') { //validacao de sinal e ponto
            return 1;
        }
    }
    printf("Nao eh numero\n");
    return 0;
}

void verification(char arr[]) {
    int len = strlen(arr);
    
    if (arr[len - 1] == '\n') { //validacao de quebra de linha
        arr[len - 1] = '\0';
        len--; 
    }
    if(arr[0] == '-') { //validacao de sinal
        printf("Numero Inteiro\n");
        return;
    } else {
        for(int i = 0; i < len; i++) {
            if (arr[i] == '.') { //validacao de ponto
                    printf("Numero Real\n");
                    return;
                }
            }
     }        
     printf("Numero Natural\n");
}

int main() {
    char arr[20];
    fgets(arr, 20, stdin);

    if (validation_number(arr)) { //validacao de numero
        verification(arr);
    }

    return 0;
}