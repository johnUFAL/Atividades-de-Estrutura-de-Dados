#include <stdio.h>

void radix_sort(int *v, int n) {
    int i, exp = 1, m = 0, aux[n], balde[10] = {0};

    for (i = 0; i < n; i++) { //usamos a var m para pegar o maior valor do vetor
        if (v[i] > m) {
            m = v[i];
        }
    }

    while ((m / exp) > 0) { //isso avi servir oara ordenar por cada casa decimal
        for (i = 0; i < 10; i++) { //aqui vai reinciar os contadores de cada casa
            balde[i] = 0;
        }
        for (i = 0; i < n; i++) { // conta quantas vezes cada digito vai aparecer
            balde[(v[i] / exp) % 10]++;
        }
         //soma a posicao final da cada num no vetor ordenado
        for (i = 1; i < 10; i++) {
            balde[i] += balde[i-1];//I = 8, I >= 0, += I+1 PARA SER DECRESCENTE 
        }
        for (i = n-1; i >= 0; i--) { // enche aux ordenando de tras pra frente
            aux[--balde[(v[i] / exp) % 10]] = v[i];
        }
        for (i = 0; i < n; i++) { //copia o vetor ordenado de volta pra o vetor original
            v[i] = aux[i];
        }
        exp *= 10; //exp represando a as casas decimais que vamos analisar
    }
}

int main() {
    int  n;
    scanf("%d", &n);

    int v[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    puts("Vetor normal:");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    puts(" ");

    radix_sort(v, n);

    puts("Vetor ordenado:");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    return 0;
}