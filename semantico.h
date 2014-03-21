#ifndef __SEMANTICO_H__
#define __SEMANTICO_H__

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include "arvore_abstrata.h"
#include "simbolo.h"
#include <sstream>


extern int erro_compilador;

using namespace std;
using namespace TipoVariavel;
using namespace Operador;
using namespace TipoNo;

typedef std::stack < Simbolo* > PilhaSimbolo;
typedef unordered_map<std::string, PilhaSimbolo*> TabelaSimbolo;
typedef TabelaSimbolo::iterator IteradorTabelaSimbolo;

#ifndef __LISTA__
#define __LISTA__
typedef std::vector<NInstrucao*> ListaInstrucao;
typedef std::vector<NExpressao*> ListaExpressao;
typedef std::vector<NDeclaracaoVariavel*> ListaVariavel;
#endif

#ifndef __ITERADORES__
#define __ITERADORES__
typedef std::vector<NInstrucao*>::iterator IteradorInstrucao;
typedef std::vector<NExpressao*>::iterator IteradorExpressao;
typedef std::vector<NDeclaracaoVariavel*>::iterator IteradorVariavel;
#endif

typedef vector<IteradorTabelaSimbolo> Remover;
typedef vector<IteradorTabelaSimbolo>::iterator IteratorRemover;

//semantico.cpp
IteradorTabelaSimbolo analise_semantica(TabelaSimbolo &tabela, No* no, int profundidade, No* funcao=0);

//checa_tipo.cpp
TipoVariavel::TipoVariavel checar_tipo(TabelaSimbolo &tabela, No* no);
//checa_tipo.cpp
bool checa_tipo_init(TabelaSimbolo &tabela, No* no, TipoVariavel::TipoVariavel tipo);

//checa_vetor_dimensao.cpp
bool checa_vetor_dimensao(bool parametro, NDeclVarVetorial *var);
//checa_chamada.cpp
No* ultimo_parametro(TabelaSimbolo &tabela, No * no);
//checa_chamada.cpp
bool checar_chamada(TabelaSimbolo &tabela, No* parametro, No* argumento);

//nome.cpp
string tipo_no(No * no);
//nome.cpp
string nome_tipo(TipoVariavel::TipoVariavel tipo);


#ifndef __CHECA_NO__
#define __CHECA_NO__
#define CHECA_NO(no, IDENT) no->tipoNo() == IDENT
#define NCHECA_NO(no, IDENT) no->tipoNo() != IDENT
#endif 

#endif