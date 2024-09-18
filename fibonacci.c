//Joao vitor kauer schuck
//codigo feito sem nenhum auxilio externo
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool fibonacci(int entrada, int numeroT){
    int primeiro=0, segundo=1, terceiro;
    bool saida=false; //na teoria um bool em C ja é inicializado com false, entao o false nao seria necessario aqui

    printf("%d\n", primeiro);
    printf("%d\n", segundo);
    if(entrada==primeiro || entrada==segundo){
        saida=true;
    }
    for(int i=numeroT-2; i>0; i--){
        terceiro=primeiro+segundo;
        if(terceiro==entrada){
            saida=true;
        }
        primeiro=segundo;
        segundo=terceiro;
        printf("%d\n", terceiro);
    }
    return saida;
}

int main() {
    int entrada, numeroT;
    printf("Digite quantos numeros da sequencia de fibonacci voce deseja imprimir: ");
    scanf("%d", &numeroT);
    printf("Digite o numero que deseja verificar se faz parte da sequencia: ");
    scanf("%d", &entrada);
    bool saida=fibonacci(entrada, numeroT);
    if(saida){
        printf("O numero %d esta na sequecia!!", entrada);
    }else{
        printf("O numero %d nao esta na sequecia!!", entrada);
    }
    return 0;
}