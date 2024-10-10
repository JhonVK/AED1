#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void criarCache(int nsets, int bsize, int assoc, char subst, int flagOut, char *arquivoEntrada) {
    FILE *arquivo;
    unsigned char buffer[4];
    unsigned int endereco=0, tag=0, indice=0, hit=0, acessos=0, blocoSubstituir=0;
    unsigned int missConflito=0, missCapacidade=0, randBloco, missCompulsorio=0;
    unsigned int cache_val[nsets][assoc], cache_tag[nsets][assoc], fifo_time[nsets][assoc], lru_acessos[nsets][assoc];

    arquivo=fopen(arquivoEntrada, "rb");
    if (arquivo==NULL) {
        printf("Erro ao ler arquivo\n");
        exit(1);
    }

    // Zerando totalmente nossa cache
    for (int i=0; i<nsets; i++) {
        for (int j=0; j<assoc; j++) {
            cache_val[i][j]=0;
            cache_tag[i][j]=-1;
            fifo_time[i][j]=0;
            lru_acessos[i][j]=0;
        }
    }

    int n_bits_offset =log2(bsize);
    int n_bits_indice =log2(nsets);
    srand(time(NULL)); // Isso gera uma seed nova

    while (fread(buffer, sizeof(unsigned char), 4, arquivo) == 4) {
        endereco = buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3];
        tag = endereco >> (n_bits_offset + n_bits_indice);
        indice = (endereco >> n_bits_offset) & ((unsigned int)pow(2, n_bits_indice) - 1);
        acessos++;

        bool verifiHit=false, cacheEspaco=false, verifiMiss=false;

        for (int i = 0; i < assoc; i++) {
            if (cache_val[indice][i]==1 && cache_tag[indice][i]==tag) {
                hit++;
                verifiHit = true;
                lru_acessos[indice][i]=acessos;
                break;
            }
        }

        if (!verifiHit) { // (MISS)
            // (miss compulsorio)
            for (int i=0; i<assoc; i++) {
                if (cache_val[indice][i]==0) {
                    cache_val[indice][i]=1;
                    cache_tag[indice][i]=tag;
                    missCompulsorio++;
                    verifiMiss=true;
                    fifo_time[indice][i] = acessos;
                    lru_acessos[indice][i] = acessos;
                    break;
                }
            }

            // Aqui temos duas opções, Miss capacidade ou Miss conflito
            if (!verifiMiss) {
                for (int i=0; i<nsets; i++) {
                    for (int j=0; j<assoc; j++) {
                        if (cache_val[i][j]==0) {
                            cacheEspaco=true;
                            break;
                        }
                    }
                    if(cacheEspaco)break;
                }

                if(!cacheEspaco){
                    missCapacidade++;
                }else{
                    missConflito++;
                }

                if(subst=='R'){
                    randBloco = rand() % assoc;
                    cache_val[indice][randBloco]=1;
                    cache_tag[indice][randBloco]=tag;
                }else if(subst=='F'){
                    unsigned int min_tempo = fifo_time[indice][0];
                    blocoSubstituir=0;
					for (int i=1; i<assoc; i++){
                        if(fifo_time[indice][i]<min_tempo){
                            min_tempo=fifo_time[indice][i];
                            blocoSubstituir=i;
                        }
                    }
                    cache_val[indice][blocoSubstituir] = 1;
                    cache_tag[indice][blocoSubstituir] = tag;
                    fifo_time[indice][blocoSubstituir] = acessos;
				}else if(subst=='L'){
                    unsigned int menorAcesso = __INT_MAX__;
                    blocoSubstituir = 0;
					for (int i=0; i<assoc; i++){
                        if(lru_acessos[indice][i]<menorAcesso){
                            menorAcesso=lru_acessos[indice][i];
                            blocoSubstituir=i;
                        }
                    }
                    cache_val[indice][blocoSubstituir] = 1;
                    cache_tag[indice][blocoSubstituir] = tag;
                    lru_acessos[indice][blocoSubstituir]=acessos;

                }
            }
        }
    }

    if(flagOut == 1) {
        printf("%d %.4f %.4f %.2f %.2f %.2f\n", acessos, (float)hit/acessos, (float)(acessos-hit)/acessos, (float)missCompulsorio/(acessos-hit), (float)missCapacidade/(acessos-hit), (float)missConflito/(acessos-hit));
    }else{
        printf("Total de acessos: %d\nTaxa de hit: %f\nTaxa de miss: %f\nTaxa de miss compulsorio: %f\nTaxa de miss de capacidade: %f\nTaxa de miss de conflito: %f\n", acessos, (float)hit/acessos, (float)(acessos-hit)/acessos, (float)missCompulsorio/(acessos-hit), (float)missCapacidade/(acessos-hit), (float)missConflito/(acessos-hit)); 
    }

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
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

    criarCache(nsets, bsize, assoc, subst, flagOut, arquivoEntrada);

    return 0;
}