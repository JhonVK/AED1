#include <stdio.h>

int main() {
    char str[20] = "12ab";
    int n;

    if (sscanf(str, "%d", &n) == 1) {
        printf("Valor convertido: %d\n", n);
    } else {
        printf("Conversão falhou.\n");
    }

    return 0;
}
