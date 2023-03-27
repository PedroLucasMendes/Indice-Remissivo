#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "lista.h"
#include "TAD_Palavra.h"
int main(int argc,char *argv[]){

    FILE *arq = fopen(argv[1],"r");
    if(arq == NULL){
        printf("ERRO: 0001");
    }
    TProcess *Processo = CriarProcess();
    unsigned char palavra[48];
    int pagina = 0;
    short flag = 0;
    int numero_palavra = 0;
    TPagina* tipo_pagina = CriarTPagina(pagina, numero_palavra);
    while (fscanf(arq,"%s",palavra) == 1)
    {
        if((strcmp(palavra,"pa") == 0)){
            pagina++;
            ResetPagina(tipo_pagina,pagina,Processo);
            ReHash(Processo);
        }
        else{
            TPalavra *palavrao = CriarPalavra(palavra, pagina);
            InserirPalavraDD(palavrao, Processo);
            numero_palavra++;
            AddPalavra(tipo_pagina, numero_palavra);
        }
    }
    TF(Processo);
    IDF(Processo);
    TF_IDF(Processo);
    Top5(Processo);
    ImprimirOrd(Processo);
    /*
    char palavraBuscar[48];
    printf("Deseja buscar alguma palavra específica?\n");
    scanf("%s",palavraBuscar);
    while(strcmp(palavraBuscar,"FIM") != 0){
        ImprimirPalavraOrdenada(Processo, palavraBuscar);
        printf("Deseja buscar alguma palavra específica?\n");
        scanf("%s",palavraBuscar);
    }
    */
    return 0;

}