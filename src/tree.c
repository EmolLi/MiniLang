#include <stdlib.h>
#include "tree.h"

extern int yylineno;

Node *newNode(NodeKind k, int lineno){
    Node *n = malloc(sizeof(Node));
    n->lineno = lineno;
    n->kind = k;
    return n;
}

Node *newType(NodeKind type, int lineno){

}


Node* newDeclarations(Node* declarations, Node* declaration, int lineno){
    Node *n = newNode();
    n->kind = k_NodeKindDeclarations;
	return n;
}


Node* newDeclaration(Node* ident, Node* varType, Node* exp, int lineno){
    Node *n = newNode();
    n->kind = k_NodeKindDeclaration;
	return n;
}


Node* newStatements(Node* statements, Node* statment, int lineno){

}

Node *newStatementRead(Node* ident, int lineno){

}

Node *newStatementPrint(Node* exp, int lineno){

}

Node *newStatementAssign(Node* ident, Node* exp, int lineno){

}

Node *newStatementIf(Node* exp, Node* statements, Node* elseStatements, int lineno){

}

Node *newStatementElse(Node* statements, int lineno){

}

Node *newStatementWhile(Node* exp, Node* statements, int lineno){

}


// expression
Node *expressionIdentifier(char* val, int lineno){}

Node *expressionIntLiteral(int val, int lineno){}
Node *expressionFloatLiteral(float val, int lineno){}
Node *expressionStringLiteral(char* val, int lineno){}
Node *expressionBoolLiteral(bool val, int lineno){}
Node *expressionLiteral(NodeKind type, int lineno){}
Node *expressionBinary(NodeKind op, Node *lhs, Node *rhs, int lineno){}
Node *expressionUnary(NodeKind op, Node *node, int lineno){}
