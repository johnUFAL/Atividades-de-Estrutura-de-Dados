#include <stdio.h>

void bubble_sort(int v[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (v[j] > v[j+1]) {
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
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

    bubble_sort(v, n);

    puts("Vetor ordenado:");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    return 0;
}