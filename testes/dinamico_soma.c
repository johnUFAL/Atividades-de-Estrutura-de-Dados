#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int *v = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += v[i];
    }

    printf("soma: %d ", soma);
    free(v);

    return 0;
}