#include "GerarCodigo.h"

void gerar_inicializador(MaquinaVirtual &vm, TabelaRef &tabela, NInicializadorVetor *list, int profundidade, int offset, No* funcao)
{
	queue<NListaInicializador*> inicializador;
	IteradorTabelaRef itIdent = tabela.find(list->nome->c_str());
	Referencia ref = itIdent->second.top();

	for(int i=0; i<list->init->size(); ++i)
	{
		inicializador.push((NListaInicializador*)list->init->at(i));
	}

	int indice = 1;
	
	while(!inicializador.empty())
	{
		NListaInicializador *init = inicializador.front();
		inicializador.pop();

		for(int i=0; i<init->expressoes->size(); ++i)
		{
			if(CHECA_NO(init->expressoes->at(i), TipoNo::LISTA_INICIALIZADOR))
				inicializador.push((NListaInicializador*)init->expressoes->at(i));
			else
			{
				//gera o código...
				gerar_codigo(vm, tabela, init->expressoes->at(i), profundidade, offset, funcao);

				if(ref.profundidade == 0)
				{
					// ebx = pg + offset(inicial) + i
					vm.codigo.push_back(new ISalva(vm.eax, vm.pg, indice));
				}
				else
				{
					vm.codigo.push_back(new ISalva(vm.eax, vm.bp, indice));
				}

				++indice;
			}
		}
	}
}