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

TipoInstrucao::TipoInstrucao IMove::tipoInstucao()
{
    return TipoInstrucao::MOVE;
}

IMoveIm::IMoveIm(MaquinaVirtual &vm, Celula &para, Celula de)
    : Instrucao(vm), registrador1(para), registrador2(de) { }

IMoveIm::IMoveIm(MaquinaVirtual &vm, Celula &para, char de)
    : Instrucao(vm), registrador1(para), registrador2(de) { }

IMoveIm::IMoveIm(MaquinaVirtual &vm, Celula &para, int de)
    : Instrucao(vm), registrador1(para), registrador2(de) { }

IMoveIm::IMoveIm(MaquinaVirtual &vm, Celula &para, double de)
    : Instrucao(vm), registrador1(para), registrador2(de) { }

void IMoveIm::execute()
{
    registrador1 = registrador2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IMoveIm::tipoInstucao()
{
    return TipoInstrucao::MOVE_IM;
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

TipoInstrucao::TipoInstrucao ISalto::tipoInstucao()
{
    return TipoInstrucao::SALTO;
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

TipoInstrucao::TipoInstrucao IAdc::tipoInstucao()
{
    return TipoInstrucao::ADC;
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

TipoInstrucao::TipoInstrucao ISub::tipoInstucao()
{
    return TipoInstrucao::SUB;
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

TipoInstrucao::TipoInstrucao IMult::tipoInstucao()
{
    return TipoInstrucao::MULT;
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

TipoInstrucao::TipoInstrucao IDiv::tipoInstucao()
{
    return TipoInstrucao::DIV;
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

TipoInstrucao::TipoInstrucao ICmp::tipoInstucao()
{
    return TipoInstrucao::CMP;
}

ICmpIm::ICmpIm(MaquinaVirtual &vm, Celula &operando1, Celula operando2)
    : Instrucao(vm), operando1(operando1), operando2(operando2) { }
ICmpIm::ICmpIm(MaquinaVirtual &vm, Celula &operando1, int operando2)
    : Instrucao(vm), operando1(operando1), operando2(operando2) { }
    
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

TipoInstrucao::TipoInstrucao ICmpIm::tipoInstucao()
{
    return TipoInstrucao::CMP_IM;
}

ISaltoEq::ISaltoEq(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset) { }

ISaltoEq::~ISaltoEq() { }

void ISaltoEq::execute()
{
    if(vm.ef)
        ISalto::execute();
    else
        ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISaltoEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_EQ;
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

TipoInstrucao::TipoInstrucao ISaltoMaior::tipoInstucao()
{
    return TipoInstrucao::SALTO_MAIOR;
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

TipoInstrucao::TipoInstrucao ISaltoNaoEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_NAO_EQ;
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

TipoInstrucao::TipoInstrucao ISaltoMaiorEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_MAIOR_EQ;
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

TipoInstrucao::TipoInstrucao ISaltoMenor::tipoInstucao()
{
    return TipoInstrucao::SALTO_MENOR;
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

TipoInstrucao::TipoInstrucao ISaltoMenorEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_MENOR_EQ;
}

IParar::IParar(MaquinaVirtual &vm)
    : Instrucao(vm)
{

}

void IParar::execute()
{
    vm.parar();
}

TipoInstrucao::TipoInstrucao IParar::tipoInstucao()
{
    return TipoInstrucao::PARAR;
}

IChamada::IChamada(MaquinaVirtual &vm, int &offset)
    : ISalto(vm, offset) {}

void IChamada::execute()
{
    vm.er = vm.pc + 1;
    ISalto::execute();
}

TipoInstrucao::TipoInstrucao IChamada::tipoInstucao()
{
    return TipoInstrucao::CHAMADA;
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

TipoInstrucao::TipoInstrucao ILeituraInt::tipoInstucao()
{
    return TipoInstrucao::LEITURA_INT;
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

TipoInstrucao::TipoInstrucao ILeituraCar::tipoInstucao()
{
    return TipoInstrucao::LEITURA_CAR;
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

TipoInstrucao::TipoInstrucao ILeituraReal::tipoInstucao()
{
    return TipoInstrucao::LEITURA_REAL;
}

ICarrega::ICarrega(MaquinaVirtual &vm, Celula &registrador, Celula &offset, int desl)
    : Instrucao(vm), registrador(registrador), offset(offset), desl(desl)
{
}

void ICarrega::execute()
{
    Celula acessa = offset+desl;
    if(vm.memoria.capacity()<=acessa.toInt())
        vm.memoria.reserve(acessa.toInt()+100);
    if(acessa.toInt()<0)
    {
        vm.erf = true;
        cout<<"ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\nENDERECO MEMORIA: "<<acessa.toInt()<<"\n";
    }
    try
    {
        registrador = vm.memoria[acessa.toInt()];
    }
    catch(exception &e)
    {
        vm.erf = true;
        cout<<"ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\nENDERECO MEMORIA: "<<acessa.toInt()<<"\n";
    }

    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ICarrega::tipoInstucao()
{
    return TipoInstrucao::CARREGA;
}

ISalva::ISalva(MaquinaVirtual &vm, Celula &registrador, Celula &offset, int desl)
    : Instrucao(vm), registrador(registrador), offset(offset), desl(desl)
{
}

void ISalva::execute()
{
    Celula acessa = offset+desl;
    if(vm.memoria.capacity()<=acessa.toInt())
        vm.memoria.reserve(acessa.toInt()+100);
    if(acessa.toInt()<0)
    {
        vm.erf = true;
        cout<<"ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\n";
    }
    try
    {
        vm.memoria[acessa.toInt()] = registrador;
    }
    catch(exception &e)
    {
        vm.erf = true;
        cout<<"ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\n";
    }
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISalva::tipoInstucao()
{
    return TipoInstrucao::SALVA;
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

TipoInstrucao::TipoInstrucao IEBit::tipoInstucao()
{
    return TipoInstrucao::E_BIT;
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

TipoInstrucao::TipoInstrucao IEBitIm::tipoInstucao()
{
    return TipoInstrucao::E_BIT_IM;
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

TipoInstrucao::TipoInstrucao IOuBit::tipoInstucao()
{
    return TipoInstrucao::OU_BIT;
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

TipoInstrucao::TipoInstrucao IOuBitIm::tipoInstucao()
{
    return TipoInstrucao::OU_BIT_IM;
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

TipoInstrucao::TipoInstrucao IXorBit::tipoInstucao()
{
    return TipoInstrucao::XOR_BIT;
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

TipoInstrucao::TipoInstrucao IXorBitIm::tipoInstucao()
{
    return TipoInstrucao::XOR_BIT_IM;
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

TipoInstrucao::TipoInstrucao IShiftDir::tipoInstucao()
{
    return TipoInstrucao::SHIFT_DIR;
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

TipoInstrucao::TipoInstrucao IShiftEsq::tipoInstucao()
{
    return TipoInstrucao::SHIFT_ESQ;
}

ILigMaiorQ::ILigMaiorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMaiorQ::execute()
{
    if(operando1 > operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMaiorQ::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_QUE;
}

ILigMaiorQIm::ILigMaiorQIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMaiorQIm::execute()
{
    if(operando1 > operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMaiorQIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_QUE_IM;
}

ILigMenorQ::ILigMenorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMenorQ::execute()
{
    if(operando1 < operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMenorQ::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_QUE;
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

TipoInstrucao::TipoInstrucao ILigMenorQIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_QUE_IM;
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

TipoInstrucao::TipoInstrucao ILigMaiorEq::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_EQ;
}

ILigMaiorEqIm::ILigMaiorEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMaiorEqIm::execute()
{
    if(operando1 >= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMaiorEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_EQ_IM;
}


ILigMenorEq::ILigMenorEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMenorEq::execute()
{
    if(operando1 <= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMenorEq::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_EQ;
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

TipoInstrucao::TipoInstrucao ILigMenorEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_EQ_IM;
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

TipoInstrucao::TipoInstrucao ILigEq::tipoInstucao()
{
    return TipoInstrucao::LIG_EQ;
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

TipoInstrucao::TipoInstrucao ILigEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_EQ_IM;
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

TipoInstrucao::TipoInstrucao ILigNaoEq::tipoInstucao()
{
    return TipoInstrucao::LIG_NAO_EQ;
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

TipoInstrucao::TipoInstrucao ILigNaoEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_NAO_EQ_IM;
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

TipoInstrucao::TipoInstrucao INaoBit::tipoInstucao()
{
    return TipoInstrucao::NAO_BIT;
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

TipoInstrucao::TipoInstrucao INaoBitIm::tipoInstucao()
{
    return TipoInstrucao::NAO_BIT_IM;
}

INada::INada(MaquinaVirtual &vm)
    : Instrucao(vm)
{

}
void INada::execute()
{
    ++vm.pc;
}


TipoInstrucao::TipoInstrucao INada::tipoInstucao()
{
    return TipoInstrucao::NADA;
}

IEscritaPalavraIm::IEscritaPalavraIm(MaquinaVirtual &vm, string *palavra)
    :Instrucao(vm), palavra(palavra) { }

void IEscritaPalavraIm::execute()
{
    vm.escrevePalavra(palavra);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaPalavraIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_PALAVRA;
}

IEscritaChar::IEscritaChar(MaquinaVirtual &vm, Celula &m)
    : Instrucao(vm), m(m) { }

void IEscritaChar::execute()
{
     vm.escreveChar(m.toChar());
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaChar::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_CHAR;
}

IEscritaCharIm::IEscritaCharIm(MaquinaVirtual &vm, int m)
    : Instrucao(vm), m(m) { }

void IEscritaCharIm::execute()
{
    vm.escreveChar((char)m);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaCharIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_CHAR_IM;
}

IEscritaInt::IEscritaInt(MaquinaVirtual &vm, Celula &m)
    : Instrucao(vm), m(m) { }

void IEscritaInt::execute()
{
    vm.escreveInt(m.toInt());
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaInt::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_INT;
}

IEscritaIntIm::IEscritaIntIm(MaquinaVirtual &vm, int m)
    : Instrucao(vm), m(m) { }

void IEscritaIntIm::execute()
{
    vm.escreveInt(m);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaIntIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_INT_IM;
}

IEscritaDouble::IEscritaDouble(MaquinaVirtual &vm, Celula &m)
   : Instrucao(vm), m(m) { }

void IEscritaDouble::execute()
{
    vm.escreveDouble(m.toDouble());
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaDouble::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_DOUBLE;
}

IEscritaDoubleIm::IEscritaDoubleIm(MaquinaVirtual &vm, double m)
   : Instrucao(vm), m(m) { }

void IEscritaDoubleIm::execute()
{
    vm.escreveDouble(m);
    ++vm.pc;
}


TipoInstrucao::TipoInstrucao IEscritaDoubleIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_DOUBLE_IM;
}

IAdcIm::IAdcIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void IAdcIm::execute()
{
    registrador = operando1 + operando2; 
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IAdcIm::tipoInstucao()
{
    return TipoInstrucao::ADC_IM;
}

ISubIm::ISubIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula  operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void ISubIm::execute()
{
    registrador = operando1 - operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISubIm::tipoInstucao()
{
    return TipoInstrucao::SUB_IM;
}

IMultIm::IMultIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

void IMultIm::execute()
{
    registrador = operando1 * operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IMultIm::tipoInstucao()
{
    return TipoInstrucao::MULT_IM;
}

IDivIm::IDivIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) { }

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

TipoInstrucao::TipoInstrucao IDivIm::tipoInstucao()
{
    return TipoInstrucao::DIV_IM;
}

IRet::IRet(MaquinaVirtual &vm, Celula &registrador)
    : Instrucao(vm), registrador(registrador) { }

void IRet::execute()
{
    vm.pc = registrador.toInt();
}

TipoInstrucao::TipoInstrucao IRet::tipoInstucao()
{
    return TipoInstrucao::RET;
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

TipoInstrucao::TipoInstrucao ITroca::tipoInstucao()
{
    return TipoInstrucao::TROCA;
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

TipoInstrucao::TipoInstrucao IResto::tipoInstucao()
{
    return TipoInstrucao::RESTO;
}

IRestoIm::IRestoIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    :Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2) {}
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

TipoInstrucao::TipoInstrucao IRestoIm::tipoInstucao()
{
    return TipoInstrucao::RESTO_IM;
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

TipoInstrucao::TipoInstrucao INeg::tipoInstucao()
{
    return TipoInstrucao::NEG;
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

TipoInstrucao::TipoInstrucao INegIm::tipoInstucao()
{
    return TipoInstrucao::NEG_IM;
}

IBoolean::IBoolean(MaquinaVirtual &vm, Celula &registrador)
    : Instrucao(vm), registrador(registrador) { }
void IBoolean::execute()
{
    registrador.convToInt();
    if(registrador!= 0)
        registrador = 1;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IBoolean::tipoInstucao()
{
    return TipoInstrucao::BOOLEAN;
}

IPotencia::IPotencia(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IPotencia::execute()
{
    registrador = operando1.pot(operando2);
    ++vm.pc;
}


TipoInstrucao::TipoInstrucao IPotencia::tipoInstucao()
{
    return TipoInstrucao::POTENCIA;
}


IPotenciaIm::IPotenciaIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void IPotenciaIm::execute()
{
    registrador = operando1.pot(operando2);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IPotenciaIm::tipoInstucao()
{
    return TipoInstrucao::POTENCIA_IM;
}

ICast::ICast(MaquinaVirtual &vm, Celula &registrador, TipoVariavel::TipoVariavel tipo)
    : Instrucao(vm), registrador(registrador), tipo(tipo) { }
void ICast::execute()
{
    if(tipo == TipoVariavel::TIPO_INT)
    {
        registrador.convToInt();
    }
    else if(tipo == TipoVariavel::TIPO_CAR)
    {
        registrador.convToChar();
    }
    else
    {
        registrador.convToDouble();
    }
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ICast::tipoInstucao()
{
    return TipoInstrucao::CAST;
}

ISistema::ISistema(MaquinaVirtual &vm, Sistema::Comando comando)
    : Instrucao(vm), comando(comando) { }

void ISistema::execute()
{
    vm.sistema(comando);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISistema::tipoInstucao()
{
    return TipoInstrucao::SISTEMA;
}