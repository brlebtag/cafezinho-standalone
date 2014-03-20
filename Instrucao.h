#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include <iostream>
#include <string>
#include "CelulaMemoria.h"
#include "arvore_abstrata.h"

namespace Sistema
{
    enum Comando
    {
        LIMPAR
    };
};

namespace TipoInstrucao
{
    enum TipoInstrucao
    {
        MOVE,
        MOVE_IM,
        ADC,
        ADC_IM,
        SUB,
        SUB_IM,
        MULT,
        MULT_IM,
        DIV,
        DIV_IM,
        CMP,
        CMP_IM,
        SALTO,
        SALTO_EQ,
        SALTO_MAIOR,
        SALTO_NAO_EQ,
        SALTO_MAIOR_EQ,
        SALTO_MENOR,
        SALTO_MENOR_EQ,
        PARAR,
        CHAMADA,
        LEITURA_INT,
        LEITURA_CAR,
        LEITURA_REAL,
        CARREGA,
        SALVA,
        E_BIT,
        E_BIT_IM,
        OU_BIT,
        OU_BIT_IM,
        XOR_BIT,
        XOR_BIT_IM,
        SHIFT_DIR,
        SHIFT_ESQ,
        LIG_MAIOR_QUE,
        LIG_MAIOR_QUE_IM,
        LIG_MENOR_QUE,
        LIG_MENOR_QUE_IM,
        LIG_MAIOR_EQ,
        LIG_MAIOR_EQ_IM,
        LIG_MENOR_EQ,
        LIG_MENOR_EQ_IM,
        LIG_EQ,
        LIG_EQ_IM,
        LIG_NAO_EQ,
        LIG_NAO_EQ_IM,
        NAO_BIT,
        NAO_BIT_IM,
        NADA,
        ESCRITA_PALAVRA,
        ESCRITA_CHAR,
        ESCRITA_CHAR_IM,
        ESCRITA_INT,
        ESCRITA_INT_IM,
        ESCRITA_DOUBLE,
        ESCRITA_DOUBLE_IM,
        RET,
        TROCA,
        RESTO,
        RESTO_IM,
        NEG,
        NEG_IM,
        BOOLEAN,
        POTENCIA,
        POTENCIA_IM,
        CAST,
        SISTEMA
    };
};

using namespace std;

class MaquinaVirtual;

typedef CelulaMemoria Celula;

class Instrucao
{
public:
    Instrucao(MaquinaVirtual &vm);
    virtual ~Instrucao();
    virtual void execute() = 0;
    virtual TipoInstrucao::TipoInstrucao tipoInstucao()=0;
protected:
    MaquinaVirtual &vm;
};

class IMove : public Instrucao
{
public:
    IMove(MaquinaVirtual &vm, Celula &para, Celula &de);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador1;
    Celula &registrador2;
};

class IMoveIm : public Instrucao
{
public:
    IMoveIm(MaquinaVirtual &vm, Celula &para, Celula de);
    IMoveIm(MaquinaVirtual &vm, Celula &para, char de);
    IMoveIm(MaquinaVirtual &vm, Celula &para, int de);
    IMoveIm(MaquinaVirtual &vm, Celula &para, double de);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador1;
    Celula registrador2;
};

class ISalto : public Instrucao
{
public:
    ISalto(MaquinaVirtual &vm, int &offset);
    virtual ~ISalto();
    virtual void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    int &offset;
};

class IAdc: public Instrucao
{
public:
    IAdc(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ISub: public Instrucao
{
public:
    ISub(MaquinaVirtual &vm, Celula &registrador, Celula  &operando1, Celula  &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IMult: public Instrucao
{
public:
    IMult(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IDiv: public Instrucao
{
public:
    IDiv(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ICmp: public Instrucao
{
public:
    ICmp(MaquinaVirtual &vm, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &operando1;
    Celula &operando2;
};

class ICmpIm: public Instrucao
{
public:
    ICmpIm(MaquinaVirtual &vm, Celula &operando1, Celula operando2);
    ICmpIm(MaquinaVirtual &vm, Celula &operando1, int operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
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
    TipoInstrucao::TipoInstrucao tipoInstucao();
};
//Salto Nao Igual
class ISaltoNaoEq : public ISalto
{
public:
    ISaltoNaoEq(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoNaoEq();
    virtual void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMaior : public ISalto
{
public:
    ISaltoMaior(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMaior();
    virtual void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMaiorEq : public ISalto
{
public:
    ISaltoMaiorEq(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMaiorEq();
    virtual void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMenor : public ISalto
{
public:
    ISaltoMenor(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMenor();
    virtual void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMenorEq : public ISalto
{
public:
    ISaltoMenorEq(MaquinaVirtual &vm, int &offset);
    virtual ~ISaltoMenorEq();
    virtual void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IParar : public Instrucao
{
public:
    IParar(MaquinaVirtual &vm);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IChamada : public ISalto
{
public:
    IChamada(MaquinaVirtual &vm, int &offset);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ILeituraInt : public Instrucao
{
public:
    ILeituraInt(MaquinaVirtual &vm, Celula &m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;

};

class ILeituraCar : public Instrucao
{
public:
    ILeituraCar(MaquinaVirtual &vm, Celula &m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class ILeituraReal : public Instrucao
{
public:
    ILeituraReal(MaquinaVirtual &vm, Celula &m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class ICarrega : public Instrucao
{
public:
    ICarrega(MaquinaVirtual &vm, Celula &registrador, Celula &offset, int desl = 0);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &offset;
    int desl;
};

class ISalva : public Instrucao
{
public:
    ISalva(MaquinaVirtual &vm, Celula &registrador , Celula &offset, int desl = 0);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &offset;
    int desl;
};

class IEBit: public Instrucao
{
public:
    IEBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IEBitIm: public Instrucao
{
public:
    IEBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};


class IOuBit: public Instrucao
{
public:
    IOuBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IOuBitIm: public Instrucao
{
public:
    IOuBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IXorBit: public Instrucao
{
public:
    IXorBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IXorBitIm: public Instrucao
{
public:
    IXorBitIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IShiftDir: public Instrucao
{
public:
    IShiftDir(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IShiftEsq: public Instrucao
{
public:
    IShiftEsq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class INaoBit: public Instrucao
{
public:
    INaoBit(MaquinaVirtual &vm, Celula &registrador, Celula &operando1);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
};

class INaoBitIm: public Instrucao
{
public:
    INaoBitIm(MaquinaVirtual &vm, Celula &registrador, Celula operando1);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula operando1;
};

class ILigMaiorQ: public Instrucao
{
public:
    ILigMaiorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMaiorQIm: public Instrucao
{
public:
    ILigMaiorQIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMenorQ: public Instrucao
{
public:
    ILigMenorQ(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMenorQIm: public Instrucao
{
public:
    ILigMenorQIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMaiorEq: public Instrucao
{
public:
    ILigMaiorEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMaiorEqIm: public Instrucao
{
public:
    ILigMaiorEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMenorEq: public Instrucao
{
public:
    ILigMenorEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMenorEqIm: public Instrucao
{
public:
    ILigMenorEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigEq: public Instrucao
{
public:
    ILigEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigEqIm: public Instrucao
{
public:
    ILigEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigNaoEq: public Instrucao
{
public:
    ILigNaoEq(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigNaoEqIm: public Instrucao
{
public:
    ILigNaoEqIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class INada: public Instrucao
{
public:
    INada(MaquinaVirtual &vm);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IEscritaPalavraIm : public Instrucao
{
public:
    IEscritaPalavraIm(MaquinaVirtual &vm, string *palavra);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    string *palavra;
};

class IEscritaChar : public Instrucao
{
public:
    IEscritaChar(MaquinaVirtual &vm, Celula &m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class IEscritaCharIm : public Instrucao
{
public:
    IEscritaCharIm(MaquinaVirtual &vm, int m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    int m;
};

class IEscritaInt : public Instrucao
{
public:
    IEscritaInt(MaquinaVirtual &vm, Celula &m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class IEscritaIntIm : public Instrucao
{
public:
    IEscritaIntIm(MaquinaVirtual &vm, int m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    int m;
};

class IEscritaDouble : public Instrucao
{
public:
    IEscritaDouble(MaquinaVirtual &vm, Celula &m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class IEscritaDoubleIm : public Instrucao
{
public:
    IEscritaDoubleIm(MaquinaVirtual &vm, double m);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    double m;
};

class IAdcIm: public Instrucao
{
public:
    IAdcIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ISubIm: public Instrucao
{
public:
    ISubIm(MaquinaVirtual &vm, Celula &registrador, Celula  &operando1, Celula  operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IMultIm: public Instrucao
{
public:
    IMultIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IDivIm: public Instrucao
{
public:
    IDivIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IRet: public Instrucao
{
public:
    IRet(MaquinaVirtual &vm, Celula &registrador);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
};

class ITroca: public Instrucao
{
public:
    ITroca(MaquinaVirtual &vm, Celula &registrador1, Celula &registrador2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador1;
    Celula &registrador2;
};

class IResto: public Instrucao
{
public:
    IResto(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IRestoIm: public Instrucao
{
public:
    IRestoIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class INeg: public Instrucao
{
public:
    INeg(MaquinaVirtual &vm, Celula &registrador, Celula &operando1);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
};

class INegIm: public Instrucao
{
public:
    INegIm(MaquinaVirtual &vm, Celula &registrador, Celula operando1);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula operando1;
};

class IBoolean : public Instrucao
{
public:
    IBoolean(MaquinaVirtual &vm, Celula &registrador);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
};

class IPotencia : public Instrucao
{
public:
    IPotencia(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula &operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IPotenciaIm : public Instrucao
{
public:
    IPotenciaIm(MaquinaVirtual &vm, Celula &registrador, Celula &operando1, Celula operando2);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ICast : public Instrucao
{
public:
    ICast(MaquinaVirtual &vm, Celula &registrador, TipoVariavel::TipoVariavel tipo);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    TipoVariavel::TipoVariavel tipo;
    Celula &registrador;
};

class ISistema: public Instrucao
{
public:
    ISistema(MaquinaVirtual &vm, Sistema::Comando comando);
    void execute();
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Sistema::Comando comando;
};

#endif // INSTRUCAO_H
