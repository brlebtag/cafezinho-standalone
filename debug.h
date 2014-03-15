#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "arvore_abstrata.h"
#include "MaquinaVirtual.h"
#include <iostream>

using namespace std;

void debug_arvore(No* no, int nivel);
void imprime_nivel(int nivel);
void debug_codigo(MaquinaVirtual &vm);
void imprime_instrucao(MaquinaVirtual &vm, Instrucao * instrucao);
string nome_reg(MaquinaVirtual &vm, CelulaMemoria &celula);
string nome_tipo_cast(TipoVariavel::TipoVariavel tipo);

#endif