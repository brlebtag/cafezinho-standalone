#include "GerarCodigo.h"

Alocado alocar_variavel(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, bool parametro)
{
	if(CHECA_NO(no, TipoNo::DECLARACAO_VARIAVEL_ESCALAR))
	{
		NDeclVarEscalar *var = dynamic_cast<NDeclVarEscalar*>(no);

		//Se não for parametro não precisa alocar variavel pq ele já foi empilhando qnd o parametro foi chamado...
		if(!parametro)
			inc_pp(vm, 1);

		IteradorTabelaRef it = tabela.find(var->nome->c_str());

		if(it == tabela.end())
		{
			PilhaRef pilha;
			pilha.push(Referencia(no, profundidade, offset, parametro));
			tabela.insert(make_pair(var->nome->c_str(), pilha));
			it = tabela.find(var->nome->c_str());
		}
		else
		{
			it->second.push(Referencia(no, profundidade, offset, parametro));
		}

		return make_pair(1, it);
	}
	else
	{
		NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(no);

		int dimensao = 0;
		if(parametro)
			dimensao = 1;
		else
			dimensao = dimensao_vetor(var);

		//Se não for parametro não precisa alocar variavel pq ele já foi empilhando qnd o parametro foi chamado...
		if(!parametro)
			inc_pp(vm, dimensao);

		IteradorTabelaRef it = tabela.find(var->nome->c_str());
		
		if(it == tabela.end())
		{
			PilhaRef pilha;
			pilha.push(Referencia(no, profundidade, offset, parametro, true));
			tabela.insert(make_pair(var->nome->c_str(), pilha));
			it = tabela.find(var->nome->c_str());
		}
		else
		{
			it->second.push(Referencia(no, profundidade, offset, parametro, true));
		}

		return make_pair(dimensao, it);
	}
}

int dimensao_vetor(NDeclVarVetorial *var)
{
	int dimensao = 1;
	
	for(IteradorExpressao it = var->dimensoes->begin(); it!= var->dimensoes->end(); ++it)
	{
		dimensao *= dynamic_cast<NInteiro*>(*it)->valor;
	}

	return dimensao;
}