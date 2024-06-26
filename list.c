#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int age;
    char name[40];
    int income;
}Data;

typedef struct Node{
    struct Node *pNext;
    Data info;
}Node;


typedef struct
{
    Node *pFirst;
}List;

Node *new(Data data){
    Node *newNode=(Node *)malloc(sizeof(Node));
    newNode->info.age=data.age;
    strcpy(newNode->info.name, data.name);
    newNode->info.income=data.income;
    newNode->pNext=NULL;
    return newNode;
}

Data search(List *lista, int indice){
    Node *atual= lista->pFirst;
    for(int i=0; atual!=NULL && i<indice; i++){
        atual=atual->pNext;
    }
    if (atual != NULL) {
        return (atual->info);
    } else {
        Data emptyData = { 0, "", 0 };
        return emptyData;
    }

}

bool push(List *pLista, Node *pNodo, unsigned int nIndex){
    Node *pAtual, *pAnterior;
    unsigned int nPos;

    if(pLista->pFirst==NULL && nIndex!=0){  
        return false;
    }else if(pLista->pFirst==NULL && nIndex==0){
        pLista->pFirst=pNodo;
        pNodo->pNext=NULL;
        return true;
    }else if(nIndex==0){
        pNodo->pNext=pLista->pFirst;
        pLista->pFirst=pNodo;
        return true;
    }
    pAtual=pLista->pFirst;

    while (pAtual != NULL && nPos < nIndex) {
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
        nPos++;
    }

    if(!pAtual){
        return false;
    }

    pNodo->pNext = pAtual;

    if (pAnterior != NULL) {
        pAnterior->pNext = pNodo;
    } else {
        pLista->pFirst = pNodo; 
    }
    return true;
}   


int main(){
   Data data;

   List myList;
   int n=0, index;
  

   while(n!=5){
    printf("Digite o que deseja fazer: 1- Adicionar elemento a lista, 5-Sair do Programa\n");
    scanf("%d", &n);

   switch(n){
   case 1:
    printf("Em qual index voce desejar colocar o elemento na lista?\n");
    scanf("%d", &index);

    printf("Digite informacoes do nodo (idade, nome e salario)\n");
    scanf("%d", &data.age);
    while (getchar() != '\n');
    fgets(data.name, sizeof(data.name), stdin);
   
    scanf("%d", &data.income);

  

    Node *nodo=new(data);

    bool result=push(&myList, nodo, index);

    if(result==true){
        printf("O nodo foi adicionado com sucesso\n");
    }else{
        printf("ERRO INDEX\n");
    }
    break;

   case 2:
    printf("Em qual index voce deseja pesquisar?\n");
    scanf("%d", &index);
    Data data2=search(&myList, index);
    printf("%d %d %s\n", data2.age, data2.name, data2.income);
    break;
   }
   
   }


    return 0;
}