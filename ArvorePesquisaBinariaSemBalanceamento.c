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
        return;  
    }
    if (x->idade > p->reg.idade) {
        pesquisa(x, p->pDir);
        return; 
    }
    *x = p->reg;
}

void antecessor(no *q, no **r){
    no *aux;
    if((*r)->pDir != NULL){
        antecessor(q, &(*r)->pDir);
        return;
    }
    q->reg= (*r)->reg;
    aux=*r;
    *r=(*r)->pEsq;
    free(aux);
}

void retira(registro x, no **p){
    no *aux;
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
        antecessor(*p, &(*p)->pEsq);
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

    no *raiz = NULL; 

    registro search;

    registro x;
    x.idade = 20;
    strcpy(x.nome, "teste1");
    insere(&x, &raiz);

    registro y;
    y.idade = 300;
    strcpy(y.nome, "teste2");
    insere(&y, &raiz);

    registro z;
    z.idade = 10;
    strcpy(z.nome, "teste3");
    insere(&z, &raiz);


    search.idade = 20;
    pesquisa(&search, raiz);
    printf("Resultado da pesquisa: %s\n", search.nome);
    
    memset(&search, 0, sizeof(search));
    search.idade = 30;
    pesquisa(&search, raiz);
    printf("Resultado da pesquisa: %s\n", search.nome);

    memset(&search, 0, sizeof(search));
    search.idade = 10;
    pesquisa(&search, raiz);
    printf("Resultado da pesquisa: %s\n", search.nome);

    return 0;
}
