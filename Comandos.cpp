#include "GerarCodigo.h"

void inc_pp(MaquinaVirtual &vm, int qtd)
{
	vm.codigo.push_back(new IAdcIm(vm, vm.pp, vm.pp, CelulaMemoria(qtd)));
}

void dec_pp(MaquinaVirtual &vm, int qtd)
{
	vm.codigo.push_back(new ISubIm(vm, vm.pp, vm.pp, CelulaMemoria(qtd)));
}

void empilha(MaquinaVirtual &vm , CelulaMemoria &op)
{
	//empilha op
	vm.codigo.push_back(new ISalva(vm, op, vm.pp));
	
	//incrementa o ponteiro de pilha
	inc_pp(vm, 1);
}

void desempilha(MaquinaVirtual &vm, CelulaMemoria &op)
{
	//decrementa o ponteiro de pilha
	dec_pp(vm, 1);

	//desempilha eax
	vm.codigo.push_back(new ICarrega(vm, op, vm.pp));
}

void cmp(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
	vm.codigo.push_back(new ICmp(vm, op1, op2));
}

void cmp_imm(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria op2)
{
	vm.codigo.push_back(new ICmp(vm, op1, op2));
}

void seq(MaquinaVirtual &vm, int &offset)
{
	vm.codigo.push_back(new ISaltoEq(vm, offset));
}

void si(MaquinaVirtual &vm, int &offset)
{
	vm.codigo.push_back(new ISalto(vm, offset));
}

void invoca(MaquinaVirtual &vm, int &offset)
{
	vm.codigo.push_back(new IChamada(vm, offset));
}

void troca(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
	vm.codigo.push_back(new ITroca(vm, op1, op2));
}

void move(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
	vm.codigo.push_back(new IMove(vm, op1, op2));
}

void carrega(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
	vm.codigo.push_back(new ICarrega(vm, op1, op2));
}

void ret(MaquinaVirtual &vm)
{
	vm.codigo.push_back(new IRet(vm, vm.er));
}