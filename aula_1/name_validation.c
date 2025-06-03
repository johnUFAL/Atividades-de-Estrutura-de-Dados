#include <stdio.h>
#include <string.h>
#include <ctype.h>

char validation_string(char arr[]) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (!isalpha(arr[i])) {  //validacao de tipo string
            return 0;
        }
    }
    return 1;
}

char validation(char arr[]){
    int len = strlen(arr);
    
    if (arr[len - 1] == '\n') { //validacao de quebra de linha
        arr[len - 1] = '\0';
    }

    if (islower(arr[0]) || isspace(arr[0])) { //validacao de espaço e tipo de letra 
        printf("Nome nao valido\n");
        return 0;
    }
    printf("Nome valido\n");
}

int main() {
    char nome[100];
    fgets(nome, 100, stdin);
    validation_string(nome);
    validation(nome);

    return 0;
}