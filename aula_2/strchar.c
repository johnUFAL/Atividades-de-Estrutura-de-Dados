#include <stdio.h>
#include <string.h>

int main() {
    char str[20];
    char letra;

    scanf("%c", &letra);
    for (int i = 0; i != '\0'; i++) {
        scanf("%s", &str[i]);
    }

    return 0;
}