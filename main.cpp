#include "arvore_abstrata.h"
#include "semantico.h"
#include "debug.h"

extern int yyparse(NBloco * bloco);
extern "C" FILE *yyin;
extern int erro_compilador;
using namespace std;

int main(int argc, char *argv[])
{
	if(argc>1)
	{
		FILE *myfile = fopen(argv[1], "r");
		if (!myfile) {
			return -1;
		}
		yyin = myfile;
		NBloco *bloco;
		do {
			bloco = new NBloco(0);
			yyparse(bloco);
		} while (!feof(yyin));
		if(!erro_compilador)
		{
			TabelaSimbolo tabela;
			analise_semantica(tabela, bloco, 0, 0);
		}
		if(!erro_compilador)
		{	
			cout<<"COMPILADO!\n";
			debug_arvore(bloco, 0);
		}
		delete bloco;
	}
}