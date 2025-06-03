#include <stdio.h> 

int maior(int arr[], int n, int m) {
    if (n == 0) return m;
    if (arr[n-1] > m) return m = arr[n-1];
    return maior(arr, n-1, m);
}

int main() {
    int n; 
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%d\n", maior(arr, n, arr[0]));

    return 0;
}