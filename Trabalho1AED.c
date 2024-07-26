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
    // Tamanho do buffer: opção (int) + head (void*) + nome (char)
    void *pBuffer = malloc(sizeof(int) + sizeof(void *) + MAX_NOME);
    if (!pBuffer) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    *(int *)pBuffer = 0; // Inicializa a opção do menu
    *(void **)(pBuffer + sizeof(int)) = NULL; // Inicializa o head da lista

    do {
        printf("\n1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4- Listar todos\n");
        printf("5- Sair\n");
        printf("Escolha uma opcao: ");
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
                printf("Opcao invalida!\n");
                break;
        }
    } while (*(int *)pBuffer != 5);

    // Liberar memória alocada para a lista
    void *current = *(void **)(pBuffer + sizeof(int));
    while (current != NULL) {
        void *next = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
        free(current);
        current = next;
    }

    free(pBuffer);
    return 0;
}

void adicionarPessoa(void *pBuffer) {
    void *novo = malloc(MAX_NOME+ sizeof(int) + MAX_EMAIL + 2 * sizeof(void *));
    if (!novo) {
        printf("Erro ao alocar memoria\n");
        return;
    }

    while (getchar() != '\n');
    printf("Nome: ");
    fgets((char *)novo, MAX_NOME, stdin);
    ((char *)novo)[strcspn((char *)novo, "\n")] = '\0';
  
    printf("Idade: ");
    scanf("%d", (int *)(novo + MAX_NOME));
   
    while (getchar() != '\n');
    printf("Email: ");
    fgets((char *)(novo + MAX_NOME + sizeof(int)), MAX_EMAIL + 1, stdin);



    *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL) = NULL; // Inicializa proximo
    *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = NULL; // Inicializa anterior

    // Inserção ordenada
    void *head = *(void **)(pBuffer + sizeof(int));//ponteiro para primeiro endereço
    void *pas = NULL; //ponteiro para anterior
    void *current = head; //ponteiro para atual

    while (current != NULL && strcmp((char *)current, (char *)novo) < 0) {
        pas = current;
        current = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
    }

    if (pas == NULL) { // Inserção no início
        *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL) = current;
        head = novo;
        if (current != NULL) {
            *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = novo;
        }
    } else { // Inserção no meio ou fim
        *(void **)(pas + MAX_NOME + sizeof(int) + MAX_EMAIL) = novo;  //ponteiro proximo de pas aponta para novo
        *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = pas; //ponteiro anterior do novo aponta para pas
        *(void **)(novo + MAX_NOME + sizeof(int) + MAX_EMAIL) = current;   //ponteiro proximo do novo aponta para current
        if (current != NULL) {
            *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = novo; //ponteiro anterior de current aponta para novo
        }
    }
    *(void **)(pBuffer + sizeof(int)) = head; //
    printf("Pessoa adicionada com sucesso!\n");
}

void removerPessoa(void *pBuffer) {
    printf("Nome da pessoa a remover: ");
    while(getchar()!='\n');
    fgets((char *)(pBuffer + sizeof(int) + sizeof(void *)), MAX_NOME, stdin);
    ((char *)pBuffer + sizeof(int) + sizeof(void *))[strcspn((char *)pBuffer + sizeof(int) + sizeof(void *), "\n")] = '\0';

    void *current = *(void **)(pBuffer + sizeof(int));

    while (current != NULL && strcmp((char *)current, (char *)(pBuffer + sizeof(int) + sizeof(void *))) != 0) {
        current = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
    }

    if (current == NULL) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    void *prev = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *));
    void *next = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);

    if (prev != NULL) {
        *(void **)(prev + MAX_NOME + sizeof(int) + MAX_EMAIL) = next;
    }else{
        *(void **)(pBuffer + sizeof(int)) = next;
        prev=NULL;
    }

    if (next != NULL) {
        *(void **)(next + MAX_NOME + sizeof(int) + MAX_EMAIL + sizeof(void *)) = prev;
    }

    free(current);
    printf("Pessoa removida com sucesso!\n");
}

void buscarPessoa(void *pBuffer) {
    printf("Nome da pessoa a buscar: ");
    while (getchar() != '\n');
    fgets((char *)(pBuffer + sizeof(int) + sizeof(void *)), MAX_NOME, stdin);
     ((char *)pBuffer + sizeof(int) + sizeof(void *))[strcspn((char *)pBuffer + sizeof(int) + sizeof(void *), "\n")] = '\0';

    void *current = *(void **)(pBuffer + sizeof(int));

    while (current != NULL && strcmp((char *)current, (char *)(pBuffer + sizeof(int) + sizeof(void *))) != 0) {
        current = *(void **)(current + MAX_NOME + sizeof(int) + MAX_EMAIL);
    }

    if (current == NULL) {
        printf("Pessoa nao encontrada!\n");
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
