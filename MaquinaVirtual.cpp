#include "MaquinaVirtual.h"
#include "Instrucao.h"

MaquinaVirtual::MaquinaVirtual()
{
    pc = 0;
    pp = 0;
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
    bp = 0;
    er = 0;
    pg = 0;
    bf = false;
    sf = false;
    ef = false;
    erf = false;
}

MaquinaVirtual::~MaquinaVirtual()
{
    //remove todas as instruções criadas...
    try
    {
        for(int i=0; i<codigo.size(); i++)
        delete codigo[i];
    }
    catch(exception &e)
    {

    }
    
}

void MaquinaVirtual::executar()
{
    execute = true;
}

void MaquinaVirtual::parar()
{
    execute = false;
}

void MaquinaVirtual::rodar()
{
    while(execute&&(!erf))
    {
        codigo[pc]->execute();
        if(pc<0||pc>=codigo.size())
        {
            cout<<"PROGRAMA ACABOU DE FORMA INESPERADA\n";
            erf = true;
        }
    }
}

void MaquinaVirtual::passo()
{
    if(execute&&(!erf))
        codigo[pc]->execute();
}

void MaquinaVirtual::escreveInt(int c)
{
    cout<<c;
}
void MaquinaVirtual::escreveChar(char c)
{
    cout<<c;
}
void MaquinaVirtual::escreveDouble(double c)
{
    cout<<c;
}
void MaquinaVirtual::escrevePalavra(std::string *palavra)
{
    cout<<palavra->c_str();
}
int MaquinaVirtual::leInt()
{
    int temp;
    cin>>temp;
    return temp;
}
char MaquinaVirtual::leChar()
{
    char temp;
    cin>>temp;
    return temp;
}
double MaquinaVirtual::leDouble()
{
    double temp;
    cin>>temp;
    return temp;
}