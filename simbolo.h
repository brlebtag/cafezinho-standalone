#ifndef __SIMBOLO_H__
#define __SIMBOLO_H__

#include "arvore_abstrata.h"

class Simbolo
{
public:
	Simbolo(No* no = 0, int profundidade = 0);
	~Simbolo();
	int profundidade;
	No* no;
};

#endif 