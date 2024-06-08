#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void adicionarNome(char **ponteiro, unsigned int *tamanhoTotal, int *conta) {
    char nome[100] = {0};
    printf("Digite o nome: ");
    fgets(nome, 100, stdin);
    *tamanhoTotal = (*tamanhoTotal + strlen(nome) - 1) * sizeof(char);
    *ponteiro = realloc(*ponteiro, *tamanhoTotal);
    
    if(*ponteiro==NULL){
        printf("erro de alocação");
        return 0;
    }
    for(unsigned int i = 0; i < strlen(nome) - 1; i++) {
        *(*ponteiro+(*conta)) = nome[i];
        (*conta)++;
    }
}

void listarNomes(char *ponteiro, int conta) {
    for (int k = 0; k < conta; k++) {
        printf("%c", ponteiro[k]);
    }
}


int main() {
    unsigned int tamanhoTotal = 0;
    char *ponteiro = NULL;
    int conta = 0;
    int menu = 0;

    while(menu != 4) {
        printf("-1) Adicionar nome\n");
        printf("-2) Remover nome\n");
        printf("-3) Listar\n");
        printf("-4) Sair\n");

        scanf("%d", &menu);
        while ((getchar()) != '\n'); // Limpa o buffer de entrada

        switch(menu) {
            case 1:
                adicionarNome(&ponteiro, &tamanhoTotal, &conta);
                break;
            case 2:
                
                break;
            case 3:
                listarNomes(ponteiro, conta);
                break;
            default:
                break;
        }
    }

    free(ponteiro);
    return 0;
}
