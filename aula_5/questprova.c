#include <stdio.h>
#include <string.h>

typedef struct {
    float media;
} Nota;

typedef struct {
    char professor[50];
    char disciplina[50];
    Nota notas;
} Colegio;

void insertSort(Colegio *aluno, int n, int flag) {
    int i, j;
    Colegio aux;

    for (i = 1; i < n; i++) {
        aux = aluno[i];
        j = i -  1;

        // Se flag == 0, ordena professor (crescente)
        // Se flag == 1, ordena disciplina (decrescente)
        while (j >= 0 && ((flag == 0 && strcmp(aux.professor, aluno[j].professor) < 0) || 
             (flag == 1 && strcmp(aux.disciplina, aluno[j].disciplina) > 0))) 
        {
            aluno[j+1] = aluno[j];
            j--;
        }
        aluno[j+1] = aux;           
    }
}

int main() {
    Colegio alunos[4];
    int i, flag;
    
    do {
        printf("Digite 0 para ordenar professores (crescente) ou 1 para disciplinas (decrescente): ");
        scanf("%d", &flag);
    } while (flag != 0 && flag != 1);
    
    for (i = 0; i < 4; i++) {
        getchar();  // Limpa buffer do scanf
            
        printf("Digite o nome do professor: ");
        fgets(alunos[i].professor, 50, stdin);
        alunos[i].professor[strcspn(alunos[i].professor, "\n")] = 0;
    
        printf("Digite a disciplina: ");
        fgets(alunos[i].disciplina, 50, stdin);
        alunos[i].disciplina[strcspn(alunos[i].disciplina, "\n")] = 0;
    
        printf("Digite a média: ");
        scanf("%f", &alunos[i].notas.media);
    }
    
    insertSort(alunos, 4, flag);
    
    printf("\nLista ordenada:\n");
    for (i = 0; i < 4; i++) {
         printf("Professor: %s | Disciplina: %s | Média: %.2f\n", alunos[i].professor, alunos[i].disciplina, alunos[i].notas.media);
    }
    
    return 0;
}