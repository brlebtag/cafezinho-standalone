#ifndef __GERAR_CODIGO_H__
#define __GERAR_CODIGO_H__

#include "arvore_abstrata.h"
#include "MaquinaVirtual.h"
#include "Instrucao.h"
#include "referencia.h"
#include <unordered_map>
#include <stack>
#include <vector>

using namespace std;

#ifndef __LISTA__
#define __LISTA__
typedef std::vector<NInstrucao*> ListaInstrucao;
typedef std::vector<NExpressao*> ListaExpressao;
typedef std::vector<NDeclaracaoVariavel*> ListaVariavel;
#endif

typedef std::stack<Referencia> PilhaRef;
typedef unordered_map<std::string, PilhaRef> TabelaRef;
typedef unordered_map<std::string, PilhaRef>::iterator IteradorTabelaRef;
typedef std::vector<IteradorTabelaRef> RemoverRef;
typedef std::vector<IteradorTabelaRef>::iterator IteradorRemoverRef;
typedef pair<int, IteradorTabelaRef> Alocado;

#ifndef __ITERADORES__
#define __ITERADORES__
typedef std::vector<NInstrucao*>::iterator IteradorInstrucao;
typedef std::vector<NExpressao*>::iterator IteradorExpressao;
typedef std::vector<NDeclaracaoVariavel*>::iterator IteradorVariavel;
#endif

#ifndef __CHECA_NO__
#define __CHECA_NO__
#define CHECA_NO(no, IDENT) no->tipoNo() == IDENT
#define NCHECA_NO(no, IDENT) no->tipoNo() != IDENT
#endif 

//GerarCodigo.cpp
void gerar_codigo(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No *funcao = 0);

//alocar_variavel.cpp
Alocado alocar_variavel(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, bool parametro = false);
int dimensao_vetor(NDeclVarVetorial *var);
int quantidade_alocada(No *no);

//gerenciamento.cpp
No* ultimo_elemento(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No *funcao);
void gerar_indice(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao);
void gerar_atribuicao(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao);

//gerar_inicializador.cpp
int gerar_inicializador(MaquinaVirtual &vm, TabelaRef &tabela, ListaExpressao *list, int profundidade, int offset, No* funcao);

//Comandos.cpp
void empilha(MaquinaVirtual &vm , CelulaMemoria &op);
void desempilha(MaquinaVirtual &vm, CelulaMemoria &op);
void inc_pp(MaquinaVirtual &vm, int qtd);
void dec_pp(MaquinaVirtual &vm, int qtd);
void invoca(MaquinaVirtual &vm, int &offset);
void troca(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void move(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void seq(MaquinaVirtual &vm, int &offset);
void cmp(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void cmp_imm(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria op2);
void si(MaquinaVirtual &vm, int &offset);
void carrega(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void ret(MaquinaVirtual &vm);


#endif