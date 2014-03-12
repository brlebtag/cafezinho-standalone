#include "Instrucao.h"
#include "MaquinaVirtual.h"

Instrucao::Instrucao(MaquinaVirtual &vm)
    :vm(vm)
{

}

Instrucao::~Instrucao()
{
}

IMove::IMove(MaquinaVirtual &vm, Celula& para, Celula & de)
    : Instrucao(vm), registrador1(para), registrador2(de)
{
}

void IMove::execute()
{
    registrador1 = registrador2;
    ++vm.pc;
}


IMoveIm::IMoveIm(MaquinaVirtual &vm, Celula &para, Celula de)
    : Instrucao(vm), registrador1(para), registrador2(de)
{

}
void IMoveIm::execute()
{
    registrador1 = registrador2;
    ++vm.pc;
}

ISalto::ISalto(MaquinaVirtual &vm, int &offset)
    : Instrucao(vm), offset(offset) { }


ISalto::~ISalto()
{

}

void ISalto::execute()
{
    vm.pc = offset;
}


IAdc::IAdc(MaquinaVirtual &vm, Celula& registrador, Celula& operando1, Celula& operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IAdc::execute()
{
    registrador = operando1 + operando2;
    ++vm.pc;
}

ISub::ISub(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void ISub::execute()
{
    registrador = operando1 - operando2;
    ++vm.pc;
}


IMult::IMult(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IMult::execute()
{
    registrador = operando1 * operando2;
    ++vm.pc;
}


IDiv::IDiv(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IDiv::execute()
{
    if(operando2==0)
    {
        cout<<"ERRO DIVISAO POR ZERO\n";
        vm.erf = true;
        return;
    }
    registrador = operando1 / operando2;
    ++vm.pc;
}


ICmp::ICmp(MaquinaVirtual &vm, Celula &operando1, Celula &operando2)
    : Instrucao(vm), operando1(operando1), operando2(operando2)
{
}

void ICmp::execute()
{
    if(operando1 > operando2)
    {
        vm.bf = true;
        vm.sf = false;
        vm.ef = false;
    }
    else if(operando1 < operando2)
    {
        vm.bf = false;
        vm.sf = true;
        vm.ef = false;
    }
    else
    {
        vm.bf = false;
        vm.sf = false;
        vm.ef = true;
    }
    ++vm.pc;
}

ICmpIm::ICmpIm(MaquinaVirtual &vm, Celula &operando1, Celula operando2)
    : Instrucao(vm), operando1(operando1), operando2(operando2)
{

}
void ICmpIm::execute()
{
    if(operando1 > operando2)
    {
        vm.bf = true;
        vm.sf = false;
        vm.ef = false;
    }
    else if(operando1 < operando2)
    {
        vm.bf = false;
        vm.sf = true;
        vm.ef = false;
    }
    else
    {
        vm.bf = false;
        vm.sf = false;
        vm.ef = true;
    }
    ++vm.pc;
}



ISaltoEq::ISaltoEq(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset)
{
}

ISaltoEq::~ISaltoEq()
{
}

void ISaltoEq::execute()
{
    if(vm.ef)
        ISalto::execute();
    else
        ++vm.pc;
}

ISaltoMaior::ISaltoMaior(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset)
{
}

ISaltoMaior::~ISaltoMaior()
{
}


void ISaltoMaior::execute()
{
    if(vm.bf)
        ISalto::execute();
    else
        ++vm.pc;
}

ISaltoNaoEq::ISaltoNaoEq(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset)
{

}
ISaltoNaoEq::~ISaltoNaoEq()
{

}
void ISaltoNaoEq::execute()
{
    if(!vm.ef)
        ISalto::execute();
    else
        ++vm.pc;
}


ISaltoMaiorEq::ISaltoMaiorEq(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset)
{
}

ISaltoMaiorEq::~ISaltoMaiorEq()
{
}

void ISaltoMaiorEq::execute()
{
    if(vm.bf||vm.ef)
        ISalto::execute();
    else
        ++vm.pc;
}


ISaltoMenor::ISaltoMenor(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset)
{
}

ISaltoMenor::~ISaltoMenor()
{
}


void ISaltoMenor::execute()
{
    if(vm.sf)
        ISalto::execute();
    else
        ++vm.pc;
}

ISaltoMenorEq::ISaltoMenorEq(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset)
{
}

ISaltoMenorEq::~ISaltoMenorEq()
{
}

void ISaltoMenorEq::execute()
{
    if(vm.sf||vm.ef)
        ISalto::execute();
    else
        ++vm.pc;
}

IParar::IParar(MaquinaVirtual &vm)
    : Instrucao(vm)
{

}

void IParar::execute()
{
    vm.parar();
}


IChamada::IChamada(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset)
{
}

void IChamada::execute()
{
    vm.er = vm.pc + 1;
    ISalto::execute();
}


ILeituraInt::ILeituraInt(MaquinaVirtual &vm, Celula &m)
    : Instrucao(vm), m(m)
{
}

void ILeituraInt::execute()
{
    m = vm.leInt();
    ++vm.pc;
}


ILeituraCar::ILeituraCar(MaquinaVirtual &vm, Celula &m)
    : Instrucao(vm), m(m)
{
}

void ILeituraCar::execute()
{

    m = vm.leChar();
    ++vm.pc;
}

ILeituraReal::ILeituraReal(MaquinaVirtual &vm, Celula &m)
    : Instrucao(vm), m(m)
{

}

void ILeituraReal::execute()
{
    m = vm.leDouble();
    ++vm.pc;
}


ICarrega::ICarrega(MaquinaVirtual &vm, Celula &registrador, Celula &offset, int desl)
    : Instrucao(vm), registrador(registrador), offset(offset), desl(desl)
{
}

void ICarrega::execute()
{
    Celula acessa = offset+desl;
    if(vm.memoria.capacity()<acessa.toInt())
        vm.memoria.reserve(acessa.toInt()+10);
    if(acessa.toInt()<0)
    {
        vm.erf = true;
        cout<<"ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\n";
    }
    registrador = vm.memoria[acessa.toInt()];
    ++vm.pc;
}


ISalva::ISalva(MaquinaVirtual &vm, Celula &registrador, Celula &offset, int desl)
    : Instrucao(vm), registrador(registrador), offset(offset), desl(desl)
{
}

void ISalva::execute()
{
    Celula acessa = offset+desl;
    if(vm.memoria.capacity()<acessa.toInt())
        vm.memoria.reserve(acessa.toInt()+10);
    if(acessa.toInt()<0)
    {
        vm.erf = true;
        cout<<"ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\n";
    }
    vm.memoria[acessa.toInt()] = registrador;
    ++vm.pc;
}

IEBit::IEBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IEBit::execute()
{
    registrador = operando1 & operando2;
    ++vm.pc;
}

IEBitIm::IEBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IEBitIm::execute()
{
    registrador = operando1 & operando2;
    ++vm.pc;
}


IOuBit::IOuBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IOuBit::execute()
{
    registrador = operando1 | operando2;
    ++vm.pc;
}

IOuBitIm::IOuBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IOuBitIm::execute()
{
    registrador = operando1 | operando2;
    ++vm.pc;
}


IXorBit::IXorBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IXorBit::execute()
{
    registrador = operando1 ^ operando2;
    ++vm.pc;
}

IXorBitIm::IXorBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IXorBitIm::execute()
{
    registrador = operando1 ^ operando2;
    ++vm.pc;
}


IShiftDir::IShiftDir(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IShiftDir::execute()
{
    registrador = operando1 >> operando2;
    ++vm.pc;
}


IShiftEsq::IShiftEsq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IShiftEsq::execute()
{
    registrador = operando1 << operando2;
    ++vm.pc;
}


ILigMaiorQ::ILigMaiorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMaiorQ::execute()
{
    if(operando1 > operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigMaiorQIm::ILigMaiorQIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMaiorQIm::execute()
{
    if(operando1 > operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigMenorQ::ILigMenorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMenorQ::execute()
{
    if(operando1 < operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigMenorQIm::ILigMenorQIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void ILigMenorQIm::execute()
{
    if(operando1 < operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigMaiorEq::ILigMaiorEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMaiorEq::execute()
{
    if(operando1 >= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigMaiorEqIm::ILigMaiorEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMaiorEqIm::execute()
{
    if(operando1 >= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigMenorEq::ILigMenorEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMenorEq::execute()
{
    if(operando1 <= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigMenorEqIm::ILigMenorEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMenorEqIm::execute()
{
    if(operando1 <= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigEq::ILigEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigEq::execute()
{
    if(operando1 == operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigEqIm::ILigEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigEqIm::execute()
{
    if(operando1 == operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigNaoEq::ILigNaoEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigNaoEq::execute()
{
    if(operando1 != operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

ILigNaoEqIm::ILigNaoEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigNaoEqIm::execute()
{
    if(operando1 != operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

INaoBit::INaoBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1)
    : Instrucao(vm), registrador(registrador), operando1(operando1)
{

}
void INaoBit::execute()
{
    registrador = ~ operando1;
    ++vm.pc;
}

INaoBitIm::INaoBitIm(MaquinaVirtual &vm, Celula &registrador, Celula operando1)
    : Instrucao(vm), registrador(registrador), operando1(operando1)
{

}
void INaoBitIm::execute()
{
    registrador = ~ operando1;
    ++vm.pc;
}

INada::INada(MaquinaVirtual &vm)
    : Instrucao(vm)
{

}
void INada::execute()
{
    ++vm.pc;
}

IEscritaPalavraIm::IEscritaPalavraIm(MaquinaVirtual &vm, string *palavra)
    :Instrucao(vm), palavra(palavra) { }

void IEscritaPalavraIm::execute()
{
    vm.escrevePalavra(palavra);
    ++vm.pc;
}

IEscritaChar::IEscritaChar(MaquinaVirtual &vm, Celula &m)
    : Instrucao(vm), m(m) { }

void IEscritaChar::execute()
{
     vm.escreveChar(m.toChar());
    ++vm.pc;
}

IEscritaCharIm::IEscritaCharIm(MaquinaVirtual &vm, int m)
    : Instrucao(vm), m(m) { }

void IEscritaCharIm::execute()
{
    vm.escreveChar((char)m);
    ++vm.pc;
}

IEscritaInt::IEscritaInt(MaquinaVirtual &vm, Celula &m)
    : Instrucao(vm), m(m) { }

void IEscritaInt::execute()
{
    vm.escreveInt(m.toInt());
    ++vm.pc;
}

IEscritaIntIm::IEscritaIntIm(MaquinaVirtual &vm, int m)
    : Instrucao(vm), m(m) { }

void IEscritaIntIm::execute()
{
    vm.escreveInt(m);
    ++vm.pc;
}

IEscritaDouble::IEscritaDouble(MaquinaVirtual &vm, Celula &m)
   : Instrucao(vm), m(m) { }

void IEscritaDouble::execute()
{
    vm.escreveDouble(m.toDouble());
    ++vm.pc;
}
IEscritaDoubleIm::IEscritaDoubleIm(MaquinaVirtual &vm, double m)
   : Instrucao(vm), m(m) { }
void IEscritaDoubleIm::execute()
{
    vm.escreveDouble(m);
    ++vm.pc;
}


IAdcIm::IAdcIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}
void IAdcIm::execute()
{
    registrador = operando1 + operando2; 
    ++vm.pc;
}

ISubIm::ISubIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula  operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}
void ISubIm::execute()
{
    registrador = operando1 - operando2;
    ++vm.pc;
}

IMultIm::IMultIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}
void IMultIm::execute()
{
    registrador = operando1 * operando2;
    ++vm.pc;
}

IDivIm::IDivIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}
void IDivIm::execute()
{
    if(operando2==0)
    {
        cout<<"ERRO DIVISAO POR ZERO\n";
        vm.erf = true;
        return;
    }
    registrador = operando1 / operando2;
    ++vm.pc;
}

IRet::IRet(MaquinaVirtual &vm, Celula &registrador)
    : Instrucao(vm), registrador(registrador) { }

void IRet::execute()
{
    vm.pc = registrador.toInt();
}

ITroca::ITroca(MaquinaVirtual &vm, Celula &registrador1, Celula &registrador2)
    :Instrucao(vm), registrador1(registrador1), registrador2(registrador2)
{

}

void ITroca::execute()
{
    Celula temp = registrador2;
    registrador2 = registrador1;
    registrador1 = temp;
    ++vm.pc;
}

IResto::IResto(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    :Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IResto::execute()
{
    if(operando2==0)
    {
        cout<<"ERRO DIVISAO POR ZERO\n";
        vm.erf = true;
        return;
    }
    registrador = operando1 % operando2;
    ++vm.pc;
}
IRestoIm::IRestoIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    :Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IRestoIm::execute()
{
    if(operando2==0)
    {
        cout<<"ERRO DIVISAO POR ZERO\n";
        vm.erf = true;
        return;
    }
    registrador = operando1 % operando2;
    ++vm.pc;
}

INeg::INeg(MaquinaVirtual &vm, Celula &registrador, Celula &operando1)
    :Instrucao(vm), registrador(registrador), operando1(operando1)
{

}
void INeg::execute()
{
    registrador = (-(operando1));
    ++vm.pc;
}
INegIm::INegIm(MaquinaVirtual &vm, Celula &registrador, Celula operando1)
    :Instrucao(vm), registrador(registrador), operando1(operando1)
{

}
void INegIm::execute()
{
    registrador = - operando1;
    ++vm.pc;
}

IBoolean::IBoolean(MaquinaVirtual &vm, Celula &registrador)
    : Instrucao(vm), registrador(registrador) { }
void IBoolean::execute()
{
    if(registrador!= 0)
        registrador = 1;
    ++vm.pc;
}

IPotencia(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void execute()
{
    registrador = operando1.pot(operando2);
    ++vm.pc;
}

IPotenciaIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void execute()
{
    registrador = operando1.pot(operando2);
    ++vm.pc;
}


ICast(MaquinaVirtual &vm, Celula &registrador, TipoVariavel::TipoVariavel tipo)
    : Instrucao(vm), registrador(registrador), tipo(tipo)
{

}
void execute()
{
    if(tipo == TipoVariavel::TIPO_INT || tipo == TipoVariavel::TIPO_CAR)
    {
        if(registrador.tipo == REAL)
            registrador.convToInt();
    }
    else
    {
        if(registrador.tipo == INTEIRO)
            registrador.convToDouble();
    }
    ++vm.pc;
}