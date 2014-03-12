#include "semantico.h"

IteradorTabelaSimbolo analise_semantica(TabelaSimbolo &tabela, No* no, int profundidade, No* funcao)
{
	if(CHECA_NO(no, BLOCO))
	{
		NBloco *bloco = dynamic_cast<NBloco*>(no);
		Remover remover;

		for(IteradorInstrucao it = bloco->instrucoes->begin(); it != bloco->instrucoes->end(); ++it)
		{
			if(CHECA_NO((*it), BLOCO))
			{
				analise_semantica(tabela, (No*)(*it), profundidade+1, funcao);
			}
			else
			{
				IteradorTabelaSimbolo itSim = analise_semantica(tabela, (No*)(*it), profundidade, funcao);

				if(itSim != tabela.end())
				{
					remover.push_back(itSim);
				}
			}
		}

		for(IteratorRemover it = remover.begin(); it!= remover.end(); ++it)
		{
			IteradorTabelaSimbolo itSim = (*it);

			delete itSim->second->top();
			itSim->second->pop();

			if(itSim->second->empty())
            {
                delete itSim->second; // remove a pilha
                tabela.erase(itSim);
            }
		}

		return tabela.end();
	}
	else if(CHECA_NO(no, DECLARACAO_VARIAVEL_ESCALAR) || CHECA_NO(no, DECLARACAO_VARIAVEL_VETORIAL))
	{
		NDeclaracaoVariavel *var = dynamic_cast<NDeclaracaoVariavel*>(no);
 
        IteradorTabelaSimbolo itSim = tabela.find(var->nome->c_str());

        if(itSim == tabela.end())
        {
            tabela.insert(make_pair<std::string, PilhaSimbolo* >(var->nome->c_str(), new PilhaSimbolo()));
            itSim = tabela.find(var->nome->c_str()); //procuro novamente para q ele aponta para este novo elemento...
        }

        if((!itSim->second->empty()) && itSim->second->top()->profundidade == profundidade)
        {
        	if(CHECA_NO(itSim->second->top()->no, DECLARACAO_FUNCAO))
        	{
        		cout<<"ERRO SEMANTICO VARIAVEL "<<var->nome->c_str()<<" JA FOI DECLARADO COMO SENDO OUTRO TIPO DE SIMBOLO PROXIMO A "<<var->linha<<"\n";
            	erro_compilador = true;
        	}
        	else
        	{
        		cout<<"ERRO SEMANTICO VARIAVEL "<<var->nome->c_str()<<" JA FOI DECLARADO PROXIMO A "<<var->linha<<"\n";
            	erro_compilador = true;
        	}

        	return tabela.end();
        }
        else
        {
        	if(CHECA_NO(no, DECLARACAO_VARIAVEL_VETORIAL)&&(!checa_vetor_dimensao(dynamic_cast<NDeclVarVetorial*>(no)->eParametro, (NDeclVarVetorial*)no)))
        	{
        		cout<<"ERRO SEMANTICO VARIAVEL VETORIAL"<<var->nome->c_str()<<" NAO FOI DECLARADO CORRETAMENTE AS DIMENSOES DO VETOR!"<<var->linha<<"\n";
            	erro_compilador = true;
            	return tabela.end();
        	}
        	else
        	{
        		itSim->second->push(new Simbolo(var, profundidade));
        		return itSim;
        	}
        }
	}
	else if(CHECA_NO(no, DECLARACAO_FUNCAO))
	{
		NDeclaracaoFuncao *func = dynamic_cast<NDeclaracaoFuncao*>(no);

		IteradorTabelaSimbolo itSim = tabela.find(func->nome->c_str());
 
        if(itSim==tabela.end())
        {
            tabela.insert( make_pair<std::string, PilhaSimbolo* >(func->nome->c_str(), new PilhaSimbolo() ) );
            itSim = tabela.find(func->nome->c_str()); //procuro novamente para q ele aponta para este novo elemento...  
        }
 
        if((!itSim->second->empty()) && itSim->second->top()->profundidade == profundidade)
        {

        	if(CHECA_NO(itSim->second->top()->no , DECLARACAO_VARIAVEL_ESCALAR) || CHECA_NO(itSim->second->top()->no , DECLARACAO_VARIAVEL_VETORIAL))
        	{
        		cout<<"ERRO SEMANTICO FUNCAO "<<func->nome->c_str()<<" JA FOI DECLARADO COMO SENDO OUTRO TIPO DE SIMBOLO PROXIMO A "<<func->linha<<"\n";
            	erro_compilador = true;
        	}
        	else
        	{
        		cout<<"ERRO SEMANTICO FUNCAO "<<func->nome->c_str()<<" JA FOI DECLARADO! PROXIMO A "<<func->linha<<"\n";
            	erro_compilador = true;
        	}

            itSim = tabela.end();
        }
        else
        {
            itSim->second->push(new Simbolo(func, profundidade));
        }

        Remover remover;

        //insiro as variaveis locais
		for(IteradorVariavel it = func->parametros->begin(); it!= func->parametros->end(); it++)
		{	
			IteradorTabelaSimbolo itSimVar = analise_semantica(tabela, (No*) (*it), profundidade+1, funcao);

			if(itSimVar != tabela.end())
			{
				remover.push_back(itSimVar);
			}
		}

		//executo para o bloco da função agora
		analise_semantica(tabela, (No*) func->bloco, profundidade+1, no);

		for(IteratorRemover it = remover.begin(); it!= remover.end(); ++it)
		{
			IteradorTabelaSimbolo itSim = (*it);
			delete itSim->second->top();

			if(itSim->second->empty())
            {
                delete itSim->second; // remove a pilha
                tabela.erase(itSim);
            }
		}

		if(func->possuiRetorno==false&&func->tipo!=TIPO_NULO)
		{
			cout<<"ERRO SEMANTICO NENHUM RETORNO FOI DEFINIDO PARA "<<func->nome->c_str()<<" ESPERADO TIPO "<<nome_tipo(func->tipo)<<" PROXIMO A "<<func->linha<<"\n";
			erro_compilador = true;
		}

		return itSim;
	}
	else if(CHECA_NO(no, INSTRUCAO_EXPRESSAO))
	{
		return analise_semantica(tabela, (No*) dynamic_cast<NInstrucaoExpressao*>(no)->expressao, profundidade+1, funcao);
	}
	else if(CHECA_NO(no, RETORNE))
	{
		NRetorne *ret = dynamic_cast<NRetorne*>(no);

		NDeclaracaoFuncao *func = dynamic_cast<NDeclaracaoFuncao*>(funcao);

		TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, ((No*) ret->expressao));

		if(tipo != func->tipo)
		{
			cout<<"ERRO SEMANTICO ESPERADO RETORNO DO TIPO "<<nome_tipo(func->tipo)<<" ENCONTADO DO TIPO "<<nome_tipo(tipo)<<" PROXIMO A "<<ret->linha<<"\n";
			erro_compilador = true;
		}

		func->possuiRetorno = true;

		return tabela.end();
	}
	else if(CHECA_NO(no, LEIA))
	{
		NLeia *ler = dynamic_cast<NLeia*>(no);

		ListaExpressao *list = dynamic_cast<NListaExpressoes*>(leia->expressao)->expressoes;

		for(IteradorExpressao it = list->begin(); it!= list->end(); ++it)
		{
			No* r = ultimo_parametro(tabela, (*it));
			
			if(CHECA_NO(r, CAST))
			{
				No* r1 = ultimo_parametro(tabela, dynamic_cast<NCast*>(expressao));

				if(NCHECA_NO(r1, IDENTIFICADOR_ESCALAR)&&NCHECA_NO(r, IDENTIFICADOR_VETORIAL))
				{
					cout<<"ERRO SEMANTICO NAO REALIZAR ESTA OPERACAO SOBRE O OPERADOR DO TIPO NAO IDENTIFICADOR PROXIMO A "<<ler->linha<<"\n";
					erro_compilador = true;
				}
			}
			else if(NCHECA_NO(r, IDENTIFICADOR_ESCALAR)&&NCHECA_NO(r, IDENTIFICADOR_VETORIAL))
			{
				cout<<"ERRO SEMANTICO NAO REALIZAR ESTA OPERACAO SOBRE O OPERADOR DO TIPO NAO IDENTIFICADOR PROXIMO A "<<ler->linha<<"\n";
				erro_compilador = true;
			}
		}

		return tabela.end();
	}
	else if(CHECA_NO(no, ESCREVA))
	{
		NEscreva *escreve = dynamic_cast<NEscreva*>(no);

		ListaExpressao *list = dynamic_cast<NListaExpressoes*>(escreve->expressao)->expressoes;

		TipoVariavel::TipoVariavel tipo;

		for(IteradorExpressao it = list->begin(); it!= list->end(); ++it)
		{			
			tipo = checar_tipo(tabela, ultimo_parametro(tabela, (*it)));

			if(tipo == TIPO_ERRO || tipo == TIPO_NULO)
			{
				cout<<"ERRO SEMANTICO NAO REALIZAR ESTA OPERACAO ENCONTRADO "<<nome_tipo(tipo)<<" PROXIMO A "<<ler->linha<<"\n";
				erro_compilador = true;
			}
		}

		return tabela.end();
	}
	else if(CHECA_NO(no, NOVA_LINHA))
	{
		return tabela.end();
	}
	else if(CHECA_NO(no, SE))
	{
		NSe *ifinstr = dynamic_cast<NSe*>(no);

		TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, ifinstr->expressao);

		if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO||tipo ==TIPO_REAL)
		{
			cout<<"ERRO SEMANTICO NAO E POSSIVEL AVALIAR ESTA EXPRESSAO ENCONTRADO TIPO "<<nome_tipo(tipo)<<" PROXIMO A "<<ifinstr->linha<<"\n";
			erro_compilador = true;
		}

		analise_semantica(tabela,(No*) ifinstr->instrucao, profundidade+1, funcao);

		return tabela.end();
	}
	else if(CHECA_NO(no, SE_SENAO))
	{
		NSeSenao *ifinstr = dynamic_cast<NSeSenao*>(no);

		TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, ifinstr->expressao);

		if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO||tipo ==TIPO_REAL)
		{
			cout<<"ERRO SEMANTICO NAO E POSSIVEL AVALIAR ESTA EXPRESSAO ENCONTRADO TIPO "<<nome_tipo(tipo)<<" PROXIMO A "<<ifinstr->linha<<"\n";
			erro_compilador = true;
		}

		analise_semantica(tabela,(No*) ifinstr->instrucaoSe, profundidade+1, funcao);
		analise_semantica(tabela,(No*) ifinstr->instrucaoSenao, profundidade+1, funcao);

		return tabela.end();
	}
	else if(CHECA_NO(no, ENQUANTO))
	{
		NEnquanto *enq = dynamic_cast<NEnquanto*>(no);

		TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, enq->expressao);

		if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO||tipo ==TIPO_REAL)
		{
			cout<<"ERRO SEMANTICO NAO E POSSIVEL AVALIAR ESTA EXPRESSAO ENCONTRADO TIPO "<<nome_tipo(tipo)<<" PROXIMO A "<<enq->linha<<"\n";
			erro_compilador = true;
		}

		analise_semantica(tabela, (No*)enq->instrucao, profundidade+1, funcao);

		return tabela.end();
	}
	else if(CHECA_NO(no, INICIALIZADOR_VETOR))
	{
		NInicializadorVetor *list = dynamic_cast<NInicializadorVetor*>(no);

		IteradorTabelaSimbolo itSim = tabela.find(list->nome->c_str());

		if(itSim==tabela.end())
		{
			cout<<"ERRO SEMANTICO VARIAVEL "<<list->nome->c_str()<<" NAO FOI PREVIAMENTE DECLARADO! PROXIMO A "<<list->linha<<"\n";
			erro_compilador = true;
		}
		else
		{

			if(CHECA_NO(itSim->second->top()->no, DECLARACAO_FUNCAO))
			{
				cout<<"ERRO SEMANTICO ESPERADO VARIAVEL VETORIAL ENCONTRADO FUNCAO PROXIMO A "<<list->linha<<"\n";
				erro_compilador = true;
			}
			else if(CHECA_NO(itSim->second->top()->no, DECLARACAO_VARIAVEL_ESCALAR))
			{
				cout<<"ERRO SEMANTICO ESPERADO VARIAVEL VETORIAL ENCONTRADO VARIAVEL ESCALAR PROXIMO A "<<list->linha<<"\n";
				erro_compilador = true;
			}
			else
			{
				NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(itSim->second->top()->no);

				bool resultado = true;

				//Checa o tipo do indice para ver se é inteiro
				for(IteradorExpressao it = list->init->begin(); it!= list->init->end(); ++it)
				{
					resultado &= checa_tipo_init(tabela, (No*)(*it), var->tipo);
				}

				if(!resultado)
				{
					//mensagem de erro...
					cout<<"ERRO SEMANTICO VALORES PARA INICIAR O VETOR NAO COINDICEM ESPERADO VALORES DO TIPO "<<nome_tipo(var->tipo)<<"\n";
					erro_compilador = true;
				}
			}
		}

		return tabela.end();
	}
	//Todos esses aqui já foram implementados em checar_tipo então eu o chamo e ignoro o retorno...
	else if(
		CHECA_NO(no, CHAMADA_FUNCAO)||
		CHECA_NO(no, IDENTIFICADOR_ESCALAR)||
		CHECA_NO(no, IDENTIFICADOR_VETORIAL)||
		CHECA_NO(no, ATRIBUICAO)||
		CHECA_NO(no, OPERACAO_BINARIA)||
		CHECA_NO(no, OPERACAO_UNARIA)||
		CHECA_NO(no, OPERACAO_TERCIARIA)||
		CHECA_NO(no, CAST) ||
		CHECA_NO(no, LISTA_EXPRESSOES)
	)
	{
		checar_tipo(tabela, no);
		return tabela.end();
	}
	else if(
		CHECA_NO(no, INTEIRO) ||
		CHECA_NO(no, CARACTER) ||
		CHECA_NO(no, REAL) ||
		CHECA_NO(no, PALAVRA_LITERAL)
	)
	{
		cout<<"ERRO SEMANTICO ESPERADO NADA ENCONTRADO "<<(tipo_no(no))<<" PROXIMO A "<<no->linha<<"\n";
    	erro_compilador = true;
    	return tabela.end();
	}
}
