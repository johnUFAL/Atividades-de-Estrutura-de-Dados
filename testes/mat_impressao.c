#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);

    int **mat = malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        mat[i] = malloc(colunas * sizeof(int));
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < linhas; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}