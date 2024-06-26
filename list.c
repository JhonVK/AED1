#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    Node *pNext;
    Data info;
}Node;

typedef struct{
    int age;
    char name[40];
    int income;
}Data;

typedef struct
{
    Node *pFirst;
}List;

bool push(List *pLista, Node *pNodo, unsigned int nIndex){
    Node *pAtual, *pAnterior;
    int nPos=0;

    if(pLista->pFirst==NULL && nIndex!=0){  
        return false; //index invalido
    }else if(pLista->pFirst==NULL && nIndex==0){
        pLista->pFirst=pNodo;
        pLista->pFirst->pNext=NULL;
        return true;
    }else if(nIndex==0){
        pNodo->pNext=pLista->pFirst;
        pLista->pFirst=pNodo;
        return true;
    }
    pAtual=pLista->pFirst;
    for(nPos; nPos<=nIndex && pAtual != NULL; nPos++){
        pAnterior=pAtual;
        pAtual=pAtual->pNext;
    }
    if(!pAtual){
        return false; //index nao existe
    }
    pNodo->pNext=pAtual;
    pAnterior->pNext=pNodo;
    return true;
}   


int main(){
   
    return 0;
}