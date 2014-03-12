#ifndef __REFERENCIA_H__
#define __REFERENCIA_H__

#include "arvore_abstrata.h"

class Referencia
{
public:
	Referencia(No* origem, int profundidade = 0, int offset = 0, bool parametro = false, bool vetor = false);
	~Referencia();
	int profundidade;
	int offset;
	bool parametro;
	bool vetor;
	No* origem;
};

#endif