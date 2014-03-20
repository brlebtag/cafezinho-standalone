#include "debug.h"

using namespace TipoInstrucao;

void debug_codigo(MaquinaVirtual &vm)
{
	int i=0;
	for(vector<Instrucao*>::iterator it = vm.codigo.begin(); it!= vm.codigo.end(); ++it, ++i)
	{
		cout<<i<<": ";
		imprime_instrucao(vm, (*it));
	}
}

void imprime_instrucao(MaquinaVirtual &vm, Instrucao * instrucao)
{
	switch(instrucao->tipoInstucao())
	{
		case MOVE:
		{
			IMove *inst = dynamic_cast<IMove*>(instrucao);
			cout<<"mov "<<nome_reg(vm, inst->registrador1)<<", "<<nome_reg(vm, inst->registrador2)<<"\n";
		}
		break;
		case MOVE_IM:
		{
			IMoveIm *inst = dynamic_cast<IMoveIm*>(instrucao);
			cout<<"mov "<<nome_reg(vm, inst->registrador1)<<", "<<nome_reg(vm, inst->registrador2)<<"\n";
		}
		break;
		case ADC:
		{
			IAdc *inst = dynamic_cast<IAdc*>(instrucao);
			cout<<"adc "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case ADC_IM:
		{
			IAdcIm *inst = dynamic_cast<IAdcIm*>(instrucao);
			cout<<"adc "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case SUB:
		{
			ISub *inst = dynamic_cast<ISub*>(instrucao);
			cout<<"sub "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case SUB_IM:
		{
			ISubIm *inst = dynamic_cast<ISubIm*>(instrucao);
			cout<<"sub "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case MULT:
		{
			IMult *inst = dynamic_cast<IMult*>(instrucao);
			cout<<"mult "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case MULT_IM:
		{
			IMultIm *inst = dynamic_cast<IMultIm*>(instrucao);
			cout<<"mult "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";	
		}
		break;
		case DIV:
		{
			IDiv *inst = dynamic_cast<IDiv*>(instrucao);
			cout<<"div "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";	
		}
		break;
		case DIV_IM:
		{
			IDivIm *inst = dynamic_cast<IDivIm*>(instrucao);
			cout<<"div "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case CMP:
		{
			ICmp *inst = dynamic_cast<ICmp*>(instrucao);
			cout<<"cmp "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case CMP_IM:
		{
			ICmpIm *inst = dynamic_cast<ICmpIm*>(instrucao);
			cout<<"cmp "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case SALTO:
		{
			ISalto *inst = dynamic_cast<ISalto*>(instrucao);
			cout<<"si "<<inst->offset<<"\n";
		}
		break;
		case SALTO_EQ:
		{
			ISaltoEq *inst = dynamic_cast<ISaltoEq*>(instrucao);
			cout<<"seq "<<inst->offset<<"\n";
		}
		break;
		case SALTO_MAIOR:
		{
			ISaltoMaior *inst = dynamic_cast<ISaltoMaior*>(instrucao);
			cout<<"smq "<<inst->offset<<"\n";
		}
		break;
		case SALTO_NAO_EQ:
		{
			ISaltoNaoEq *inst = dynamic_cast<ISaltoNaoEq*>(instrucao);
			cout<<"sne "<<inst->offset<<"\n";
		}
		break;
		case SALTO_MAIOR_EQ:
		{
			ISaltoMaiorEq *inst = dynamic_cast<ISaltoMaiorEq*>(instrucao);
			cout<<"sme "<<inst->offset<<"\n";
		}
		break;
		case SALTO_MENOR:
		{
			ISaltoMenor *inst = dynamic_cast<ISaltoMenor*>(instrucao);
			cout<<"sme "<<inst->offset<<"\n";
		}
		break;
		case SALTO_MENOR_EQ:
		{
			ISaltoMenorEq *inst = dynamic_cast<ISaltoMenorEq*>(instrucao);
			cout<<"smeq "<<inst->offset<<"\n";
		}
		break;
		case PARAR:
		{
			IParar *inst = dynamic_cast<IParar*>(instrucao);
			cout<<"parar\n";
		}
		break;
		case CHAMADA:
		{
			IChamada *inst = dynamic_cast<IChamada*>(instrucao);
			cout<<"inv "<<inst->offset<<"\n";
		}
		break;
		case LEITURA_INT:
		{
			ILeituraInt *inst = dynamic_cast<ILeituraInt*>(instrucao);
			cout<<"lei "<<nome_reg(vm, inst->m)<<"\n";
		}
		break;
		case LEITURA_CAR:
		{
			ILeituraCar *inst = dynamic_cast<ILeituraCar*>(instrucao);
			cout<<"lec "<<nome_reg(vm, inst->m)<<"\n";
		}
		break;
		case LEITURA_REAL:
		{
			ILeituraReal *inst = dynamic_cast<ILeituraReal*>(instrucao);
			cout<<"ler "<<nome_reg(vm, inst->m)<<"\n";
		}
		break;
		case CARREGA:
		{
			ICarrega *inst = dynamic_cast<ICarrega*>(instrucao);
			cout<<"cp "<<nome_reg(vm, inst->registrador)<<", "<<inst->desl<<"["<<nome_reg(vm, inst->offset)<<"]\n";
		}
		break;
		case SALVA:
		{
			ISalva *inst = dynamic_cast<ISalva*>(instrucao);
			cout<<"sp "<<nome_reg(vm, inst->registrador)<<", "<<inst->desl<<"["<<nome_reg(vm, inst->offset)<<"]\n";
		}
		break;
		case E_BIT:
		{
			IEBit *inst = dynamic_cast<IEBit*>(instrucao);
			cout<<"e "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case E_BIT_IM:
		{
			IEBitIm *inst = dynamic_cast<IEBitIm*>(instrucao);
			cout<<"e "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case OU_BIT:
		{
			IOuBit *inst = dynamic_cast<IOuBit*>(instrucao);
			cout<<"ou "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case OU_BIT_IM:
		{
			IOuBitIm *inst = dynamic_cast<IOuBitIm*>(instrucao);
			cout<<"ou "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case XOR_BIT:
		{
			IXorBit *inst = dynamic_cast<IXorBit*>(instrucao);
			cout<<"xor "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case XOR_BIT_IM:
		{
			IXorBitIm *inst = dynamic_cast<IXorBitIm*>(instrucao);
			cout<<"xor "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case SHIFT_DIR:
		{
			IShiftDir *inst = dynamic_cast<IShiftDir*>(instrucao);
			cout<<"shd "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case SHIFT_ESQ:
		{
			IShiftEsq *inst = dynamic_cast<IShiftEsq*>(instrucao);
			cout<<"she "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MAIOR_QUE:
		{
			ILigMaiorQ *inst = dynamic_cast<ILigMaiorQ*>(instrucao);
			cout<<"lmq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MAIOR_QUE_IM:
		{
			ILigMaiorQIm *inst = dynamic_cast<ILigMaiorQIm*>(instrucao);
			cout<<"lmq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MENOR_QUE:
		{
			ILigMenorQ *inst = dynamic_cast<ILigMenorQ*>(instrucao);
			cout<<"lmeq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MENOR_QUE_IM:
		{
			ILigMenorQIm *inst = dynamic_cast<ILigMenorQIm*>(instrucao);
			cout<<"lmeq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MAIOR_EQ:
		{
			ILigMaiorEq *inst = dynamic_cast<ILigMaiorEq*>(instrucao);
			cout<<"lme "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MAIOR_EQ_IM:
		{
			ILigMaiorEqIm *inst = dynamic_cast<ILigMaiorEqIm*>(instrucao);
			cout<<"lme "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MENOR_EQ:
		{
			ILigMenorEq *inst = dynamic_cast<ILigMenorEq*>(instrucao);
			cout<<"lmee "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_MENOR_EQ_IM:
		{
			ILigMenorEqIm *inst = dynamic_cast<ILigMenorEqIm*>(instrucao);
			cout<<"lmee "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_EQ:
		{
			ILigEq *inst = dynamic_cast<ILigEq*>(instrucao);
			cout<<"leq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_EQ_IM:
		{
			ILigEqIm *inst = dynamic_cast<ILigEqIm*>(instrucao);
			cout<<"leq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_NAO_EQ:
		{
			ILigNaoEq *inst = dynamic_cast<ILigNaoEq*>(instrucao);
			cout<<"lne "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case LIG_NAO_EQ_IM:
		{
			ILigNaoEqIm *inst = dynamic_cast<ILigNaoEqIm*>(instrucao);
			cout<<"lne "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case NAO_BIT:
		{
			INaoBit *inst = dynamic_cast<INaoBit*>(instrucao);
			cout<<"nao "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<"\n";
		}
		break;
		case NAO_BIT_IM:
		{
			INaoBitIm *inst = dynamic_cast<INaoBitIm*>(instrucao);
			cout<<"nao "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<"\n";
		}
		break;
		case NADA:
		{
			ICmp *inst = dynamic_cast<ICmp*>(instrucao);
			cout<<"nada\n";
		}
		break;
		case ESCRITA_PALAVRA:
		{
			IEscritaPalavraIm *inst = dynamic_cast<IEscritaPalavraIm*>(instrucao);
			if(inst->palavra->compare("\n")==0||inst->palavra->compare("\r\n")==0)
				cout<<"ecos \\n\n";
			else
				cout<<"ecos "<<inst->palavra->c_str()<<"\n";
		}
		break;
		case ESCRITA_CHAR:
		{
			IEscritaChar *inst = dynamic_cast<IEscritaChar*>(instrucao);
			cout<<"ecoc "<<nome_reg(vm, inst->m)<<"\n";
		}
		break;
		case ESCRITA_CHAR_IM:
		{
			IEscritaCharIm *inst = dynamic_cast<IEscritaCharIm*>(instrucao);
			cout<<"ecoc "<<inst->m<<"\n";
		}
		break;
		case ESCRITA_INT:
		{
			IEscritaInt *inst = dynamic_cast<IEscritaInt*>(instrucao);
			cout<<"eco "<<nome_reg(vm, inst->m)<<"\n";
		}
		break;
		case ESCRITA_INT_IM:
		{
			IEscritaIntIm *inst = dynamic_cast<IEscritaIntIm*>(instrucao);
			cout<<"eco "<<inst->m<<"\n";
		}
		break;
		case ESCRITA_DOUBLE:
		{
			IEscritaDouble *inst = dynamic_cast<IEscritaDouble*>(instrucao);
			cout<<"ecor "<<nome_reg(vm, inst->m)<<"\n";
		}
		break;
		case ESCRITA_DOUBLE_IM:
		{
			IEscritaDoubleIm *inst = dynamic_cast<IEscritaDoubleIm*>(instrucao);
			cout<<"ecor "<<inst->m<<"\n";
		}
		break;
		case RET:
		{
			IRet *inst = dynamic_cast<IRet*>(instrucao);
			cout<<"ret "<<nome_reg(vm, inst->registrador)<<"\n";
		}
		break;
		case TROCA:
		{
			ITroca *inst = dynamic_cast<ITroca*>(instrucao);
			cout<<"trc "<<nome_reg(vm, inst->registrador1)<<", "<<nome_reg(vm, inst->registrador2)<<"\n";
		}
		break;
		case RESTO:
		{
			IResto *inst = dynamic_cast<IResto*>(instrucao);
			cout<<"rest "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case RESTO_IM:
		{
			IRestoIm *inst = dynamic_cast<IRestoIm*>(instrucao);
			cout<<"rest "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case NEG:
		{
			INeg *inst = dynamic_cast<INeg*>(instrucao);
			cout<<"neg "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<"\n";
		}
		break;
		case NEG_IM:
		{
			INegIm *inst = dynamic_cast<INegIm*>(instrucao);
			cout<<"neg "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<"\n";
		}
		break;
		case BOOLEAN:
		{
			IBoolean *inst = dynamic_cast<IBoolean*>(instrucao);
			cout<<"bool "<<nome_reg(vm, inst->registrador)<<"\n";
		}
		break;
		case POTENCIA:
		{
			IPotencia *inst = dynamic_cast<IPotencia*>(instrucao);
			cout<<"pot "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case POTENCIA_IM:
		{
			IPotenciaIm *inst = dynamic_cast<IPotenciaIm*>(instrucao);
			cout<<"pot "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2)<<"\n";
		}
		break;
		case SISTEMA:
		{
			ISistema *inst = dynamic_cast<ISistema*>(instrucao);
			cout<<"sis "<<nome_comando(inst->comando)<<"\n";
		}
		break;
	}
}

string nome_reg(MaquinaVirtual &vm, CelulaMemoria &celula)
{
	if(&vm.eax == &celula)
		return "eax";
	if(&vm.ebx == &celula)
		return "ebx";
	if(&vm.ecx == &celula)
		return "ecx";
	if(&vm.edx == &celula)
		return "edx";
	if(&vm.pp == &celula)
		return "pp";
	if(&vm.bp == &celula)
		return "bp";
	if(&vm.er == &celula)
		return "er";
	if(&vm.pg == &celula)
		return "pg";

	char temp[30];
	sprintf(temp, "%d", celula.toInt());

	return temp;
}

string nome_tipo_cast(TipoVariavel::TipoVariavel tipo)
{
	if(tipo == TipoVariavel::TIPO_INT)
		return "INT";
	if(tipo == TipoVariavel::TIPO_CAR)
		return "CAR";

	return "REAL";
}

string nome_comando(Sistema::Comando comando)
{
	switch(comando)
	{
		case Sistema::LIMPAR:
		{
			return "limpar";
		}
		break;
	}
}