#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sSTW.h"
#include "ctype.h"
int VerificaAcentuacao(char palavra[]){
    unsigned int i, k;
    char comAcentos[] = "ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç[]";
    for (k = 0; k < strlen(palavra); k++) {
        for (i = 0; i < strlen(comAcentos); i++) {
            if (palavra[k] == comAcentos[i]) {
                return 1;
            }
        }
    }
    return 0;

}

void Criar_Arquivos(char* arquivos, TDEstatico* Stw){

    FILE *arquivo = fopen(arquivos, "r");
    if(arquivo == NULL){
        printf("ERRO: 0001");
        return;
    }
        
    char palavra[48];
    int i, tam;
    
    while(fscanf(arquivo,"%[^ \t-,.;!?():/<>_—1234567890-'|\n‘’{}=]%*[ \t-,.;!?():/<>_—1234567890-'|\n‘’{}=]",palavra) == 1){

        if(!VerificaAcentuacao(palavra) && strlen(palavra) > 1){
            tam = strlen(palavra);
            for(i=0; i < tam; i++){
                palavra[i] = tolower(palavra[i]);
            }
            if (buscar_DE(Stw, palavra) == NULL)
            {
                printf("%s \n",palavra);
            }  
        }
          
    }
    fclose(arquivo);    
}





int main(int argc, char* argv[]){
    TDEstatico* Stw = cria_dicionario_sw(argv[2]);
    Criar_Arquivos(argv[1], Stw);
}