#include "tree.h"
#define HashSize 317

typedef enum{ st_INT, st_FLOAT, st_STRING, st_BOOL} SymbolType;
typedef struct SYMBOL {
    char *name;
    SymbolType type;
    Node *val;
    struct SYMBOL *next;
} SYMBOL;


typedef struct SymbolTable {
    SYMBOL *table[HashSize];
} SymbolTable;  // only one global symbol table




SymbolTable *initSymbolTable();
void buildSymbolTable(Node *n);
void printSymTable();
SYMBOL *putSymbol(Node* declaration);

SYMBOL *getSymbol(char *name);

void symProgram(Node *n, bool printTable);
