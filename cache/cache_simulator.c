#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void criarCache(int nsets, int bsize, int assoc, char *subst, int flagOut, char *arquivoEntrada) {
    FILE *arquivo;
    unsigned char buffer[4];
    unsigned int endereco; // uns int tem 4 bytes= 32 bits

    arquivo = fopen(arquivoEntrada, "rb");

    if (arquivo == NULL) {
        printf("Erro ao ler arquivo\n");
        exit(1);
    }

    int cache_val[nsets][assoc];
    int cache_tag[nsets][assoc];

    int n_bits_offset = log2(bsize);
    int n_bits_indice = log2(nsets);
    int n_bits_tag = 32 - n_bits_offset - n_bits_indice;

    printf("offset: %d\n", n_bits_offset);
    printf("indice: %d\n", n_bits_indice);
    printf("tag: %d\n", n_bits_tag);

    while (fread(buffer, sizeof(unsigned char), 4, arquivo) == 4) { // uns char tem 8 bits, 8*4= 32 bits
    endereco= buffer[0]<<24 | buffer[1]<<16 | buffer[2]<<8 | buffer[3];// por algum motivo se lermos direto, (32 bits de uma vez) o endereço fica invertido, por isso li byte por byte e dps inverti eles

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

