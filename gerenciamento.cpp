#include "GerarCodigo.h"

No* ultimo_elemento(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No *funcao)
{
	if(CHECA_NO(no, TipoNo::LISTA_EXPRESSOES))
	{
		NListaExpressoes *list = dynamic_cast<NListaExpressoes*>(no);

		for(int i = 0; i<(list->expressoes->size()-1); ++i)
		{
			No * r = ultimo_elemento(vm, tabela, list->expressoes->at(i), profundidade, offset, funcao);
			gerar_codigo(vm, tabela, r, profundidade, offset, funcao);
		}
		return  list->expressoes->at(list->expressoes->size()-1);
	}
	else
		return no;
}

void gerar_indice(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao)
{

	NIdentificadorVetorial* ident = dynamic_cast<NIdentificadorVetorial*>(no);

	IteradorTabelaRef it = tabela.find(ident->nome->c_str());

	Referencia ref = it->second.top();

	NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(ref.origem);

	int dimensao = 1;

	gerar_codigo(vm, tabela, ultimo_elemento(vm, tabela, ident->indice->at(ident->indice->size()), profundidade, offset, funcao) , profundidade, offset, funcao);
	
	int j = var->dimensoes->size() -1;

	//Se for diferente de 1 dimensão
	if(j>0)
		vm.codigo.push_back(new IMove(vm, vm.ebx, vm.eax));
	
	for(int i = ident->indice->size()-2; i>=0; --i, --j)
	{
		dimensao *= dynamic_cast<NInteiro*>(var->dimensoes->at(j))->valor;
		gerar_codigo(vm, tabela, ultimo_elemento(vm, tabela, ident->indice->at(i), profundidade, offset, funcao) , profundidade, offset, funcao);
		vm.codigo.push_back(new IMultIm(vm, vm.eax, vm.eax, CelulaMemoria(dimensao)));
		vm.codigo.push_back(new IAdc(vm, vm.ebx, vm.eax, vm.ebx));
	}
	//Se for diferente de 1 dimensão
	if(j>0)
		vm.codigo.push_back(new IMove(vm, vm.eax, vm.ebx));
}

void gerar_atribuicao(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao)
{
	NIdentificador *lhs = dynamic_cast<NIdentificador*>(no);
	IteradorTabelaRef itIdent = tabela.find(lhs->nome->c_str());
	Referencia ref = itIdent->second.top();

	if(CHECA_NO(no, TipoNo::IDENTIFICADOR_ESCALAR))
	{

		if(ref.profundidade == 0)
		{
			vm.codigo.push_back(new ISalva(vm, vm.ebx, vm.pg, ref.offset));
		}
		else
		{
			if(ref.parametro)
			{
				vm.codigo.push_back(new ISalva(vm, vm.ebx, vm.bp, -ref.offset));
			}
			else
			{
				vm.codigo.push_back(new ISalva(vm, vm.ebx, vm.bp, ref.offset));
			}
		}
	}
	else
	{
		NIdentificadorVetorial* ident = dynamic_cast<NIdentificadorVetorial*>(lhs);
		gerar_indice(vm, tabela, lhs, profundidade, offset, funcao);

		if(ref.profundidade == 0)
		{
			// ecx = pg + offset(do vetor alocado)
			vm.codigo.push_back(new IAdcIm(vm, vm.ecx, vm.pg, ref.offset));
			// eax = ecx + vm.eax(eax contém o deslocamento dentro do vetor)
			vm.codigo.push_back(new IAdc(vm, vm.eax, vm.ecx, vm.eax));
		}
		else
		{
			if(ref.parametro)
			{
				// ecx = bp - ref.offset( - ref.offset é o lucar onde aquele parametro está com relacao a bp)
				vm.codigo.push_back(new ISubIm(vm, vm.ecx, vm.bp, ref.offset));
				//carrega o valor que está em [ecx] que é o endereco do vetor pq é um ponteiro para o vetor...
				vm.codigo.push_back(new ICarrega(vm, vm.ecx, vm.ecx));
				// apartir de encerreco soma o deslocamento dentro do vetor...
				vm.codigo.push_back(new IAdc(vm, vm.eax, vm.ecx, vm.eax));
			}
			else
			{
				// ecx = bp + offset(do vetor alocado)
				vm.codigo.push_back(new IAdcIm(vm, vm.ecx, vm.bp, ref.offset));
				// eax = ecx + vm.eax(eax contém o deslocamento dentro do vetor)
				vm.codigo.push_back(new IAdc(vm, vm.eax, vm.ecx, vm.eax));
			}
		}

		// vm.memoria[vm.eax] = vm.ebx
		vm.codigo.push_back(new ISalva(vm, vm.ebx, vm.eax));
	}
}