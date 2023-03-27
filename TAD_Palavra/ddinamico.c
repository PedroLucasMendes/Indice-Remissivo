#include "stdio.h"
#include "assert.h"
#include "stdlib.h"
#include "lista.h"
#include "ddinamico.h"
#include "math.h"

struct ddinamico{
  // dados
  int tamanho;
  int nro_elementos;
  //Criação das estruturas
  TListaSE* *entradas;
  // estatistica

  int nro_remocao;
  int nro_busca;
  int nro_insercao;
  long int nro_cmps_por_rmc;
  long int nro_cmps_por_bsc;
};

typedef struct entrada{
  int chave;
  void* info;
}TEntradaDD;

TEntradaDD* criar_entrada_DD(int chave, void* info){
  TEntradaDD *e = malloc(sizeof(TEntradaDD));
  e->chave = chave;
  e->info = info;

  return e;
}

int comparaEntradaDD(void* e1, void* e2){//Criação das estruturas
  TEntradaDD *ee1 = e1;
  TEntradaDD *ee2 = e2;

  return (ee1->chave - ee2->chave);

}

static int hashing(TDDinamico* dd, int chave){
  return (chave % dd->tamanho);
}

static int primo_proximo(int num){
  short encontrou = 0;
  while(!encontrou){
    int i=2;
    while( (i<num) && ( (num%i) != 0) ){
      i++;
    }
    if (i==num){
      encontrou=1;
    }else{
      num+=1;
    }
  }
  return num;
}

TDDinamico* criar_DD(int tamanho){
    TDDinamico* dd = malloc(sizeof(TDDinamico));

    dd->tamanho = primo_proximo(tamanho);
    dd->nro_elementos = 0;
    dd->entradas = malloc(sizeof(TListaSE*)*dd->tamanho);
//Criação das estruturas
    for(int i=0;i<dd->tamanho;i++){
      dd->entradas[i] = criarLSE(NULL,comparaEntradaDD);
    }
    dd->nro_busca = dd->nro_remocao = dd->nro_insercao = 0;
    dd->nro_cmps_por_bsc = dd->nro_cmps_por_rmc = 0;

    return dd;

}



//Criação das estruturas
void inserir_DD(TDDinamico *dd, int chave, void* info){
  
  int k = hashing(dd, chave);
  TListaSE *l = dd->entradas[k];
  inserirInicioLSE(l, criar_entrada_DD(chave,info));

  dd->nro_elementos++;
  dd->nro_insercao++;

}

void* buscar_DD(TDDinamico *dd, int chave){

  int k = hashing(dd, chave);
  TListaSE *l = dd->entradas[k];
  TEntradaDD *e = buscarConteudoLSE(l, &chave);
  
  
//Criação das estruturas

  dd->nro_busca++;
  dd->nro_cmps_por_bsc += tamanhoLSE(l);

  return (e?e->info:e);

}

void* remover_DD(TDDinamico *dd, int chave){
  int k = hashing(dd, chave);
  TListaSE *l = dd->entradas[k];
  
  TEntradaDD* e = removerConteudoLSE(l, &chave);

  void* info = NULL;
  if(e != NULL){
    info = e->info;
  
    free(e);
  }
  dd->nro_remocao++;
  dd->nro_cmps_por_rmc += tamanhoLSE(l);

  return info;
}


void destruirDD(TDDinamico *dd){

  for (int i = 0; i < dd->tamanho; i++)
  {
    destruirLSE(&dd->entradas[i]);
  }
  free(dd->entradas);
  free(dd);
}

//Criação das estruturas
TDDinamico* re_hashingDD(TDDinamico *atual){
  TDDinamico *novo;
  int tam_novo = primo_proximo(atual->tamanho+1);
  novo = criar_DD(tam_novo);
  for (int i = 0; i < atual->tamanho; i++)
  {
    TListaSE *lse = atual->entradas[i];
    TEntradaDD *entrada = removerInicioLSE(lse);
    
    while (entrada != NULL)
    {
      inserir_DD(novo, entrada->chave, entrada->info);
      free(entrada);
      entrada = removerInicioLSE(lse);
    }
    
    
  }
  destruirDD(atual);
  return novo;
}

TDDinamico* faz_rehashing(TDDinamico *dd, int quantidade){
  int acum_x = 0;
  int acum_x2 = 0;
  int quant = quantidade;
  //printf("rehashing\n");
  for(int i =0; i < dd->tamanho; i++){
    int tam = tamanhoLSE(dd->entradas[i]);
    if(tam > 0){
      acum_x += tam;
      acum_x2 += tam * tam;
    }
  }
  double Czao =((double)acum_x2/(double)acum_x)-4;
  if(((Czao) > 1 || Czao < 0) && quant < 3){
    quant++;
    dd = re_hashingDD(dd);
    dd = faz_rehashing(dd,quant);
  }
  return dd;
}


void DashBoardDD(TDDinamico *dicio){
  printf("Numero de Busca: %d\n",dicio->nro_busca);
  printf("Numero de comparações por busca: %ld\n",dicio->nro_cmps_por_bsc);
  printf("Numero de comparações por remoção: %ld\n",dicio->nro_cmps_por_rmc);
  printf("Numero de inserção: %d\n",dicio->nro_insercao);
  printf("Numero de remoção: %d\n",dicio->nro_remocao);
  printf("Numero de elementos: %d\n",dicio->nro_elementos);

  double acum = 0;
  double acum1 = 0;
  double acum2 = 0;
  double acum3 = 0;
  double acum4 = 0;
  double acum5 = 0;
  double acum6 = 0;
  double acum7 = 0;

  int j = 0;
  printf("Tamanho do dicio: %d\n",dicio->tamanho);
  for(int i = 0; i < dicio->tamanho; i++){
    j++;
    int tam = tamanhoLSE(dicio->entradas[i]);
    acum += tam;
    
  }
  acum  = acum/j;
  printf("Média de colisões: %lf\n",acum);
}