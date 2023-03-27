#include "destatico.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef unsigned char TStopword;

TStopword* criar_sw(unsigned char palavra[]){
    TStopword* sw = malloc(sizeof(unsigned char)*47);
    strcpy(sw,palavra);
    
    return sw;
}

void imprimir_sw(TStopword* p){
    printf("palavra: %s\n", p);
}

int comparar_SW(void* sw1, void* sw2){
    TStopword* ssw1 = sw1;
    TStopword* ssw2 = sw2;

    //printf("Buscando\n");

    return strcmp(ssw1,ssw2);
}


TDEstatico* cria_dicionario_sw(const char* arq){
    TDEstatico* stopwords = criar_DE(10000,comparar_SW);
    unsigned char palavraAtual[48];
    unsigned char palavraAnterior[48];
    palavraAnterior[0] = '\0';

    FILE *arquivoStopWord = fopen(arq, "r+");
    

    while(fscanf(arquivoStopWord,"%s",palavraAtual) == 1){
        carga_DE(stopwords, criar_sw(palavraAtual));
        strcpy(palavraAnterior, palavraAtual);      
    }   
    fclose(arquivoStopWord);
    return stopwords;
}

/*
int main(int argc, char const *argv[]){
    
    //printf("Buscando...\n");

    
    TDEstatico* dicionarioStw = cria_dicionario_sw(argv[1]);

    unsigned char buscado[48];
    scanf("%s", buscado);
    
    while (strcmp(buscado,"FIM")!=0)
    {
        TStopword* sw = buscar_DE(dicionarioStw, buscado);
        if(sw){
            imprimir_sw(sw); 
        }
        else{
            printf("Não encontrou\n");
    }    
        scanf("%s", buscado);
    }
    dashbord_DE(dicionarioStw);
    
    return 0;
}
*/