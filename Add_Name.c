#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definição da estrutura da lista encadeada simples
typedef struct Nodo {
    char *nome;
    struct Nodo *prox;
} Nodo;


Nodo *head = NULL;                                           

Nodo* criarNodo(char *nome) {
    Nodo *novoNodo = (Nodo*)malloc(sizeof(Nodo));              
    novoNodo->nome = strdup(nome);                             
    novoNodo->prox = NULL;                                   
    return novoNodo;
}

void adicionarNome(char *nome) {                               
    Nodo *novoNodo = criarNodo(nome);                         
    novoNodo->prox = head;                                     
    head = novoNodo;                                           
}

void removerNome(char *nome) {
    Nodo *temp = head, *prev;
    if (temp != NULL && strcmp(temp->nome, nome) == 0) {
        head = temp->prox;
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->nome, nome) != 0) {
        prev = temp;
        temp = temp->prox;
    }
    if (temp == NULL) return;
    prev->prox = temp->prox;
    free(temp);
}

void listarNomes() {
    Nodo *temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->nome);
        temp = temp->prox;
    }
}

int main() {
    int choice;
    char nome[50];
    while(1) {
        printf("1-aAdicionar nome\n2-Remover nome\n3-Listar\n4-Sair\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Digite o nome para adicionar: ");
                scanf("%s", nome);
                adicionarNome(nome);
                break;
            case 2:
                printf("Digite o nome para remover: ");
                scanf("%s", nome);
                removerNome(nome);
                break;
            case 3:
                listarNomes();
                break;
            case 4:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
