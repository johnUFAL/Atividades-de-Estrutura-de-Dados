#include <stdio.h>

void swap(int *a, int *b) { //troca de dois elementos usando ponteiro
    int aux = *a;
    *a = *b;
    *b = aux;
}

int particao(int *v, int esquerda, int direita) { //parte o vetor para p quick
    int pivo = v[direita]; //pivo é o ultimo elemento 
    int i = esquerda-1; //elementos menores que o pivo vao ter esse indice

    for (int j = esquerda; j < direita; j++) { //andando no vetor
        //se o elemneto atual for menor que o pivo
        if (v[j] < pivo) { //INVERTE O SINAL PARA SER DECRESCENTE
            i++; //aumenta a posciao domenor
            swap(&v[i], &v[j]); //troca
        }
    }
    swap(&v[i+1], &v[direita]); //arruma o vetor na posicao certa
    return (i+1); //da a posicao do pivo pra o quick
}

void quick_sort(int *v, int esquerda, int direita) {
    if (esquerda < direita) {  //condicao de parada da rec
        int pi = particao(v, esquerda, direita); //recebe a posicao do pivo
        quick_sort(v, esquerda, pi-1); //lado do pivo a esquerda
        quick_sort(v, pi+1,direita); //lado do pivo a direita
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    puts("Vetor normal:");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    puts(" ");

    quick_sort(arr, 0, n-1);

    puts("Vetor ordenado:");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}

//particao - vai escolher o pivo e dps vai reorganizar os elemetos - a esquerdar os maiores a direita os menores
//pra fazer isso troca os elementos com swap
//quick de forma recursiva - usar a funcao particao pra dividir e conquistar 
//vai ordenar nas duas metades do vetor (maiores e nemores elementos)
//pi+-1 para ordenar a parte antes e deois do pivo