#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char nome[50];
    int idade;
} registro;

typedef struct no {
    registro reg;
    struct no *pEsq, *pDir;
} no;

void pesquisa(registro *x, no *p){
    if (p == NULL) {
        printf("Registro nao encontrado\n");
        return;
    }
    if (x->idade < p->reg.idade) {
        pesquisa(x, p->pEsq);
    } else if (x->idade > p->reg.idade) {
        pesquisa(x, p->pDir);
    } else {
        *x = p->reg;
    }
}
void retira(registro x, no **p){
    no *auxi;
    if(*p==NULL){
        printf("Arvore vazia");
        return;
    }
    if(x.idade < (*p)->reg.idade){
        retira(x, &((*p)->pEsq));
        return;
    }
    if(x.idade > (*p)->reg.idade){
        retira(x, &((*p)->pDir));
        return;
    }
    if((*p)->pDir == NULL){
        aux=*p;
        *p=(*p)->pEsq;
        free(aux);
        return;
    }
    if((*p)->pEsq != NULL){
        antecessor(*p, &(*p)->pEsq)
        return;
    }else{
        aux=*p;
        *p=(*p)->pDir;
        free(aux);

    }
}



void insere(registro *x, no **p) {
    if (*p == NULL) {
        *p = (no*)malloc(sizeof(no));
        (*p)->reg = *x;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
        return;
    }
    if (x->idade < (*p)->reg.idade) {
        insere(x, &((*p)->pEsq));
    } else if (x->idade > (*p)->reg.idade) {
        insere(x, &((*p)->pDir));
    } else {
        printf("Registro ja existe na arvore\n");
    }
}

int main() {
    registro x;
    x.idade = 20;
    strcpy(x.nome, "arturdoveneno");

    no *ponteiro = NULL; 
    insere(&x, &ponteiro);

    registro y;
    y.idade = 30;
    strcpy(y.nome, "joaodoteste");
    insere(&y, &ponteiro);

    registro z;
    z.idade = 10;
    strcpy(z.nome, "mariadoteste");
    insere(&z, &ponteiro);


    registro search;
    search.idade = 10;
    pesquisa(&search, ponteiro);
    printf("Resultado da pesquisa: %s\n", search.nome);

    search.idade = 30;
    pesquisa(&search, ponteiro);
    printf("Resultado da pesquisa: %s\n", search.nome);

    search.idade = 20;
    pesquisa(&search, ponteiro);
    printf("Resultado da pesquisa: %s\n", search.nome);

    return 0;
}
