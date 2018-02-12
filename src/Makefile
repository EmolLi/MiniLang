CC = gcc

CFLAGS = -Wall

all: parser.tab.o lex.yy.o main.o tree.h tree.o pretty.h pretty.o symbol.h symbol.o
	$(CC) lex.yy.o parser.tab.o tree.o pretty.o symbol.o main.o -o mini -lfl

scan: mini.l tree.h tree.o
	make lex.yy.c; $(CC) lex.yy.c -o mini -lfl

parser.tab.c parser.tab.h: mini.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h mini.y

lex.yy.c: mini.l parser.tab.h
	flex mini.l

debug: mini.y
	 rm mini.output; bison --verbose mini.y
clean:
	rm parser.tab.* lex.yy.*; rm *.o mini mini.tab.*
