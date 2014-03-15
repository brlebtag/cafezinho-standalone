%{
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "arvore_abstrata.h"
#include "debug.h"
#include "sintatico.tab.h"

#define YY_DECL extern "C" int yylex()

extern void yyerror(NBloco * bloco, const char *s);

int linha = 1;

using namespace std;

string ultimo_token; 

%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
ID 			[_a-zA-Z][_a-zA-Z0-9]*
OC 			[0-7]

%option noyywrap
%option yylineno


%%

0[xX]{H}+			{
/* Numero Hexadecimal*/
						std::stringstream ss;
						ss<< std::hex << yytext;
						ss>>yylval.ival;
						ultimo_token = "CONSTANTE INTEIRA";
						return(INT_CONST); 
					}

0{OC}+				{
/* Numero Octeto */
						std::stringstream ss;
						ss<< std::oct << yytext;
						ss>>yylval.ival;
						ultimo_token = "CONSTANTE INTEIRA";
						return(INT_CONST); 
					}

[+-]?0?{D}+			{
/* Numero Inteiro */
						std::stringstream ss;
						ss<< std::dec << yytext;
						ss>>yylval.ival;
						ultimo_token = "CONSTANTE INTEIRA";
						return(INT_CONST);
					}	

[+-]?{D}+{E}		{
/* Numero real  */		
						yylval.dval = atof(yytext);
						ultimo_token = "CONSTANTE REAL";
						return(REAL_CONST); 
					}

[+-]?{D}*"."{D}+({E})? {	
/* Numero real  */
							yylval.dval = atof(yytext);
							ultimo_token = "CONSTANTE REAL";
							return(REAL_CONST); 
					 	}

[+-]?{D}+"."{D}*({E})?	{
/* Numero real  */
							yylval.dval = atof(yytext);
							ultimo_token = "CONSTANTE REAL";
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
						yyerror(0, "ERRO COMENTARIO NAO TERMINA " );
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
							yyerror(0, "ERRO CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA " );
							break;
						}
						else
							val+=c; 
					}
					if( c == '\"')
					{
						yylval.sval = new string(val) ;
						ultimo_token = "PALAVRA LITERAL";
						return PALAVRA_LITERAL;
						break;
					}
					if( c == '\n')
					{
						yyerror(0, "ERRO CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA " );
						break;
					}
					if ( c == EOF )
					{
						yyerror(0, "ERRO CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA " );
						break;
					}
				}
			}
      
"["			{
				yylval.ival = yylineno;
				ultimo_token = "[";
				return '[';
			}
   
"]"			{
				ultimo_token = "]";
				return ']';
   			}

"("			{
				yylval.ival = yylineno;
				ultimo_token = "(";
				return '(';
			}
   
")"			{
				ultimo_token = ")";
				return ')';
   			}	

"<="		{
				ultimo_token = "<=";
				return LE_OP;
			}

">="		{
				ultimo_token = ">=";
				return GE_OP;
			}

"<<="		{
				ultimo_token = "<<=";
				return ESQ_ATRIBUICAO;
			}

"<<"		{
				ultimo_token = "<<";
				return ESQ_OP;
			}			

"<"			{
				ultimo_token = "<";
				return '<';
			}

">>="		{
				ultimo_token = ">>=";
				return DIR_ATRIBUICAO;
			}

">>"		{
				ultimo_token = "<<";
				return DIR_OP;
			}

">"			{
				ultimo_token = "<";
				return '>';
			}

"=="		{
				ultimo_token = "==";
				return EQ_OP;
			}

"!="		{
				ultimo_token = "!=";
				return NE_OP;
			}

"="			{
				ultimo_token = "=";
				return '=';
			}

","			{
				ultimo_token = ",";
				return ',';
			}

";"			{
				ultimo_token = ";";
				return ';';
			}

"{"			{
				yylval.ival = yylineno;
				ultimo_token = "{";
				return '{'; 
			}

"}"			{ 	
				ultimo_token = "}";
				return '}'; 
			}
	
"'"			{
				register int a = yyinput(), b=yyinput();
				if(a=='\\'&&b=='\''&& (a=yyinput())=='\'')
				{

					//esta composicao e '\'' que é OK!
					ultimo_token = "\'";
					yylval.ival = (int) '\'' ;
					return CAR_CONST;
				}
				else if(a!='\''&&b=='\'')
				{
					//esta composicao e 'c' onde c!=vazio 
					ultimo_token = a;
					yylval.ival = (int) a ;
					return CAR_CONST;
				}
				else
				{
					if(a=='\'')
					{
						yyerror(0, "ERRO CONSTANTE CARACTERE VAZIA " );
					}
					else
					{
						yyerror(0, "ERRO ESTOURO DE CONSTANTE CARACTERE " );
					}
				}
					
			}

"?"			{
				ultimo_token = "?";
				return '?';
			}

":"			{
				ultimo_token = ":";
				return ':';
			}

"+="		{
				ultimo_token = "+=";
				return ADICAO_ATRIBUICAO;
			}			

"++"		{
				yylval.ival = yylineno;
				ultimo_token = "++";
				return INC_OP;
			}

"+"			{
				ultimo_token = "+";
				return '+';
			}

"-="		{
				ultimo_token = "-=";
				return SUBTRACAO_ATRIBUICAO;
			}

"--"		{
				yylval.ival = yylineno;
				ultimo_token = "--";
				return DEC_OP;
			}

"-"			{
				ultimo_token = "-";
				return '-';
			}

"*="		{
				ultimo_token = "*=";
				return MULT_ATRIBUICAO;
			}

"**="		{
				ultimo_token = "**=";
				return POT_ATRIBUICAO;
			}

"**"		{
				ultimo_token = "**";
				return POT_OP;
			}


"*"			{
				ultimo_token = "*";
				return '*';
			}

"/="		{
				ultimo_token = "/=";
				return DIV_ATRIBUICAO;
			}				

"/"			{
				ultimo_token = "/";
				return '/';
			}

"%="		{
				ultimo_token = "%=";
				return MOD_ATRIBUICAO;
			}

"%"			{
				ultimo_token = "%";
				return '%';
			}

"!"			{
				ultimo_token = "!";
				return '!';
			}

"&="		{
				ultimo_token = "&=";
				return E_ATRIBUICAO;
			}

"&&"		{
				ultimo_token = "&&";
				return E_OP;
			}

"&"			{
				ultimo_token = "&";
				return '&';
			}

"|="		{
				ultimo_token = "|=";
				return OU_ATRIBUICAO;
			}

"||"		{
				ultimo_token = "||";
				return OU_OP;
			}

"|"			{
				ultimo_token = "|";
				return '|';
			}

"^"			{
				ultimo_token = "^";
				return '^';
			}

"^="		{
				ultimo_token = "^=";
				return XOR_ATRIBUICAO;
			}

"nulo"	    {
				ultimo_token = "nulo";
 				return NULO;
			}

"car" 		{
				ultimo_token = "car";
				return CAR;
			}

"real" 		{
				ultimo_token = "real";
				return REAL;
			}

"int"		{
				ultimo_token = "int";
 				return INT;
			}

"retorne"	{
				yylval.ival = yylineno;
				ultimo_token = "retorne";
				return RETORNE;
			}

"leia"		{
				yylval.ival = yylineno;
				ultimo_token = "leia";
				return LEIA;
			}

"escreva"	{
				yylval.ival = yylineno;	
				ultimo_token = "escreva";
				return ESCREVA;
			}

"novalinha"	{
				yylval.ival = yylineno;
				ultimo_token = "novalinha";
				return NOVA_LINHA;
			}

"se" 		{
				yylval.ival = yylineno;
				ultimo_token = "se";
				return SE;
			}

"senao" 	{
				yylval.ival = yylineno;	
				ultimo_token = "senao";
				return SENAO;
			}

"entao"		{
				ultimo_token = "entao";
				return ENTAO;
			}

"enquanto"	{
				yylval.ival = yylineno;
				ultimo_token = "enquanto";
				return ENQUANTO;
			}

"execute"	{
				ultimo_token = "execute";
				return EXECUTE;
			}

"e" 		{
				ultimo_token = "e";
				return E_OP;
			}

"ou"		{
				ultimo_token = "ou";
				return OU_OP;
			}

{ID}+ 		{
				ultimo_token = "IDENTIFICADOR";
				yylval.sval = new string(yytext) ;
				return IDENTIFICADOR;
      		}

[ <<EOF>>\0\t\v\r\n\f]+ 	; /* eat up whitespace */

.			{
				ultimo_token = yytext;
				yyerror(0, "");
			}		

%%