#include "destatico.h"
#include "stdlib.h"
#include "stdio.h"

/*struct estatistica{
  int num_cmp; //comparações
  int num_bsc; //buscas
};*/

struct destatico{
    void* *entradas;

    int tamanho;
    int ocupacao;

    TCompararDE comparar;

    int num_cmp;
    int num_bsc;
};

TDEstatico* criar_DE(int tam, TCompararDE comparar){
    TDEstatico *de = malloc(sizeof(TDEstatico));
    de->tamanho = tam;
    de->ocupacao = 0;
    de->entradas = malloc(sizeof(void)*de->tamanho);
    de->comparar = comparar;

    return de;
}

void* buscar_DE(TDEstatico* de, void* chave){
  
  de->num_bsc++;
  
  void* entrada=NULL;
  int inicio=0;
  int fim = de->ocupacao-1;
  short encontrou = 0; // falso
  while( (!encontrou) && (inicio<=fim)){
      int meio = (inicio+fim)/2;
      int status = de->comparar(de->entradas[meio],chave);
      if (status == 0){
        de->num_cmp+=1;
        encontrou=1; //verdade
        entrada = de->entradas[meio];
      }else if(status > 0){
        de->num_cmp+=2;
        fim = meio-1;
      }else{
        de->num_cmp+=3;
        inicio = meio+1;
      }
  }
  return entrada;
}

int ocupacao_DE(TDEstatico* de){
    return de->ocupacao;
}

void carga_DE(TDEstatico* de, void* info){
    de->entradas[de->ocupacao] = info;
    de->ocupacao++;
}

void dashbord_DE(TDEstatico *de){
  printf("Num buscas: %d\n",de->num_bsc);
  printf("Num comparacoes: %d\n",de->num_cmp);
  printf("Media comparacoes por buscas: %.2lf\n", (double) de->num_cmp/de->num_bsc);
  printf("ocupação: %d\n", de->ocupacao);
}

