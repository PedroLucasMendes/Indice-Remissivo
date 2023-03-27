#include "destatico.h"

typedef unsigned char TStopword;

TStopword* criar_sw(unsigned char palavra[]);

void imprimir_sw(TStopword* p);

int comparar_SW(void* sw1, void* sw2);


TDEstatico* cria_dicionario_sw(const char* arq);