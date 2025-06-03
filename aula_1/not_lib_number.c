#include <stdio.h>
#include <string.h>

int validation_number(char arr[]) {
    int ponto = 0; 
    
    for (int i = 0; arr[i] != '\0' && arr[i] != '\n'; i++) {
        if (arr[i] == '.') { 
            if (ponto || i == 0) {  //validacao de ponto
                printf("Nao eh numero\n");
                return 0; 
            }
            ponto = 1; 
        } else if (arr[i] == '-') {
            if (i != 0) {  //validacao de sinal
                printf("Nao eh numero\n");
                return 0;
            }
        } else if (arr[i] < '0' || arr[i] > '9') {  //validacao de tipo numero
            printf("Nao eh numero\n");
            return 0;
        }
    }
    return 1;
}

void verification(char arr[]) {
    int len = strlen(arr);
    
    if (arr[len - 1] == '\n') { 
        arr[len - 1] = '\0';
        len--; //validacao de quebra de linha
    }

    if (arr[0] == '-') { 
        printf("Numero Inteiro\n");
        return;
    } 
    
    for (int i = 0; i < len; i++) {
        if (arr[i] == '.') { 
            printf("Numero Real\n");
            return; 
        } 
    }
    
    printf("Numero Natural\n");
}

int main() {
    char arr[20];
    fgets(arr, 20, stdin);

    if (validation_number(arr)) { 
        verification(arr);
    }

    return 0;
}
