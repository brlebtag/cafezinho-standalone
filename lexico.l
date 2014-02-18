%{
#include <stdio.h>
#include <iostream>
#include "sintatico.tab.h"

#define YY_DECL extern "C" int yylex()

extern void yyerror(const char *s);

using namespace std;

int num_lines = 0;

%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
ID [_a-zA-Z][_a-zA-Z0-9]*
OC [0-7]

%option noyywrap

%%


0[xX]{H}+			{
/* Numero Hexadecimal*/
						return(INT_CONST); 
					}

0{OC}+				{
/* Numero Octeto */
						return(INT_CONST); 
					}

0?{D}+				{
/* Numero Inteiro */
						return(INT_CONST);
					}	

{D}+{E}				{
/* Numero real  */
						return(REAL_CONST); 
					}

{D}*"."{D}+({E})?	{	
/* Numero real  */
						return(REAL_CONST); 
					}

{D}+"."{D}*({E})?	{
/* Numero real  */
						return(REAL_CONST); 
					}
"/*"		{
				register int c;
				for ( ; ; )
				{
					while ( (c = yyinput()) != '*' && c != EOF ); 
					if ( c == '*' )
					{
						while ( (c = yyinput()) == '*' );
						if ( c == '/' )
						{
							break; 
						}
					}
					if ( c == EOF )
					{
						yyerror( "ERRO COMENTARIO NAO TERMINA " );
						break;
					}
				}
			}

"\""		{
				string val;

				register int c;
				for ( ; ; )
				{
					while ( (c = yyinput()) != '\"' && c != EOF && c != '\n' && c !='\\')
						val+=c;

					if(c == '\\') 
					{
						/*Eu ignoro o proximo caractere pq \\ é o caracter de escape*/
						c = yyinput();
						if(c==EOF)
						{
							yyerror( "ERRO CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA " );
							break;
						}
						else
							val+=c; 
					}
					if( c == '\"')
					{
						return PALAVRA_LITERAL;
						break;
					}
					if( c == '\n')
					{
						yyerror( "ERRO CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA " );
						break;
					}
					if ( c == EOF )
					{
						yyerror( "ERRO CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA " );
						break;
					}
				}
			}
      
"["			{
				return '[';
			}
   
"]"			{
				return ']';
   			}

"("			{
				return '(';
			}
   
")"			{
				return ')';
   			}	

"<="		{
				return LE_OP;
			}

">="		{
				return GE_OP;
			}

"<<="		{
				return ESQ_ATRIBUICAO;
			}

"<<"		{
				return ESQ_OP;
			}			

"<"			{
				return '<';
			}

">>="		{
				return DIR_ATRIBUICAO;
			}

">>"		{
				return DIR_OP;
			}

">"			{
				return '>';
			}

"=="		{
				return EQ_OP;
			}

"!="		{
				return NE_OP;
			}

"="			{
				return '=';
			}

","			{
				return ',';
			}

";"			{
				return ';';
			}

"{"			{ 
				return '{'; 
			}

"}"			{ 	
				return '}'; 
			}
	
"'"			{
				register int a = yyinput(),b=yyinput();
				if(a=='\\'&&b=='\''&& (a=yyinput())=='\'')
				{

					//esta composicao e '\'' que é OK!
					return CAR_CONST;
				}
				else if(a!='\''&&b=='\'')
				{
					//esta composicao e 'c' onde c!=vazio 
					return CAR_CONST;
				}
				else
				{
					if(a=='\'')
					{
						yyerror( "ERRO CONSTANTE CARACTERE VAZIA " );
					}
					else
					{
						yyerror( "ERRO ESTOURO DE CONSTANTE CARACTERE " );
					}
				}
					
			}

"?"			{
				return '?';
			}

":"			{
				return ':';
			}

"+="		{
				return ADICAO_ATRIBUICAO;
			}			

"++"		{

				return INC_OP;
			}

"+"			{
				return '+';
			}

"-="		{
				return SUBTRACAO_ATRIBUICAO;
			}

"--"		{
				return DEC_OP;
			}

"-"			{
				return '-';
			}

"*="		{
				return MULT_ATRIBUICAO;
			}

"**="		{
				return POT_ATRIBUICAO;
			}

"**"		{
				return POT_OP;
			}


"*"			{
				return '*';
			}

"/="		{
				return DIV_ATRIBUICAO;
			}				

"/"			{
				return '/';
			}

"%="		{
				return MOD_ATRIBUICAO;
			}

"%"			{
				return '%';
			}

"!"			{
				return '!';
			}

"&="		{
				return E_ATRIBUICAO;
			}

"&&"		{
				return E_OP;
			}

"&"			{
				return '&';
			}

"|="		{
				return OU_ATRIBUICAO;
			}

"||"		{
				return OU_OP;
			}

"|"			{
				return '|';
			}

"^"			{
				return '^';
			}

"^="		{
				return XOR_ATRIBUICAO;
			}

"nulo"	    {
 				return NULO;
			}

"car" 		{
				return CAR;
			}

"real" 		{
				return REAL;
			}

"int"		{
 				return INT;
			}

"retorne"	{
				return RETORNE;
			}

"leia"		{
				return LEIA;
			}

"escreva"	{
				return ESCREVA;
			}

"novalinha"	{
				return NOVA_LINHA;
			}

"se" 		{
				return SE;
			}

"senao" 	{
				return SENAO;
			}

"entao"		{
				return ENTAO;
			}

"enquanto"	{
				return ENQUANTO;
			}

"execute"	{

				return EXECUTE;
			}

"e" 		{
				return E_OP;
			}

"ou"		{
				return OU_OP;
			}

{ID}+ 		{
				return IDENTIFICADOR;
      		}

\n 			num_lines++;

[ \t]+ 	; /* eat up whitespace */

.			{ 
				yyerror("ERRO CARACTERE INVALIDO ");
			}		

%%