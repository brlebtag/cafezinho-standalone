#include "GerarCodigo.h"

int gerar_inicializador(MaquinaVirtual &vm, TabelaRef &tabela, ListaExpressao *list, int profundidade, int offset, No* funcao)
{

	for(IteradorExpressao it = list->begin(); it!=list->end(); ++it)
	{
		if((*it)->tipoNo() == TipoNo::LISTA_INICIALIZADOR)
		{

			offset += gerar_inicializador(vm, tabela, dynamic_cast<NListaInicializador*>(*it)->expressoes, profundidade, offset, funcao);

		}
		else
		{
			gerar_codigo(vm, tabela, (*it), profundidade, offset, funcao);
			vm.codigo.push_back(new IMove(vm, vm.ebx, vm.eax));
			gerar_atribuicao(vm, tabela, (*it), profundidade, offset, funcao);
			++offset;
		}
	}

	return offset;
}