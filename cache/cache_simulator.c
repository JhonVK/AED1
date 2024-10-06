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
    unsigned int endereco=0, tag=0, indice=0, hitTemp=0, hit=0; // uns int tem 4 bytes= 32 bits cache_simulator 256 4 1 R 1 bin_100.bin

    arquivo = fopen(arquivoEntrada, "rb");

    if(arquivo == NULL){
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

    while(fread(buffer, sizeof(unsigned char), 4, arquivo) == 4) { // uns char tem 8 bits, 8*4= 32 bits
    	endereco= buffer[0]<<24 | buffer[1]<<16 | buffer[2]<<8 | buffer[3];// por algum motivo se lermos direto, (32 bits de uma vez) o endereço fica em little endian.Por isso li byte por byte e desloquei eles para big endian
		tag = endereco>>(n_bits_offset + n_bits_indice);
		indice = (endereco >> n_bits_offset) & ((unsigned int)pow(2, n_bits_indice)-1); 
		printf("Tag: %d, Indice: %d\n", tag, indice);


		for(int i=0; i<assoc; i++){
			if(cache_val[indice][assoc]==1 && cache_tag[indice][assoc]==tag){
				hitTemp=1;
			}
		}
		if(hitTemp=0){//(MISS)
			if(*subst=='R'){
				int randBloco=rand()%assoc;
				cache_val[indice][randBloco]=1;
				cache_tag[indice][randBloco]=tag;
			}
		}else{
			hit+=hitTemp;
			hitTemp=0;
		}
		printf("Total de hits: %d", hit);
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


