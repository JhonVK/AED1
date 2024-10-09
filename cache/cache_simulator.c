#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


void criarCache(int nsets, int bsize, int assoc, char subst, int flagOut, char *arquivoEntrada) {
    FILE *arquivo;
    unsigned char buffer[4];
    unsigned int endereco=0, tag=0, indice=0, hit=0, acessos=0, missConflito=0, missCapacidade=0, randBloco, missCompulsorio=0; // unsigned int tem 4 bytes= 32 bits ./cache_simulator 256 4 1 R 1 bin_100.bin
	unsigned int cache_val[nsets][assoc], cache_tag[nsets][assoc];

    arquivo = fopen(arquivoEntrada, "rb");

    if(arquivo == NULL){
        printf("Erro ao ler arquivo\n");
        exit(1);
    }

	//zerando totalmente nossa cache
	for(int i=0; i<nsets; i++){
		for(int j=0; j<assoc; j++){
			cache_val[i][j]=0;
			cache_tag[i][j]=-1;
		}
	}

    int n_bits_offset = log2(bsize);
    int n_bits_indice = log2(nsets);
    int n_bits_tag = 32 - n_bits_offset - n_bits_indice;

    while(fread(buffer, sizeof(unsigned char), 4, arquivo)==4) { // unsigned char tem 8 bits, 8*4= 32 bits
		srand(time(NULL));//isso gera uma seed nova 
    	endereco=buffer[0]<<24 | buffer[1]<<16 | buffer[2]<<8 | buffer[3];// por algum motivo se lermos direto, (32 bits de uma vez) o endereço fica em little endian.Por isso li byte por byte e desloquei eles para big endian
		tag=endereco>>(n_bits_offset + n_bits_indice);
		indice=(endereco >> n_bits_offset) & ((unsigned int)pow(2, n_bits_indice)-1); 
		acessos++;

		int hitTemp=0;
		int blocoVazio=-1;
		for(int i=0; i<assoc; i++){
			if(cache_val[indice][i]==1 && cache_tag[indice][i]==tag){
				hitTemp=1;
			}
			if(cache_val[indice][i] == 0 && blocoVazio == -1){
                blocoVazio = i;
            }
		}
		if(!hitTemp){//(MISS)
			//(miss compulsorio)
			if(blocoVazio!=-1){
				cache_val[indice][blocoVazio]=1;
				cache_tag[indice][blocoVazio]=tag;
				missCompulsorio++;		
			}else{
			//aqui vemos se a cache esta cheia pra definir se é miss de capacidade ou de conflito.
				int todacacheCheia=1;
				for(int i=0; i<nsets; i++){
					for(int j=0; j<assoc; j++){
						if(cache_val[i][j]==0){
							todacacheCheia=0;
							break;
						}
						if(todacacheCheia==0){
							break;
						}
					}
				}
			if(todacacheCheia){
				missCapacidade++;
			}else{
				missConflito++;
			}
			if(subst=='R'){ 
				randBloco=rand()%assoc;
				cache_val[indice][randBloco]=1;
				cache_tag[indice][randBloco]=tag;
			}
		}
		}else{
			hit++;
		}
    }
	if(flagOut==1){
		printf("%d %.4f %.4f %.4f %.4f %.4f\n", acessos, (float)hit/acessos, (float)(acessos-hit)/acessos, (float)missCompulsorio/(acessos-hit), (float)missCapacidade/(acessos-hit), (float)missConflito/(acessos-hit)); // casting para float
	}else{
		printf("Total de acessos: %d\nTaxa de hit: %f\nTaxa de miss: %f\nTaxa de miss compulsorio: %f\nTaxa de miss de capacidade: %f\nTaxa de miss de conflito: %f\n", acessos, (float)hit/acessos, (float)(acessos-hit)/acessos, (float)missCompulsorio/(acessos-hit), (float)missCapacidade/(acessos-hit), (float)missConflito/(acessos-hit)); 
	}
    fclose(arquivo);
}

int main(int argc, char *argv[]){//argv é um ponteiro para um array de ponteiros (modelo que o prof sugeriu )	
		if(argc != 7){
			printf("Numero de argumentos incorreto. Utilize:\n");
			printf("cache_simulator <nsets> <bsize> <assoc> <substituicao> <flag_saida> arquivo_de_entrada\n");
			exit(EXIT_FAILURE);
		}
		int nsets = atoi(argv[1]);
		int bsize = atoi(argv[2]);
		int assoc = atoi(argv[3]);
		char subst = *argv[4];
		int flagOut = atoi(argv[5]);
		char *arquivoEntrada = argv[6];

		//printf("nsets = %d\n", nsets);
		//printf("bsize = %d\n", bsize);
		//printf("assoc = %d\n", assoc);
		//printf("subst = %c\n", subst);
		//printf("flagOut = %d\n", flagOut);
		//rintf("arquivo = %s\n", arquivoEntrada);

		criarCache(nsets, bsize, assoc, subst, flagOut, arquivoEntrada);


	
	return 0;
}

