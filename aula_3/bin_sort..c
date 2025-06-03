#include <stdio.h> 

int maximo(int *v, int n) { //retornar o maior elemento do vetor
    int max = v[0]; //iniciar na primeira posicao
    for (int i = 1; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

void bin_sort(int *v, int n) {
    int balde[maximo(v, n) + 1]; //aqui vamos contar as ocorrencias 

    const int max = maximo(v, n); //usa a maximo para ter o amior valor
    for (int i = 0; i <= max; i++) { //inicia cada balde com 0
        balde[i] = 0;
    }
    for (int i = 0; i < n; i++) { //conta a ocorrencia de cada numero
        balde[v[i]]++;
    }
    //reconstruindo o vetor
    for (int i = 0, j = 0; i <= max; i++){ //INVERTE I = MAX I >= 0 PARA SER DECRESCENTE
        while (balde[i] > 0) {
            v[j++] = i;
            balde[i]--;
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

    bin_sort(v, n);

    puts("Vetor ordenado:");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    return 0;
}

/*priemro cria um vetor balde que tem tamanho max+1 e 
max é o maio numero e depois vamos zerar todos os baldes com 0
dai vamos contar a frequencia em cada numero aparece 
isso é armazenada no balde
depois reconstroi o vetor ordenando percorrendo o balde
*/