#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
SymbolTable *t;
int Hash(char *str){
    unsigned int hash = 0;
    while (*str) hash = (hash << 1) + *str++;
    return hash % HashSize;
}


SymbolTable *initSymbolTable(){
    SymbolTable *t = malloc(sizeof(SymbolTable));
    for (int i = 0; i < HashSize; i++) {
        t->table[i] = NULL;
    }
    return t;
}



SYMBOL *putSymbol(Node* declaration) {
    char* name = strdup((declaration->val.declaration.ident)->val.identifier);
    int i = Hash(name);
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0) {
            fprintf(stderr, "Error: (line %d) Variable %s already defined.\n", declaration->lineno, name);
            exit(1);
        }
    }
    SYMBOL *s = malloc(sizeof(SYMBOL));
    s->name = name;
    s->val = declaration;   // defined point
    switch ((declaration->val.declaration.varType)->kind) {
        case k_NodeKindTypeInt:
            s->type = st_INT;
            break;

        case k_NodeKindTypeBool:
            s->type = st_BOOL;
            break;

        case k_NodeKindTypeFloat:
            s->type = st_FLOAT;
            break;

        case k_NodeKindTypeString:
            s->type = st_STRING;
            break;

        default:
            fprintf(stderr, "Error: (line %d) Putting symbol %s wrong type.\n", declaration->lineno, name);
            exit(1);
    }
    // s->kind = kind;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
}

SYMBOL *getSymbol(char *name) {
    int i = Hash(name);
    // Check the current scope
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0) return s;
    }
    return NULL;
}

bool symbolNotDefined(char* name){
    return getSymbol(name)==NULL;
}

void symProgram(Node *n, bool printTable){
    t = initSymbolTable();
    buildSymbolTable(n);
    if (printTable){
        printSymTable();
    }
}



void printSymTable(){
    for (int i = 0; i < HashSize; i++) {
        if (t->table[i] != NULL){
            for (SYMBOL *s = t->table[i]; s; s = s->next) {
                printf("%s: ", s->name);
                switch (s->type) {
                    case st_INT:
                        printf("int\n");
                        break;
                    case st_FLOAT:
                        printf("float\n");
                        break;
                    case st_STRING:
                        printf("string\n");
                        break;
                    case st_BOOL:
                        printf("bool\n");
                        break;
                }
            }
        }
    }
}
void buildSymbolTable(Node *n){
    char* name;
    SYMBOL* s;
    if (n != NULL){
        switch (n->kind) {
            case k_NodeKindProg:
                buildSymbolTable(n->val.prog.declarations);
                buildSymbolTable(n->val.prog.statements);
                break;

            case k_NodeKindDeclaration:
                name = (n->val.declaration.ident)->val.identifier;
                s = putSymbol(n);
                n->val.declaration.ident->type = s->type;
                break;

            case k_NodeKindDeclarations:
                buildSymbolTable(n->val.declarations.declarations);
                buildSymbolTable(n->val.declarations.declaration);
                break;

            case k_NodeKindExpIdentifier:
                name = n->val.identifier;
                s = getSymbol(name);
                if (s == NULL){
                    fprintf(stderr, "Error: (line %d) Variable %s not defined.\n", n->lineno, name);
            		exit(1);
                }
                n->symbol = s;
                n->type = s->type;
                break;

            case k_NodeKindExpAddition:
            case k_NodeKindExpSubtraction:
            case k_NodeKindExpMultiplication:
            case k_NodeKindExpDivision:
            case k_NodeKindExpEqual:
            case k_NodeKindExpNotEqual:
            case k_NodeKindExpAnd:
            case k_NodeKindExpOr:
                buildSymbolTable(n->val.binary.lhs);
                buildSymbolTable(n->val.binary.rhs);
                break;

            case k_NodeKindExpUMinus:
            case k_NodeKindExpNeg:
            case k_NodeKindStatementRead:
            case k_NodeKindStatementPrint:
            case k_NodeKindStatementElse:
                buildSymbolTable(n->val.node);
                break;


            case k_NodeKindStatements:
                buildSymbolTable(n->val.statements.statements);
                buildSymbolTable(n->val.statements.statement);
                break;


            case k_NodeKindStatementAssign:
                buildSymbolTable(n->val.assignStatement.ident);
                buildSymbolTable(n->val.assignStatement.exp);
                break;

            case k_NodeKindStatementIf:
                buildSymbolTable(n->val.ifStatement.exp);
                buildSymbolTable(n->val.ifStatement.statements);
                buildSymbolTable(n->val.ifStatement.elseStatement);
                break;


            case k_NodeKindStatementWhile:
                buildSymbolTable(n->val.whileStatement.exp);
                buildSymbolTable(n->val.whileStatement.statements);
                break;

            default: break;
        }
    }
}
