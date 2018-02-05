#include <stdlib.h>
#include "tree.h"

extern int yylineno;

Node *newNode(){
    Node *n = malloc(sizeof(Node));
    n->lineno = yylineno;
    return n;
}

Node *newIntType(){
    Node *n = newNode();
    n->kind = k_NodeKindTypeInt;
    return n;
}

Node *newBoolType(){
    Node *n = newNode();
    n->kind = k_NodeKindTypeBool;
    return n;
}

Node *newFloatType(){
    Node *n = newNode();
    n->kind = k_NodeKindTypeFloat;
    return n;
}

Node *newStringType(){
    Node *n = newNode();
    n->kind = k_NodeKindTypeString;
    return n;
}

Node* newDeclaration(){
    Node *n = newNode();
    n->kind = k_NodeKindDeclaration;
	return n;
}
