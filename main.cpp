#include "arvore_abstrata.h"
#include "semantico.h"
#include "GerarCodigo.h"
#include <vector>
#include <string.h>
#include "MaquinaVirtual.h"
#include "debug.h"
#include <set>

extern int yyparse(NBloco * bloco);
extern "C" FILE *yyin;
extern int erro_compilador;
using namespace std;

typedef void (*chama)(NBloco *bloco);

void chama_debug_codigo(NBloco *bloco)
{
	if(!erro_compilador)
	{
		TabelaRef tabela;
		MaquinaVirtual vm;
		gerar_codigo(vm, tabela, bloco, 0, 0, 0);

		if((*vm.rotulo[0])!=-1)
		{
			debug_codigo(vm);
		}
		else
			cout<<"A FUNCAO void programa() NAO FOI DEFINIDA!";
	}
}

void chama_analise_semantica(NBloco *bloco)
{
	if(!erro_compilador)
	{
		TabelaSimbolo tabela;
		analise_semantica(tabela, bloco, 0, 0);
	}
}

void chama_debug_arvore(NBloco *bloco)
{
	if(!erro_compilador)
	{	
		debug_arvore(bloco, 0);
	}
}

void chama_gera_codigo(NBloco *bloco)
{
	if(!erro_compilador)
	{
		TabelaRef tabela;
		MaquinaVirtual vm;
		gerar_codigo(vm, tabela, bloco, 0, 0, 0);

		if((*vm.rotulo[0])!=-1)
		{
			vm.executar();
		}
		else
			cout<<"A FUNCAO void programa() NAO FOI DEFINIDA!";
	}
}

CelulaMemoria* determina_registrador(MaquinaVirtual &vm, string registrador)
{
	if(registrador.compare("eax")==0)
		return &vm.eax;
	if(registrador.compare("ebx")==0)
		return &vm.ebx;
	if(registrador.compare("ecx")==0)
		return &vm.ecx;
	if(registrador.compare("edx")==0)
		return &vm.edx;
	if(registrador.compare("pp")==0)
		return &vm.pp;
	if(registrador.compare("er")==0)
		return &vm.er;
	if(registrador.compare("pg")==0)
		return &vm.pg;
	if(registrador.compare("bp")==0)
		return &vm.bp;

	return NULL;
}

void chama_gera_codigo_debug(NBloco *bloco)
{
	chama_analise_semantica(bloco);
	
	if(!erro_compilador)
	{
		TabelaRef tabela;
		MaquinaVirtual vm;
		gerar_codigo(vm, tabela, bloco, 0, 0, 0);

		if((*vm.rotulo[0])!=-1)
		{
			bool execute = true;
			bool loop;
			int indice;
			bool nao_parou = true;
			set<int> indice_parar;
			bool continuar = false;

			do
			{
				if(vm.execute != false)
				{
					if(continuar)
					{
						//executa até achar um break...
						int sem_break = true;
						do
						{
							indice = vm.pc;
							if(indice_parar.find(indice)!=indice_parar.end())
							{
								continuar = false;
								sem_break = false;
								nao_parou = true;
								cout<<"[BREAK] "<<indice<<": ";
								imprime_instrucao(vm, vm.codigo[indice]);
								goto sair_break;
							}
							vm.passo();
						}while(sem_break&&vm.execute!=false);
						nao_parou = false;
						cout<<"o programa parou!\n";
					}
					else
					{
						indice = vm.pc;
						vm.passo();
					}
				}
				else
				{
					nao_parou = false;
					cout<<"o programa parou!\n";
				}
				

				if(!vm.erf)
				{
					if(nao_parou)
					{
						cout<<indice<<": ";
						imprime_instrucao(vm, vm.codigo[indice]);
					}

sair_break:
					do
					{
						loop = true;
						cout<<"> ";
						string opcao;
						getline(cin, opcao);

						char* token = strtok(&opcao[0]," ");
						while(token!=NULL)
						{
							if(strcmp(token,"eco")==0)
							{
								token = strtok(NULL, " ");
								if(token!=NULL)
								{
									if(strcmp(token, "pc")==0)
										cout<<"pc: "<<vm.pc<<"\n";
									else if(strcmp(token, "bf")==0)
										cout<<"bf: "<<vm.bf<<"\n";
									else if(strcmp(token, "sf")==0)
										cout<<"sf: "<<vm.sf<<"\n";
									else if(strcmp(token, "ef")==0)
										cout<<"ef: "<<vm.ef<<"\n";
									else if(strcmp(token, "erf")==0)
										cout<<"erf: "<<vm.erf<<"\n";
									else
									{
										CelulaMemoria *celula = determina_registrador(vm, token);
										if(celula!=NULL)
											cout<<""<<nome_reg(vm, *celula)<<": "<<celula->toInt()<<"\n";
										else
											cout<<"registrador nao conhecido!\n";
									}
								}
							}
							else if(token!=NULL&&strcmp(token,"ecor")==0)
							{
								token = strtok(NULL, " ");
								if(token!=NULL)
								{
									if(strcmp(token, "pc")==0)
										cout<<"pc: "<<((double)vm.pc)<<"\n";
									else if(strcmp(token, "bf")==0)
										cout<<"bf: "<<((double)vm.bf)<<"\n";
									else if(strcmp(token, "sf")==0)
										cout<<"sf: "<<((double)vm.sf)<<"\n";
									else if(strcmp(token, "ef")==0)
										cout<<"ef: "<<((double)vm.ef)<<"\n";
									else if(strcmp(token, "erf")==0)
										cout<<"erf: "<<((double)vm.erf)<<"\n";
									else
									{
										CelulaMemoria *celula = determina_registrador(vm, token);
										if(celula!=NULL)
											cout<<""<<nome_reg(vm, *celula)<<": "<<celula->toDouble()<<"\n";
										else
											cout<<"registrador nao conhecido!\n";
									}
								}
							}
							else if(token!=NULL&&strcmp(token,"reiniciar")==0)
							{
								cout<<"Deseja realmente reiniciar a execucao do programa? (1 = sim, 0 = nao)\n";
								cout<<"> ";
								string reiniciar;
								getline(cin, reiniciar);
								if(reiniciar.compare("1")==0||reiniciar.compare("sim")==0)
								{
									vm.reiniciar();
									loop = false;
									nao_parou = true;
								}
								else if(reiniciar.compare("0")!=0||reiniciar.compare("nao")!=0)
									cout<<"opcao invalida!\n";
							}
							else if(token!=NULL&&strcmp(token,"prox")==0)
							{
								loop = false;
							}
							else if(token!=NULL&&strcmp(token,"sair")==0)
							{
								execute = false;
								loop = false;
							}
							else if(token!=NULL&&strcmp(token,"repete")==0)
							{
								cout<<indice<<": ";
								imprime_instrucao(vm, vm.codigo[indice]);
							}
							else if(token!=NULL&&strcmp(token,"memoria")==0)
							{
								token = strtok(NULL, " ");
								if(token!=NULL)
								{
									int indice = stoi(token, NULL);
									if(indice!=-1&&indice<vm.memoria.capacity())
										cout<<vm.memoria[indice]<<"\n";
									else
										cout<<"memeoria invalida!\n";
								}
							}
							else if(token!=NULL&&strcmp(token,"break")==0)
							{
								token = strtok(NULL, " ");
								if(token!=NULL&&(strcmp(token, "limpar")==0))
								{
									indice_parar.clear();
								}
								else
								{
									int ponto_parar = stoi(token, NULL);
									if(ponto_parar!=-1)
									{
										indice_parar.insert(ponto_parar);
									}
								}
							}
							else if(token!=NULL&&strcmp(token,"continuar")==0)
							{
								continuar = true;
								loop = false;
							}
							else
							{
								cout<<"opcao invalida!\n";
								break;
							}

							token = strtok(NULL, " ");
						}
					}while(loop);
				}
				else
					execute = false;
			}
			while(execute);
			
		}
		else
			cout<<"A FUNCAO void programa() NAO FOI DEFINIDA!";
	}
}

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


		vector<chama> parametros;

		for(int i=2; i<argc; ++i)
		{
			if(strcmp("-dc",argv[i])==0)
				parametros.push_back(chama_debug_codigo);
			else if(strcmp("-da",argv[i])==0)
				parametros.push_back(chama_debug_arvore);
			else if(strcmp("-s",argv[i])==0)
				parametros.push_back(chama_analise_semantica);
			else if(strcmp("-c",argv[i])==0)
				parametros.push_back(chama_gera_codigo);
			else if(strcmp("-d",argv[i])==0)
				parametros.push_back(chama_gera_codigo_debug);
			else
				cout<<"> parametro nao conhecido!\n";
		}

		for(vector<chama>::iterator it = parametros.begin(); it!= parametros.end(); ++it)
		{
			chama func = (*it);
			func(bloco);
		}

		if(parametros.size()==0)
		{
			chama_analise_semantica(bloco);
			chama_gera_codigo(bloco);
		}

		delete bloco;
	}
} 