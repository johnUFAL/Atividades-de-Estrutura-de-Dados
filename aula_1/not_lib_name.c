#include <stdio.h>
#include <string.h>

char validation_string(char arr[]) {
    int i = 0; //contador
    
    int len = strlen(arr);
    if (arr[len - 1] == '\n') { //validacao de quebra de linha
        arr[len - 1] = '\0';
        len--; 
    }

    if (arr[0] == ' ' || arr[len - 1] == ' ') { //validacao de espaco
        printf("Nome nao valido\n");
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (!((arr[i] >= 'A' && arr[i] <= 'Z') || //validacao de letra
              (arr[i] >= 'a' && arr[i] <= 'z') || 
              arr[i] == ' ')) { //validacao de espaco
            printf("Nome nao valido\n");
            return 0;
        }
    }
    return 1;
}

void validation(char arr[]){
    int len = strlen(arr);

    if (arr[0] < 'A' || arr[0] > 'Z') {  //validacao de letra
        printf("Nome nao valido\n");
        return;
    }

    for (int i = 1; i < len; i++) {
        if (arr[i] == ' ' && (arr[i+1] < 'A' || arr[i+1] > 'Z')) { //validacao de espaco'    
            printf("Nome nao valido\n");
            return;  
        }
    }
    printf("Nome valido\n");
}

int main() {
    char nome[100];
    fgets(nome, 100, stdin);

    if (validation_string(nome)) { //validacao de string
        validation(nome);
    }

    return 0;
}