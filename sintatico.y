%{

#include <cstdio>
#include <iostream>


extern "C" int yylex();
extern "C" FILE *yyin;
extern int yylineno;

using namespace std;

void yyerror(const char *s);

%}

%token CAR INT REAL NULO

%token IDENTIFICADOR PALAVRA_LITERAL INT_CONST REAL_CONST CAR_CONST

%token SE ENTAO SENAO ENQUANTO EXECUTE LEIA ESCREVA RETORNE NOVA_LINHA

%token MULT_ATRIBUICAO DIV_ATRIBUICAO MOD_ATRIBUICAO ADICAO_ATRIBUICAO SUBTRACAO_ATRIBUICAO 
%token ESQ_ATRIBUICAO DIR_ATRIBUICAO E_ATRIBUICAO XOR_ATRIBUICAO OU_ATRIBUICAO POT_ATRIBUICAO

%token OU_OP E_OP EQ_OP NE_OP LE_OP GE_OP ESQ_OP DIR_OP POT_OP INC_OP DEC_OP

%start unidade_traducao

%%

unidade_traducao 
	: declaracao_externa 
	| unidade_traducao declaracao_externa 
	;

declaracao_externa
	: definicao_funcao 
	| lista_declaracao
	; 

definicao_funcao
	: tipo_especificador declarador_funcao instrucao_composta
	;

tipo_especificador
	: NULO
	| CAR
	| INT
	| REAL
	;

declarador_funcao
	: IDENTIFICADOR '(' lista_parametro ')'
	| IDENTIFICADOR '(' ')'
	;

lista_parametro
	: declaracao_parametro
	| lista_parametro ',' declaracao_parametro
	;

declaracao_parametro
	: tipo_especificador declarador
	;

declarador
	: IDENTIFICADOR lista_ponteiro_vetor
	| IDENTIFICADOR
	;

lista_ponteiro_vetor
	: '[' ']'
	| '[' expressao_constante ']'
	| lista_ponteiro_vetor '[' ']'
	| lista_ponteiro_vetor '[' expressao_constante ']'
	;

instrucao_composta
	: '{' '}'
	| '{' lista_instrucao'}'
	| '{' lista_declaracao '}'
	| '{' lista_declaracao lista_instrucao '}'
	;

lista_instrucao
	: instrucao
	| lista_instrucao instrucao
	;

instrucao
	: instrucao_composta
	| instrucao_expressao
	| instrucao_decisao
	| instrucao_iteracao
	| instrucao_entrada_saida
	| instrucao_salto
	;

instrucao_expressao
	: ';'
	| expressao ';'
	;

instrucao_decisao
	: SE '(' expressao ')' ENTAO instrucao
	| SE '(' expressao ')' ENTAO instrucao SENAO instrucao
	;

instrucao_iteracao
	: ENQUANTO '(' expressao ')' EXECUTE instrucao
	;
instrucao_entrada_saida
	: LEIA expressao ';'
	| ESCREVA expressao ';'

instrucao_salto
	: RETORNE ';'
	| RETORNE expressao ';'
	;

lista_declaracao
	: declaracao
	| lista_declaracao declaracao
	;

declaracao
	: tipo_especificador inicio_lista_declaracao ';'
	;

inicio_lista_declaracao
	: inicio_declarador
	| inicio_lista_declaracao ',' inicio_declarador
	;

inicio_declarador
	: declarador
	| declarador '=' inicializador
	;

inicializador
	: expressao_atribuicao
	| '{' lista_inicializador '}'
	;

lista_inicializador
	: inicializador
	| lista_inicializador ',' inicializador
	;

expressao_atribuicao
	: expressao_condicional
	| expressao_unaria	operador_atribuicao expressao_atribuicao
	;

operador_atribuicao
	: '='
	| MULT_ATRIBUICAO
	| DIV_ATRIBUICAO
	| MOD_ATRIBUICAO
	| ADICAO_ATRIBUICAO
	| SUBTRACAO_ATRIBUICAO
	| ESQ_ATRIBUICAO
	| DIR_ATRIBUICAO
	| E_ATRIBUICAO
	| XOR_ATRIBUICAO
	| OU_ATRIBUICAO
	| POT_ATRIBUICAO
	;

expressao_condicional
	: expressao_logico_ou
	| expressao_logico_ou '?' expressao ':' expressao_condicional
	;

expressao_logico_ou
	: expressao_logico_e
	| expressao_logico_ou OU_OP expressao_logico_e
	;

expressao_logico_e
	: expressao_inclusivo_ou
	| expressao_logico_e E_OP expressao_inclusivo_ou
	;

expressao_inclusivo_ou
	: expressao_exclusivo_ou
	| expressao_inclusivo_ou '|' expressao_exclusivo_ou
	;

expressao_exclusivo_ou
	: expressao_e
	| expressao_exclusivo_ou '^' expressao_e
	;

expressao_e
	: expressao_igualdade
	| expressao_e '&' expressao_igualdade
	;

expressao_igualdade
	: expressao_relacional
	| expressao_igualdade EQ_OP expressao_relacional
	| expressao_igualdade NE_OP expressao_relacional
	;

expressao_relacional
	: expressao_shift
	| expressao_relacional '<' expressao_shift
	| expressao_relacional '>' expressao_shift
	| expressao_relacional LE_OP expressao_shift
	| expressao_relacional GE_OP expressao_shift
	;

expressao_shift
	: expressao_aditiva
	| expressao_shift ESQ_OP expressao_aditiva
	| expressao_shift DIR_OP expressao_aditiva
	;

expressao_aditiva
	: expressao_multiplicativa
	| expressao_aditiva '+' expressao_multiplicativa
	| expressao_aditiva '-' expressao_multiplicativa
	;

expressao_multiplicativa
	: expressao_cast
	| expressao_multiplicativa '*' expressao_cast
	| expressao_multiplicativa '/' expressao_cast
	| expressao_multiplicativa '%' expressao_cast
	| expressao_multiplicativa POT_OP expressao_cast
	;

expressao_cast
	: expressao_unaria
	| '(' tipo_especificador ')' expressao_cast
	;

expressao_unaria
	: expressao_posfix
	| INC_OP expressao_unaria
	| DEC_OP expressao_unaria
	| operador_unario expressao_cast
	;

operador_unario
	: '-'
	| '!'
	| '~'
	;

expressao_posfix
	: expressao_primaria
	| expressao_posfix '[' expressao ']'
	| expressao_posfix '(' ')'
	| expressao_posfix '(' lista_expressao_argumento ')'
	| expressao_posfix INC_OP
	| expressao_posfix DEC_OP
	;

expressao_primaria
	: IDENTIFICADOR
	| INT_CONST
	| CAR_CONST
	| PALAVRA_LITERAL
	| REAL_CONST
	| '(' expressao ')'
	;

expressao
	: expressao_atribuicao
	| expressao ',' expressao_atribuicao
	;

lista_expressao_argumento
	: expressao_atribuicao
	| lista_expressao_argumento ',' expressao_atribuicao
	;


expressao_constante
	: expressao_condicional
	;

%%
main(int argc, char**argv) {

	if(argc>1)
	{
		FILE *myfile = fopen(argv[1], "r");
		if (!myfile) {
			return -1;
		}
		yyin = myfile;
		do {
			yyparse();
		} while (!feof(yyin));
		cout<<"COMPILADO!";
	}
}

void yyerror(const char *s) 
{
    cout<<s<<endl;
    exit(1);
}