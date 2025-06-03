#include <stdio.h>

void selection_sort(int v[], int n) {
    for (int i = 0; i < n-1; i++) {
        int menor = i; //MAIOR SE FOR DECRESCENTE
        for (int j = i+1; j < n; j++) {
            if (v[j] < v[menor]) menor = j; //MUDA O SINAL PARA SER DECRESCENTE
        }
        int aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}

int main() {
    int n;
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

    selection_sort(v, n);

    puts("Vetor ordenado:");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    return 0;
    
}