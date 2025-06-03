#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    float *v = malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        scanf("%f", &v[i]);
    }

    float soma = 0;
    for (int i = 0; i < n; i++) {
        soma += v[i];
    }

    float media = soma/(float)n;

    printf("media: %.2f", media);
    free(v);

    return 0;
}