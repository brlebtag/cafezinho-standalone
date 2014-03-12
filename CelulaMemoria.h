#ifndef CELULAMEMORIA_H
#define CELULAMEMORIA_H

#include <iostream>
#include <string>
#include <sstream>
#include <math.h> 

using namespace std;

class CelulaMemoria
{
public:
    CelulaMemoria();
    CelulaMemoria(const CelulaMemoria &rhs);
    CelulaMemoria(const int value);
    CelulaMemoria(const double value);
    CelulaMemoria(const char value);
    CelulaMemoria operator=(const CelulaMemoria &rhs);
    CelulaMemoria operator=(const int &rhs);
    CelulaMemoria operator=(const double &rhs);
    CelulaMemoria operator+(const CelulaMemoria &rhs);
    CelulaMemoria operator+(const int &rhs);
    CelulaMemoria operator-(const CelulaMemoria &rhs);
    void operator-();
    CelulaMemoria operator*(const CelulaMemoria &rhs);
    CelulaMemoria operator/(const CelulaMemoria &rhs);
    CelulaMemoria operator&(const CelulaMemoria &rhs);
    CelulaMemoria operator|(const CelulaMemoria &rhs);
    CelulaMemoria operator^(const CelulaMemoria &rhs);
    CelulaMemoria operator>>(const CelulaMemoria &rhs);
    CelulaMemoria operator<<(const CelulaMemoria &rhs);
    CelulaMemoria operator%(const CelulaMemoria &rhs);
    CelulaMemoria operator~();
    CelulaMemoria operator++();
    CelulaMemoria operator++(int);
    CelulaMemoria operator--();
    CelulaMemoria operator--(int);
    CelulaMemoria pot(const CelulaMemoria &rhs);
    CelulaMemoria pot(const double &rhs);
    bool operator==(const CelulaMemoria &rhs);
    bool operator!=(const CelulaMemoria &rhs);
    bool operator>(const CelulaMemoria &rhs);
    bool operator<(const CelulaMemoria &rhs);
    bool operator<=(const CelulaMemoria &rhs);
    bool operator>=(const CelulaMemoria &rhs);
    char toChar();
    int toInt();
    double toDouble();
    void convToInt();
    void convToDouble();
    union
    {
        int inteiro;
        double real;
    }celula;
    enum
    {
        INTEIRO, REAL
    }tipo;
};

#endif // CELULAMEMORIA_H
