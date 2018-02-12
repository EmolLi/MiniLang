#include "tree.h"
#define HashSize 317

typedef enum{classSym,fieldSym,methodSym,formalSym,localSym} SymbolKind;
typedef enum{ st_INT, st_FLOAT, st_STRING, st_BOOL} SymbolType;
typedef struct SYMBOL {
    char *name;
    SymbolKind kind;
    SymbolType type;
    Node *val;
    struct SYMBOL *next;
} SYMBOL;


typedef struct SymbolTable {
    SYMBOL *table[HashSize];
} SymbolTable;  // only one global symbol table




SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind);

SYMBOL *getSymbol(SymbolTable *t, char *name);


void symProgram(Node *n);
