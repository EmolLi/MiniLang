CC = gcc

CFLAGS = -Wall

all: parser.tab.o lex.yy.o main.o
	$(CC) lex.yy.o parser.tab.o main.o -o mini -lfl

scan: mini.l
	make lex.yy.c; $(CC) lex.yy.c -o mini -lfl

parser.tab.c parser.tab.h: mini.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h mini.y

lex.yy.c: mini.l parser.tab.h
	flex mini.l


clean:
	rm parser.tab.* lex.yy.*; rm *.o mini
