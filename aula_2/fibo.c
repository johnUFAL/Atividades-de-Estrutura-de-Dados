#include <stdio.h>

int fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int soma(int n){     
    if(n == 1) return 0;
    if(n == 2) return 1;
    return fibonacci(n) + fibonacci(n-1);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", soma(n));

    return 0;
}

//somar os n primeiros termos de fibonacci