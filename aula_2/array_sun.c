#include <stdio.h>
int main() {
    int n; 
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int soma = 0;
    for(int i = 0; i < n; i++){
        soma += arr[i];
    }
        
    printf("Soma: %d\n", soma);
    return 0;
}