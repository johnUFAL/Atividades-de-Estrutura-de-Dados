#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    float nota;
} Aluno;

int main() {
    int qtd_aluno;
    scanf("%d", &qtd_aluno);
    getchar();

    Aluno *v = malloc(qtd_aluno * sizeof(Aluno));

    for (int i = 0; i < qtd_aluno; i++) {
        fgets(v[i].nome, sizeof(v[i].nome), stdin);
        scanf("%f", &v[i].nota);
        getchar();
    }

    printf("\n-----Alunos-----\n");
    for (int i = 0; i < qtd_aluno; i++) {
        printf("\nAluno: %s\nNotas: %.2f", v[i].nome, v[i].nota);
    }
    printf("\n");

    free(v);
    return 0;
}