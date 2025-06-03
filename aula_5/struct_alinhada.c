#include <stdio.h>
#include <string.h>

typedef struct {
    int av[4];
} Nota;

typedef struct {
    char nome[50];
    Nota notas;
} Aluno;

void insertSort(Aluno *aluno) {
    int i, j, aux;

    for (i = 1; i < 4; i++) {
        aux = aluno->notas.av[i];
        j = i -  1;

        while (j >= 0 && aux < aluno->notas.av[j]) {
            aluno->notas.av[j+1] = aluno->notas.av[j];
            j--;
        }
        aluno->notas.av[j+1] = aux;           
    }
}

int main() {
    Aluno aluno;

    puts("Digite seu nome:");
    fgets(aluno.nome, 50, stdin);

    aluno.nome[strcspn(aluno.nome, "\n")] = 0;  //quebra de linnha
    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("Digite a nota da AV%d: ", i + 1);
        scanf("%d", &aluno.notas.av[i]);
    }

    insertSort(&aluno);

    printf("\nNotas ordenadas:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d\n", aluno.notas.av[i]);
    }

    return 0;
}

/*-> usamos quando temos ponteiros para structs
Ex:  p->idade = 10;   (*p).idade = 10;

(Aluno *aluno) usamos ponteiro para modificar os dados direto da 
memoria, sem ponteiro poderiamos usar uma copia da struct
*/