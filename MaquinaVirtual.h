#ifndef MAQUINAVIRTUAL_H
#define MAQUINAVIRTUAL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Instrucao.h"
#include "CelulaMemoria.h"


using namespace std;

class MaquinaVirtual
{
public:
    explicit MaquinaVirtual();
    virtual ~MaquinaVirtual();
    void executar();
    void parar();
    void passo();
    void reiniciar();
    int pc; //Contator de programa
    CelulaMemoria pp; //Ponteiro da pilha
    CelulaMemoria eax; // registrador acumulador
    CelulaMemoria ebx; // registrador de proposito geral
    CelulaMemoria ecx; // registrador de proposito geral
    CelulaMemoria edx; // registrador de proposito geral
    CelulaMemoria bp; // ponteiro base pilha (usar como fp do assembly MIPS)
    CelulaMemoria er; // endereço de retorno
    CelulaMemoria pg; // Ponteiro Global...
    bool bf; //flag maior que...
    bool sf; //flag menor que...
    bool ef; //flag igual a...
    bool erf; //Flag indicando erro...
    vector<CelulaMemoria> memoria;
    vector<Instrucao*> codigo;
    vector<int*>rotulo;
    void escreveInt(int c);
    void escreveChar(char c);
    void escreveDouble(double c);
    void escrevePalavra(std::string *palavra);
    int leInt();
    char leChar();
    double leDouble();
    bool execute;
    void sistema(Sistema::Comando comando);
};

#endif // MAQUINAVIRTUAL_H
