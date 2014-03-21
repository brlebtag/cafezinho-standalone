 #include "semantico.h"

bool checar_chamada(TabelaSimbolo &tabela, No* parametro, No* argumento)
{
	No* no = ultimo_parametro(tabela, argumento);

	if(CHECA_NO(parametro, DECLARACAO_VARIAVEL_ESCALAR))
	{
		NDeclVarEscalar *var = dynamic_cast<NDeclVarEscalar*>(parametro);

		return var->tipo == checar_tipo(tabela, no);	
	}
	else
	{
		NDeclVarVetorial *param = dynamic_cast<NDeclVarVetorial*>(parametro);
		
		if(NCHECA_NO(no, IDENTIFICADOR_ESCALAR))
		{
			cout<<"ERRO SEMANTICO ESPERADO VARIAVEL VETORIAL ENCONTRADO "<<tipo_no(no)<<" PROXIMO A "<<argumento->linha<<"\n";
			erro_compilador = true;
			return false;
		}
		else
		{
			NIdentificadorEscalar *ident = dynamic_cast<NIdentificadorEscalar*>(no);

			IteradorTabelaSimbolo itSim = tabela.find(ident->nome->c_str());

			if(itSim==tabela.end())
			{
				cout<<"ERRO SEMANTICO VARIAVEL "<<ident->nome->c_str()<<" NAO FOI PREVIAMENTE DECLARADO! PROXIMO A "<<ident->linha<<"\n";
				erro_compilador = true;
				return false;
			}
			else
			{
				if(CHECA_NO(itSim->second->top()->no, DECLARACAO_FUNCAO))
				{
					cout<<"ERRO SEMANTICO ESPERADO VARIAVEL VETORIAL ENCONTRADO FUNCAO PROXIMO A "<<ident->linha<<"\n";
					erro_compilador = true;
					return false;
				}
				else if(CHECA_NO(itSim->second->top()->no, DECLARACAO_VARIAVEL_ESCALAR))
				{
					cout<<"ERRO SEMANTICO ESPERADO VARIAVEL VETORIAL ENCONTRADO VARIAVEL ESCALAR PROXIMO A "<<ident->linha<<"\n";
					erro_compilador = true;
					return false;
				}
				else
				{
					NDeclVarVetorial *arg = dynamic_cast<NDeclVarVetorial*>(itSim->second->top()->no);


					if(param->dimensoes->size()!=arg->dimensoes->size())
					{
						cout<<"ERRO SEMANTICO PARAMETRO POSSUI "<<param->dimensoes->size()<<" DIMENSOES ENQUANTO QUE ARGUMENTO POSSUI "<<arg->dimensoes->size()<<" PERTO DE "<<ident->linha<<"\n";
						erro_compilador = true;
						return false;
					}


					bool resultado = true;
					string dimArg, dimParam;

					if(param->dimensoes->at(0)->tipoNo() == TipoNo::INTEIRO)
					{
						if(dynamic_cast<NInteiro*>(param->dimensoes->at(0))->valor != dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor)
						{
							resultado = false;
							dimArg = static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor) )->str();
							dimParam = static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(param->dimensoes->at(0))->valor) )->str();
						}
						else
						{
							dimArg = static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor) )->str();
							dimParam = static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(param->dimensoes->at(0))->valor) )->str();
						}
					}
					else
					{
						dimArg = static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor) )->str();
						dimParam = static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor) )->str();
					}

					for(int i=1; i<param->dimensoes->size(); ++i)
					{
						resultado &= dynamic_cast<NInteiro*>(param->dimensoes->at(i))->valor == dynamic_cast<NInteiro*>(arg->dimensoes->at(i))->valor;
						dimArg +="][";
						dimArg += static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(arg->dimensoes->at(i))->valor) )->str();
						dimParam +="][";
						dimParam += static_cast<ostringstream*>( &(ostringstream() << dynamic_cast<NInteiro*>(param->dimensoes->at(i))->valor) )->str();
					}

					if(!resultado)
					{
						cout<<"ERRO SEMANTICO AS DIMENSOES DO ARGUMENTO SAO "<<arg->nome->c_str()<<"["<<dimArg.c_str()<<"] ENQUANTO QUE AS DIMENSOES DO PARAMETRO SAO "<<param->nome->c_str()<<"["<<dimParam.c_str()<<"] PERTO DE "<<ident->linha<<"\n";
						erro_compilador = true;
						return false;
					}

					if(param->tipo!=arg->tipo)
					{
						cout<<"ERRO SEMANTICO PARAMETRO E DO TIPO *"<<param->tipo<<" E ARGUMENTO E DO TIPO *"<<arg->tipo<<" PERTO DE "<<ident->linha<<"\n";
						erro_compilador = true;
						return false;
					}

					return true;
				}
			}
		}
	}
}

No* ultimo_parametro(TabelaSimbolo &tabela, No * no)
{
	if(CHECA_NO(no, LISTA_EXPRESSOES))
	{
		NListaExpressoes *list  = dynamic_cast<NListaExpressoes*>(no);

		for(int i=0; i<(list->expressoes->size()-1); ++i)
		{
			checar_tipo(tabela, (No*) list->expressoes->at(i));
		}

		return ultimo_parametro(tabela, list->expressoes->at(list->expressoes->size()-1));
	}
	else
		return no;
}