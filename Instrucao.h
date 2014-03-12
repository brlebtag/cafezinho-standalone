#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include <iostream>
#include <string>
#include "CelulaMemoria.h"
#include "arvore_abstrata.h"

using namespace std;

class MaquinaVirtual;

typedef CelulaMemoria Celula;

class Instrucao
{
public:
    Instrucao(MaquinaVirtual &vm);
    virtual ~Instrucao();
    virtual void execute() = 0;
protected:
    MaquinaVirtual &vm;
};

class IMove : public Instrucao
{
public:
    IMove(MaquinaVirtual &vm, Celula &para, Celula &de);
    void execute();
    Celula &registrador1;
    Celula &registrador2;
};

class IMoveIm : public Instrucao
{
public:
    IMoveIm(MaquinaVirtual &vm, Celula &para, Celula de);
    void execute();
    Celula &registrador1;
    Celula registrador2;
};

class ISalto : public Instrucao
{
public:
    ISalto(MaquinaVirtual &vm, int &offset);
    ISalto(MaquinaVirtual &vm, Celula &offset);
    virtual ~ISalto();
    virtual void execute();
    int &offset;
};

class IAdc: public Instrucao
{
public:
    IAdc(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ISub: public Instrucao
{
public:
    ISub(MaquinaVirtual &vm, Celula &registrador, Celula  &operando1, Celula  &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IMult: public Instrucao
{
public:
    IMult(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IDiv: public Instrucao
{
public:
    IDiv(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ICmp: public Instrucao
{
public:
    ICmp(MaquinaVirtual &vm, Celula &operando1, Celula &operando2);
    void execute();
    Celula &operando1;
    Celula &operando2;
};

class ICmpIm: public Instrucao
{
public:
    ICmpIm(MaquinaVirtual &vm, Celula &operando1, Celula operando2);
    void execute();
    Celula &operando1;
    Celula operando2;
};

//Salto Igual
class ISaltoEq : public ISalto
{
public:
    ISaltoEq(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoEq();
    virtual void execute();
};
//Salto Nao Igual
class ISaltoNaoEq : public ISalto
{
public:
    ISaltoNaoEq(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoNaoEq();
    virtual void execute();
};

class ISaltoMaior : public ISalto
{
public:
    ISaltoMaior(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMaior();
    virtual void execute();
};

class ISaltoMaiorEq : public ISalto
{
public:
    ISaltoMaiorEq(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMaiorEq();
    virtual void execute();
};

class ISaltoMenor : public ISalto
{
public:
    ISaltoMenor(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMenor();
    virtual void execute();
};

class ISaltoMenorEq : public ISalto
{
public:
    ISaltoMenorEq(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMenorEq();
    virtual void execute();
};

class IParar : public Instrucao
{
public:
    IParar(MaquinaVirtual &vm);
    void execute();
};

class IChamada : public ISalto
{
public:
    IChamada(MaquinaVirtual &vm, int &offset);
    void execute();
};

class ILeituraInt : public Instrucao
{
public:
    ILeituraInt(MaquinaVirtual &vm, Celula &m);
    void execute();
    Celula &m;
};

class ILeituraCar : public Instrucao
{
public:
    ILeituraCar(MaquinaVirtual &vm, Celula &m);
    void execute();
    Celula &m;
};

class ILeituraReal : public Instrucao
{
public:
    ILeituraReal(MaquinaVirtual &vm, Celula &m);
    void execute();
    Celula &m;
};

class ICarrega : public Instrucao
{
public:
    ICarrega(MaquinaVirtual &vm, Celula &registrador, Celula &offset, int desl = 0);
    void execute();
    Celula &registrador;
    Celula &offset;
    int desl;
};

class ISalva : public Instrucao
{
public:
    ISalva(MaquinaVirtual &vm, Celula &registrador , Celula &offset, int desl = 0);
    void execute();
    Celula &registrador;
    Celula &offset;
    int desl;
};

class IEBit: public Instrucao
{
public:
    IEBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IEBitIm: public Instrucao
{
public:
    IEBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};


class IOuBit: public Instrucao
{
public:
    IOuBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IOuBitIm: public Instrucao
{
public:
    IOuBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IXorBit: public Instrucao
{
public:
    IXorBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IXorBitIm: public Instrucao
{
public:
    IXorBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IShiftDir: public Instrucao
{
public:
    IShiftDir(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IShiftEsq: public Instrucao
{
public:
    IShiftEsq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class INaoBit: public Instrucao
{
public:
    INaoBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1);
    void execute();
    Celula &registrador;
    Celula &operando1;
};

class INaoBitIm: public Instrucao
{
public:
    INaoBitIm(MaquinaVirtual &vm, Celula &registrador, Celula operando1);
    void execute();
    Celula &registrador;
    Celula operando1;
};

class ILigMaiorQ: public Instrucao
{
public:
    ILigMaiorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMaiorQIm: public Instrucao
{
public:
    ILigMaiorQIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMenorQ: public Instrucao
{
public:
    ILigMenorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMenorQIm: public Instrucao
{
public:
    ILigMenorQIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMaiorEq: public Instrucao
{
public:
    ILigMaiorEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMaiorEqIm: public Instrucao
{
public:
    ILigMaiorEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMenorEq: public Instrucao
{
public:
    ILigMenorEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMenorEqIm: public Instrucao
{
public:
    ILigMenorEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigEq: public Instrucao
{
public:
    ILigEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigEqIm: public Instrucao
{
public:
    ILigEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigNaoEq: public Instrucao
{
public:
    ILigNaoEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigNaoEqIm: public Instrucao
{
public:
    ILigNaoEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class INada: public Instrucao
{
public:
    INada(MaquinaVirtual &vm);
    void execute();
};

class IEscritaPalavraIm : public Instrucao
{
public:
    IEscritaPalavraIm(MaquinaVirtual &vm, string *palavra);
    void execute();
    string *palavra;
};

class IEscritaChar : public Instrucao
{
public:
    IEscritaChar(MaquinaVirtual &vm, Celula &m);
    void execute();
    Celula &m;
};

class IEscritaCharIm : public Instrucao
{
public:
    IEscritaCharIm(MaquinaVirtual &vm, int m);
    void execute();
    int m;
};

class IEscritaInt : public Instrucao
{
public:
    IEscritaInt(MaquinaVirtual &vm, Celula &m);
    void execute();
    Celula &m;
};

class IEscritaIntIm : public Instrucao
{
public:
    IEscritaIntIm(MaquinaVirtual &vm, int m);
    void execute();
    int m;
};

class IEscritaDouble : public Instrucao
{
public:
    IEscritaDouble(MaquinaVirtual &vm, Celula &m);
    void execute();
    Celula &m;
};

class IEscritaDoubleIm : public Instrucao
{
public:
    IEscritaDoubleIm(MaquinaVirtual &vm, double m);
    void execute();
    double m;
};

class IAdcIm: public Instrucao
{
public:
    IAdcIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ISubIm: public Instrucao
{
public:
    ISubIm(MaquinaVirtual &vm, Celula &registrador, Celula  &operando1, Celula  operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IMultIm: public Instrucao
{
public:
    IMultIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IDivIm: public Instrucao
{
public:
    IDivIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IRet: public Instrucao
{
public:
    IRet(MaquinaVirtual &vm, Celula &registrador);
    void execute();
    Celula &registrador;
};

class ITroca: public Instrucao
{
public:
    ITroca(MaquinaVirtual &vm, Celula &registrador1, Celula &registrador2);
    void execute();
    Celula &registrador1;
    Celula &registrador2;
};

class IResto: public Instrucao
{
public:
    IResto(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IRestoIm: public Instrucao
{
public:
    IRestoIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class INeg: public Instrucao
{
public:
    INeg(MaquinaVirtual &vm, Celula &registrador, Celula &operando1);
    void execute();
    Celula &registrador;
    Celula &operando1;
};

class INegIm: public Instrucao
{
public:
    INegIm(MaquinaVirtual &vm, Celula &registrador, Celula operando1);
    void execute();
    Celula &registrador;
    Celula operando1;
};

class IBoolean : public Instrucao
{
public:
    IBoolean(MaquinaVirtual &vm, Celula &registrador);
    void execute();
    Celula &registrador;
};

class IPotencia : public Instrucao
{
public:
    IPotencia(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IPotenciaIm : public Instrucao
{
public:
    IPotenciaIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ICast : public Instrucao
{
public:
    ICast(MaquinaVirtual &vm, Celula &registrador, TipoVariavel::TipoVariavel tipo);
    void execute();
    TipoVariavel::TipoVariavel tipo;
    Celula &registrador;
};

#endif // INSTRUCAO_H
