#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho máximo para nome e email
#define MAX_NOME 100
#define MAX_EMAIL 50

void adicionarPessoa(void *pBuffer);
void removerPessoa(void *pBuffer);
void buscarPessoa(void *pBuffer);
void listarTodos(void *pBuffer);

int main() {
    // Tamanho do buffer: opção (int) + nome (char[MAX_NOME]) + idade (int) + email (char[MAX_EMAIL]) + head (void*) + tail (void*)
    void *pBuffer = malloc(sizeof(int) + MAX_NOME * sizeof(char) + sizeof(int) + MAX_EMAIL * sizeof(char) + 2 * sizeof(void *));
    if (!pBuffer) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    *(int *)pBuffer = 0; // Inicializa a opção do menu
    *(void **)(pBuffer + sizeof(int)) = NULL; // Inicializa o head da lista
    *(void **)(pBuffer + sizeof(int) + sizeof(void *)) = NULL; // Inicializa o tail da lista

    do {
        printf("\n1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4- Listar todos\n");
        printf("5- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", (int *)(pBuffer)); // Lê a opção diretamente no buffer

        switch (*(int *)pBuffer) {
            case 1:
                adicionarPessoa(pBuffer);
                break;
            case 2:
                removerPessoa(pBuffer);
                break;
            case 3:
                buscarPessoa(pBuffer);
                break;
            case 4:
                listarTodos(pBuffer);
                break;
            case 5:
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (*(int *)pBuffer != 5);

    // Liberar memória alocada para a lista
    void *current = *(void **)(pBuffer + sizeof(int));
    while (current != NULL) {
        void *next = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL + 2 * sizeof(void *));
        free(current);
        current = next;
    }

    free(pBuffer);
    return 0;
}

void adicionarPessoa(void *pBuffer) {
    void *novo = malloc(MAX_NOME + sizeof(int) + MAX_EMAIL + 2 * sizeof(void *));
    if (!novo) {
        printf("Erro ao alocar memória\n");
        return;
    }

    printf("Nome: ");
    scanf("%s", (char *)novo);
    printf("Idade: ");
    scanf("%d", (int *)(novo + MAX_NOME));
    printf("Email: ");
    scanf("%s", (char *)(novo + MAX_NOME + sizeof(int)));

    *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL) = NULL; // Inicializa prox
    *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = NULL; // Inicializa ant

    // Inserção ordenada
    void *head = *(void **)(pBuffer + sizeof(int));
    void *prev = NULL;
    void *current = head;

    while (current != NULL && strcmp((char *)current, (char *)novo) < 0) {
        prev = current;
        current = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
    }

    if (prev == NULL) { // Inserção no início
        *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL) = head;
        if (head != NULL) {
            *(void **)(head + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = novo;
        }
        *(void **)(pBuffer + sizeof(int)) = novo;
    } else { // Inserção no meio ou fim
        *(void **)(prev + MAX_NOME + sizeof(int) + MAX_EMAIL) = novo;
        *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = prev;
        *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL) = current;
        if (current != NULL) {
            *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = novo;
        }
    }

    printf("Pessoa adicionada com sucesso!\n");
}

void removerPessoa(void *pBuffer) {
    printf("Nome da pessoa a remover: ");
    scanf("%s", (char *)(pBuffer + sizeof(int) + 2 * sizeof(void *))); // Armazena o nome no local correto no buffer

    void *head = *(void **)(pBuffer + sizeof(int));
    void *current = head;

    while (current != NULL && strcmp((char *)current, (char *)(pBuffer + sizeof(int) + 2 * sizeof(void *))) != 0) {
        current = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
    }

    if (current == NULL) {
        printf("Pessoa não encontrada!\n");
        return;
    }

    void *prev = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *));
    void *next = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);

    if (prev != NULL) {
        *(void **)(prev + MAX_NOME + sizeof(int) + MAX_EMAIL) = next;
    } else {
        *(void **)(pBuffer + sizeof(int)) = next;
    }

    if (next != NULL) {
        *(void **)(next + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = prev;
    }

    free(current);
    printf("Pessoa removida com sucesso!\n");
}

void buscarPessoa(void *pBuffer) {
    printf("Nome da pessoa a buscar: ");
    scanf("%s", (char *)(pBuffer + sizeof(int) + 2 * sizeof(void *)));

    void *current = *(void **)(pBuffer + sizeof(int));

    while (current != NULL && strcmp((char *)current, (char *)(pBuffer + sizeof(int) + 2 * sizeof(void *))) != 0) {
        current = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
    }

    if (current == NULL) {
        printf("Pessoa não encontrada!\n");
        return;
    }

    printf("Nome: %s\n", (char *)current);
    printf("Idade: %d\n", *(int *)(current + MAX_NOME));
    printf("Email: %s\n", (char *)(current + MAX_NOME + sizeof(int)));
}

void listarTodos(void *pBuffer) {
    void *current = *(void **)(pBuffer + sizeof(int));

    if (current == NULL) {
        printf("Nenhuma pessoa na agenda.\n");
        return;
    }

    while (current != NULL) {
        printf("Nome: %s\n", (char *)current);
        printf("Idade: %d\n", *(int *)(current + MAX_NOME));
        printf("Email: %s\n", (char *)(current + MAX_NOME + sizeof(int)));
        current = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
    }
}
