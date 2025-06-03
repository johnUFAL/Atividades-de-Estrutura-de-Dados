#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;
    int *p;

    scanf("%d", &x);

    p = &x;


    printf("Valor: %d\nEndereco: %p", *p, (void*)p);

    return 0;
}