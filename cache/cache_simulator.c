#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void leituraDados(int *argc, char ***argv){ //argv aqui é o endereço do ponteiro que aponta para o primeiro elemento do vetor,
											//*argv é o ponteiro que aponta para o primeiro elemento do vetor
											//**argv é o valor do vetor
    char string[50];
    char *token;
    

    fgets(string, 50, stdin);

	int tamanho = strlen(string); // removendo o \n que o fgets concatena no final da leitura
    if(tamanho>0 && string[tamanho-1]=='\n') {
        string[tamanho-1] = '\0';
    }
	
    token = strtok(string, " ");

    while(token!=NULL){
        *argv = realloc(*argv, sizeof(char*)*((*argc) + 1));
        (*argv)[*argc]=malloc(sizeof(char)*50);
        strcpy((*argv)[*argc], token);
        token=strtok(NULL, " ");
        (*argc)++;
    }
}

void criarCache(int nsets, int bsize, int assoc, char *subst, int flagOut, char *arquivoEntrada){
	FILE *arquivo;
	unsigned int buffer;

	arquivo=fopen(arquivoEntrada, "rb");
	
	if(arquivo==NULL){
		printf("erro ao ler arquivo");
		exit(1);
	}
	while (fread(&buffer, sizeof(unsigned int), 1, arquivo)) { //unsigned int tem 4bytes == 32 bits
        printf("Endereco: 0x%08X\n", buffer);

    }

    fclose(arquivo);
}

int main(int argc, char *argv[]){//argv é um vetor de ponteiros
	argc=0;
	leituraDados(&argc, &argv);
	if (argc != 7){
		printf("Numero de argumentos incorreto. Utilize:\n");
		printf("./cache_simulator <nsets> <bsize> <assoc> <substituicao> <flag_saida> arquivo_de_entrada\n");//./cache simulator 10 10 1 rand 1 bin_100.bin
		exit(EXIT_FAILURE);
	}

	int nsets = atoi(argv[1]);
	int bsize = atoi(argv[2]);
	int assoc = atoi(argv[3]);
	char *subst = argv[4];
	int flagOut = atoi(argv[5]);
	char *arquivoEntrada = argv[6];

	printf("nsets = %d\n", nsets);
	printf("bsize = %d\n", bsize);
	printf("assoc = %d\n", assoc);
	printf("subst = %s\n", subst);
	printf("flagOut = %d\n", flagOut);
	printf("arquivo = %s\n", arquivoEntrada);

	criarCache(nsets, bsize, assoc, subst, flagOut, arquivoEntrada);

	free(argv);

	return 0;
}


