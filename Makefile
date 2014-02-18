all: lex.yy.c sintatico.tab.c sintatico.tab.h
	g++ sintatico.tab.c lex.yy.c -o cafezinho

sintatico.tab.c sintatico.tab.h: sintatico.y
	bison -d sintatico.y	

lex.yy.c: lexico.l sintatico.tab.h
	flex lexico.l
