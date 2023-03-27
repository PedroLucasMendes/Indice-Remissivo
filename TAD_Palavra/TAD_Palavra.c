#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista.h"
#include "ddinamico.h"
#include "TAD_Palavra.h"
#include "math.h"

//Estruturas
struct stats
{
    int pagina;
    double ocorrencia;
    double tf;
    double tf_idf;
};

struct NoPalavra
{
    char palavra[48];
    double idf ;
    
    TListaSE *listaDePaginas;
};

struct palavra{
    char palavra[48];
    int pagina;
};

struct pagina{
    int TNP; // Total de palavras na página
};

typedef struct pagina TPagina;

struct Process{
    TDDinamico *dicioPala;
    TListaSE *lista;

    int* qtdPalavra;
    int ocupacao;
    int tamanho;
};

//Funçoes Especialistas
void imprimirPalavra(void *ocorre){
    TStats *stats = ocorre;
    printf("Pagina: %d\n", stats->pagina);
    return;
}

void imprimirListaOrd(void *no){
    TNoPalavra *pala = no;
    printf("%s\n",pala->palavra);
}
void imprimirTnoPalavra(void *no){
    TNoPalavra *pala = no;
    printf("%s\n",pala->palavra);
    imprimirLSE(pala->listaDePaginas);
}

int CompararPagina(void* ocorre, void* ocorre2){
    TStats *stats1 = ocorre;
    TStats *stats2 = ocorre2;
    return (stats1->pagina - stats2->pagina);
}

int CompararPalavra(void* ocorre, void* ocorre2){
    TNoPalavra* stats1 = ocorre;
    TNoPalavra* stats2 = ocorre2;
    return (strcmp(stats2->palavra, stats1->palavra));
}

int CompararTF_IDF(void* tf_idf1 , void* tf_idf2){
    TStats *stats1 = tf_idf1;
    TStats *stats2 = tf_idf2;

    return ((stats1->tf_idf*1000000) - (stats2->tf_idf*1000000));
}

//Criação das estruturas
TProcess* CriarProcess(){
    TProcess *processamento = malloc(sizeof(TProcess));
    processamento->dicioPala = criar_DD(3);
    processamento->lista = criarLSE(imprimirListaOrd, CompararPalavra); //Listra de TNoPalavra;
    processamento->ocupacao = 0;
    processamento->tamanho = 10;
    processamento->qtdPalavra = malloc(sizeof(int) * 10);
    return processamento;
}

TNoPalavra* CriarNoPalavra(char palavra[]){
    TNoPalavra *pala = malloc(sizeof(TNoPalavra));

    strcpy(pala->palavra, palavra);
    pala->listaDePaginas = criarLSE(imprimirPalavra, CompararPagina);
    pala->idf = 0;
    

    return pala;
}

TNoPalavra* CriarNoPalavraLSE(char palavra[]){
    TNoPalavra *pala = malloc(sizeof(TNoPalavra));

    strcpy(pala->palavra, palavra);
    pala->listaDePaginas = criarLSE(imprimirPalavra, CompararTF_IDF);
    pala->idf = 0;
    

    return pala;
}

TPalavra* CriarPalavra(char palavra[], int pagina){
    TPalavra *Tpalavra = malloc(sizeof(TPalavra));
    strcpy(Tpalavra->palavra, palavra);
    Tpalavra->pagina = pagina;

    return Tpalavra;
}

TStats* CriarOcorrencia(int pagina){
    TStats *stats = malloc(sizeof(TStats));
    stats->pagina = pagina;
    stats->ocorrencia = 1;
    stats->tf = 0.0;
    stats->tf_idf = 0.0;
    return stats;
}

TPagina* CriarTPagina(int pagina, int TNP){
    TPagina* pagina1 = malloc(sizeof(TPagina));

    pagina1->TNP = TNP; // TOtal numero de palavra na pagina

    return pagina1;    
}

double log2(double x)
{
    return log(x)/log(2);
}

TPagina* ResetPagina(TPagina* pagina, int novaPagina, TProcess* process){
    if(process->ocupacao == process->tamanho){
        process->qtdPalavra = realloc(process->qtdPalavra, sizeof(int) * process->tamanho*2);
        process->tamanho = process->tamanho * 2;
    }
    process->qtdPalavra[novaPagina-1] = pagina->TNP;
    process->ocupacao++;
    pagina->TNP = 0;
}
TPagina* AddPalavra(TPagina* pagina, int numero_palavra){
    pagina->TNP = numero_palavra;
}


static int AplicaPeso(char palavra[]){
    int acom = 0;
    int tam = strlen(palavra);
    for (int i = 0; i < tam; i++)
    {
        acom = acom + (i+1 * palavra[i]);
    }
    
    return acom;
}

void ImprimirPalavraOrdenada(TProcess *processo, char palavra[]){
    TNoPalavra *palavraEncontrada = buscarConteudoLSE(processo->lista, palavra);
    if(palavraEncontrada){
        imprimirTnoPalavra(palavraEncontrada);
    }else{
        printf("Não encontramos essa palavra\n");
    }
}   

void ImprimirOrd(TProcess* Processo){
    int tam = tamanhoLSE(Processo->lista);
    for(int i = 1; i <= tam; i++){
        TNoPalavra *palavrao = acessarLSE(Processo->lista, i);
        printf("Palavra: %s \n", palavrao->palavra);
        imprimirLSE(palavrao->listaDePaginas);
    }
    //DashBoardDD(Processo->dicioPala);
}

//Funções usando DD
void InserirPalavraDD(TPalavra* pala, TProcess *dicio){
    int peso = AplicaPeso(pala->palavra);
    TNoPalavra *NOpalavra = buscar_DD(dicio->dicioPala, peso);
    if(NOpalavra){
        TStats *stats =  buscarConteudoLSE(NOpalavra->listaDePaginas, &pala->pagina);
        if(stats){
            stats->ocorrencia++;
        }else{
            TStats *novoStats = CriarOcorrencia(pala->pagina);
            inserirInicioLSE(NOpalavra->listaDePaginas, novoStats);
        }
    }else{
        TNoPalavra *novaPalavra = CriarNoPalavra(pala->palavra);
        TStats *novoStats = CriarOcorrencia(pala->pagina);
        inserirInicioLSE(novaPalavra->listaDePaginas, novoStats);
        inserir_DD(dicio->dicioPala, peso, novaPalavra);
        //insere na lista encadeada para impressão
        TNoPalavra *PalavraLSE = CriarNoPalavraLSE(pala->palavra);
        inserirConteudoLSE(dicio->lista, PalavraLSE); // inserir por conteudo na lse, em ordem alfabetica
    }
}
void* BuscarPalavraDD(char palavra[], TProcess *dicio){
    int peso = AplicaPeso(palavra);
    TNoPalavra *palavra2 = buscar_DD(dicio->dicioPala, peso);
    return palavra2->listaDePaginas;
}

void Top5(TProcess *dicio){
    TListaSE* l = dicio->lista;
    TListaSE* l2;
    TNoPalavra* carga;
    TStats* CargaStats;
    int tamanho = tamanhoLSE(l); // acha tamanho da lista final(do top5)
    int tamanho2;
    for (int i = 1; i <= tamanho; i++)//percorre todas as palavras armazenadas na lista final
    {
        carga = acessarLSE(l, i);//retorna elemento TNoPalavra
        l2 = BuscarPalavraDD(carga->palavra,dicio);//busca palavra no dicioDDinamico, retorna um TListaSE
        tamanho2 = tamanhoLSE(l2); // percorrer todas as ocorrencias da palavra i, no dicionario dinamico
        for (int j = 1; j <= tamanho2; j++)
        {
            CargaStats = acessarLSE(l2, j);
            inserirConteudoLSE(carga->listaDePaginas,CargaStats);
        }
        while(tamanho2 > 5)//remove da pos 6 até o final
        {
            removerFinalLSE(carga->listaDePaginas);
            tamanho2 = tamanhoLSE(carga->listaDePaginas);
        }
        
    }
    
      
}

void TF(TProcess* dicio){
    TListaSE* l = dicio->lista;
    TListaSE* l2;
    TNoPalavra* carga;
    TStats* CargaStats;
    int tamanho = tamanhoLSE(l); // acha tamanho da lista final(do top5)
    int tamanho2;
    for (int i = 1; i <= tamanho; i++)//percorre todas as palavras armazenadas na lista final
    {
        carga = acessarLSE(l, i);//retorna elemento TNoPalavra
        l2 = BuscarPalavraDD(carga->palavra,dicio);//busca palavra no dicioDDinamico, retorna um TListaSE
        tamanho2 = tamanhoLSE(l2); // percorrer todas as ocorrencias da palavra i, no dicionario dinamico
        for (int j = 1; j <= tamanho2; j++)
        {
            CargaStats = acessarLSE(l2, j);
            CargaStats->tf = (CargaStats->ocorrencia)/(dicio->qtdPalavra[CargaStats->pagina]);
        }
    }

}

void IDF(TProcess* dicio){

    int tamanho = tamanhoLSE(dicio->lista);
    for(int i = 1; i<=tamanho;i++){

        TNoPalavra* palavra = acessarLSE(dicio->lista,i);
        TListaSE* palavra2 = BuscarPalavraDD(palavra->palavra,dicio);
        int tamanho2 = tamanhoLSE(palavra2);
        int tamanhoVetor = dicio->ocupacao-1;
        double idf = (double)tamanhoVetor/(double)(tamanho2+1);
        double idf2 = log2(idf);
        palavra->idf = idf2;
    }
}

void TF_IDF(TProcess* dicio){
    int tamanho = tamanhoLSE(dicio->lista);
    for(int i = 1; i<tamanho;i++){
        int tamanho = dicio->ocupacao-1;
        TNoPalavra* palavra = acessarLSE(dicio->lista,i);
        TListaSE* palavra2 = BuscarPalavraDD(palavra->palavra,dicio);
        int tamanho2 = tamanhoLSE(palavra2);
        for(int j = 1; j<tamanho2;j++){
            TStats *stats = acessarLSE(palavra2, j);
            double tfidf = stats->tf * palavra->idf;
            stats->tf_idf = tfidf;
        }
    }
}

void ReHash(TProcess *dicio){
    dicio->dicioPala = faz_rehashing(dicio->dicioPala, 0);
}
