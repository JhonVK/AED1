#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void *alocarPessoa(char *nome, int *idade, char *email){
    void *pessoa=malloc(sizeof(nome)*50 + sizeof(idade)+ sizeof(email)*50+ sizeof(void*)*2);
    memcpy(pessoa, nome, 50);
    memcpy(pessoa + 50, idade, sizeof(int));
    memcpy(pessoa + 50 + sizeof(int), email, 50);
    }


int main() {



    return 0;
}
