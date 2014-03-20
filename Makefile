CPPFLAGS = -std=c++0x -g
NOMEPROGRAMA = cafezinho
COMPILADOR = g++
CPPFILES = $(wildcard *.cpp)
HEADERFILES = $(wildcard *.h)

all: lex.yy.c sintatico.tab.c sintatico.tab.h
	$(COMPILADOR) sintatico.tab.c lex.yy.c $(HEADERFILES) $(CPPFILES) -o $(NOMEPROGRAMA) $(CPPFLAGS)

sintatico.tab.c sintatico.tab.h: sintatico.y
	bison -d sintatico.y

lex.yy.c: lexico.l sintatico.tab.h
	flex lexico.l
