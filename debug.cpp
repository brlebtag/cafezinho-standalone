#include "debug.h"

void imprime_nivel(int nivel)
{
	cout<<"|";
	for(int i=0; i<nivel; ++i)
	{
		cout<<"-";
	}
	cout<<" ";
}

void debug_arvore(No* no, int nivel)
{
	switch(no->tipoNo())
	{
		case TipoNo::NO:
		{
			imprime_nivel(nivel);
			cout<<"NO, linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::EXPRESSAO:
		{
			imprime_nivel(nivel);
			cout<<"EXPRESSAO, linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::INSTRUCAO:
		{
			imprime_nivel(nivel);
			cout<<"INSTRUCAO, linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::INTEIRO:
		{
			imprime_nivel(nivel);
			NInteiro *cons = dynamic_cast<NInteiro*>(no);
			cout<<"INTEIRO: "<<cons->valor<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::CARACTER:
		{
			imprime_nivel(nivel);
			NCaracter *cons = dynamic_cast<NCaracter*>(no);
			cout<<"CARACTER: "<<((char)cons->valor)<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::REAL:
		{
			imprime_nivel(nivel);
			NReal *cons = dynamic_cast<NReal*>(no);
			cout<<"REAL: "<<cons->valor<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::PALAVRA_LITERAL:
		{
			imprime_nivel(nivel);
			NPalavraLiteral *cons = dynamic_cast<NPalavraLiteral*>(no);
			cout<<"PALAVRA LITERAL: "<<cons->valor->c_str()<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::IDENTIFICADOR:
		{
			imprime_nivel(nivel);
			NIdentificador *ident = dynamic_cast<NIdentificador*>(no);
			cout<<"IDENTIFICADOR: "<<ident->nome->c_str()<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::IDENTIFICADOR_ESCALAR:
		{
			imprime_nivel(nivel);
			NIdentificadorEscalar *ident = dynamic_cast<NIdentificadorEscalar*>(no);
			cout<<"IDENTIFICADOR ESCALAR: "<<ident->nome->c_str()<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::IDENTIFICADOR_VETORIAL:
		{
			imprime_nivel(nivel);

			NIdentificadorVetorial *ident = dynamic_cast<NIdentificadorVetorial*>(no);

			cout<<"IDENTIFICADOR VETORIAL: "<<ident->nome->c_str()<<", linha: "<<no->linha<<"\n";

			for(ListaExpressao::iterator it = ident->indice->begin(); it!= ident->indice->end(); ++it)
				debug_arvore((*it), nivel+1);
		}
		break;
		case TipoNo::DECLARACAO_VARIAVEL:
		{
			imprime_nivel(nivel);
			NDeclaracaoVariavel *var = dynamic_cast<NDeclaracaoVariavel*>(no);
			cout<<"DECLARACAO VARIAVEL: "<<var->nome->c_str()<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::DECLARACAO_VARIAVEL_ESCALAR:
		{
			imprime_nivel(nivel);
			NDeclVarEscalar *var = dynamic_cast<NDeclVarEscalar*>(no);
			cout<<"DECLARACAO VARIAVEL ESCALAR: "<<var->nome->c_str()<<", linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::DECLARACAO_VARIAVEL_VETORIAL:
		{
			imprime_nivel(nivel);
			NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(no);
			cout<<"DECLARACAO VARIAVEL VETORIAL: "<<var->nome->c_str()<<", linha: "<<no->linha<<"\n";

			for(ListaExpressao::iterator it = var->dimensoes->begin(); it!= var->dimensoes->end(); ++it)
				debug_arvore((*it), nivel+1);

		}
		break;
		case TipoNo::BLOCO:
		{
			imprime_nivel(nivel);
			cout<<"BLOCO, linha: "<<no->linha<<"\n";

			NBloco *bloco = dynamic_cast<NBloco*>(no);

			for(ListaInstrucao::iterator it = bloco->instrucoes->begin(); it!= bloco->instrucoes->end(); ++it)
				debug_arvore((*it), nivel+1);
		}
		break;
		case TipoNo::CHAMADA_FUNCAO:
		{
			imprime_nivel(nivel);
			

			NChamadaFuncao *call = dynamic_cast<NChamadaFuncao*>(no);
			cout<<"CHAMADA FUNCAO: "<<call->nome->c_str()<<", linha: "<<no->linha<<"\n";

			for(ListaExpressao::iterator it = call->argumentos->begin(); it!= call->argumentos->end(); ++it)
				debug_arvore((*it), nivel+1);
		}
		break;
		case TipoNo::DECLARACAO_FUNCAO:
		{
			imprime_nivel(nivel);
			
			NDeclaracaoFuncao *func = dynamic_cast<NDeclaracaoFuncao*>(no);
			cout<<"DECLARACAO FUNCAO: "<<func->nome->c_str()<<", linha: "<<no->linha<<"\n";

			for(ListaVariavel::iterator it = func->parametros->begin(); it!= func->parametros->end(); ++it)
				debug_arvore((*it), nivel+1);

			debug_arvore(func->bloco, nivel+1);
		}
		break;
		case TipoNo::INSTRUCAO_EXPRESSAO:
		{
			imprime_nivel(nivel);
			cout<<"INSTRUCAO EXPRESSAO, linha: "<<no->linha<<"\n";

			NInstrucaoExpressao *expr = dynamic_cast<NInstrucaoExpressao*>(no);
			debug_arvore(expr->expressao, nivel+1);
		}
		break;
		case TipoNo::ATRIBUICAO:
		{
			imprime_nivel(nivel);
			cout<<"ATRIBUICAO, linha: "<<no->linha<<"\n";

			NAtribuicao *atr = dynamic_cast<NAtribuicao*>(no);
			debug_arvore(atr->lhs, nivel+1);
			debug_arvore(atr->rhs, nivel+1);
		}
		break;
		case TipoNo::OPERACAO_BINARIA:
		{
			imprime_nivel(nivel);
			cout<<"OPERACAO BINARIA, linha: "<<no->linha<<"\n";

			NOperacaoBinaria *bin = dynamic_cast<NOperacaoBinaria*>(no);
			debug_arvore(bin->lhs, nivel+1);
			debug_arvore(bin->rhs, nivel+1);
		}
		break;
		case TipoNo::OPERACAO_UNARIA:
		{
			imprime_nivel(nivel);
			cout<<"OPERACAO UNARIA, linha: "<<no->linha<<"\n";

			NOperacaoUnaria *uni = dynamic_cast<NOperacaoUnaria*>(no);
			debug_arvore(uni->rhs, nivel+1);
		}
		break;
		case TipoNo::OPERACAO_TERCIARIA:
		{
			imprime_nivel(nivel);
			cout<<"OPERACAO TERCIARIA, linha: "<<no->linha<<"\n";

			NOperacaoTerciaria *ter = dynamic_cast<NOperacaoTerciaria*>(no);
			debug_arvore(ter->expressao, nivel+1);
			debug_arvore(ter->ifExpr, nivel+1);
			debug_arvore(ter->elsExpr, nivel+1);
		}
		break;
		case TipoNo::RETORNE:
		{
			imprime_nivel(nivel);
			cout<<"RETORNE, linha: "<<no->linha<<"\n";

			NRetorne *ret = dynamic_cast<NRetorne*>(no);
			debug_arvore(ret->expressao, nivel+1);
		}
		break;
		case TipoNo::LEIA:
		{
			imprime_nivel(nivel);
			cout<<"LEIA, linha: "<<no->linha<<"\n";

			NLeia *leia = dynamic_cast<NLeia*>(no);
			debug_arvore(leia->expressao, nivel+1);
		}
		break;
		case TipoNo::ESCREVA:
		{
			imprime_nivel(nivel);
			cout<<"ESCREVA, linha: "<<no->linha<<"\n";

			NEscreva *escreva = dynamic_cast<NEscreva*>(no);
			debug_arvore(escreva->expressao, nivel+1);
		}
		break;
		case TipoNo::NOVA_LINHA:
		{
			imprime_nivel(nivel);
			cout<<"NOVA LINHA, linha: "<<no->linha<<"\n";
		}
		break;
		case TipoNo::SE:
		{
			imprime_nivel(nivel);
			cout<<"SE, linha: "<<no->linha<<"\n";

			NSe *se = dynamic_cast<NSe*>(no);
			debug_arvore(se->expressao, nivel+1);
			debug_arvore(se->instrucao, nivel+1);
		}
		break;
		case TipoNo::SE_SENAO:
		{
			imprime_nivel(nivel);
			cout<<"SE SENAO, linha: "<<no->linha<<"\n";

			NSeSenao *senao = dynamic_cast<NSeSenao*>(no);
			debug_arvore(senao->expressao, nivel+1);
			debug_arvore(senao->instrucaoSe, nivel+1);
			debug_arvore(senao->instrucaoSenao, nivel+1);
		}
		break;
		case TipoNo::ENQUANTO:
		{
			imprime_nivel(nivel);
			cout<<"ENQUANTO, linha: "<<no->linha<<"\n";

			NEnquanto *enq = dynamic_cast<NEnquanto*>(no);
			debug_arvore(enq->expressao, nivel+1);
			debug_arvore(enq->instrucao, nivel+1);
		}
		break;
		case TipoNo::CAST:
		{
			imprime_nivel(nivel);
			cout<<"CAST, linha: "<<no->linha<<"\n";

			NCast *cast = dynamic_cast<NCast*>(no);
			debug_arvore(cast->expressao, nivel+1);
		}
		break;
		case TipoNo::LISTA_EXPRESSOES:
		{
			imprime_nivel(nivel);
			cout<<"LISTA EXPRESSOES, linha: "<<no->linha<<"\n";

			NListaExpressoes *list = dynamic_cast<NListaExpressoes*>(no);

			for(ListaExpressao::iterator it = list->expressoes->begin(); it!= list->expressoes->end(); ++it)
				debug_arvore((*it), nivel+1);
		}
		break;
		case TipoNo::INICIALIZADOR_VETOR:
		{
			imprime_nivel(nivel);
			cout<<"INICIALIZADOR VETOR, linha: "<<no->linha<<"\n";

			NInicializadorVetor *list = dynamic_cast<NInicializadorVetor*>(no);
			int i=0;
			for(ListaExpressao::iterator it = list->init->begin(); it!= list->init->end(); ++it, ++i)
				debug_arvore((*it), nivel+1);
		}
		break;
		case TipoNo::LISTA_INICIALIZADOR:
		{
			imprime_nivel(nivel);
			cout<<"LISTA INICIALIZADOR, linha: "<<no->linha<<"\n";

			NListaInicializador *list = dynamic_cast<NListaInicializador*>(no);
			int i=0;
			
			for(ListaExpressao::iterator it = list->expressoes->begin(); it!= list->expressoes->end(); ++it, ++i)
				debug_arvore((*it), nivel+1);
		}
		break;
	}
}