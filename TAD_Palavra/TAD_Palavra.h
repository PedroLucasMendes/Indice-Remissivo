typedef struct stats TStats;
typedef struct NoPalavra TNoPalavra;
typedef struct palavra TPalavra;
typedef struct pagina TPagina;
typedef struct Process TProcess;

void imprimirListaOrd(void *no);
void ImprimirOrd(TProcess* Processo);
void imprimirPalavra(void *ocorre);
int CompararPagina(void* ocorre, void* ocorre2);
void ImprimirPalavraOrdenada(TProcess *processo, char palavra[]); 

TPagina* ResetPagina(TPagina* pagina, int novaPagina, TProcess* process);
TProcess* CriarProcess();
TPalavra* CriarPalavra(char palavra[], int pagina);
TPagina* CriarTPagina(int pagina, int TNP);
TPagina* AddPalavra(TPagina* pagina, int numero_palavra);

void InserirPalavraDD(TPalavra* pala, TProcess *dicio);
void* BuscarPalavraDD(char palavra[], TProcess *dicio);
void Top5(TProcess *dicio);
void TF(TProcess* dicio);
void IDF(TProcess* dicio);
void TF_IDF(TProcess* dicio);
void ReHash(TProcess *dicio);

