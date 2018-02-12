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
    Node *n = newNode(k_NodeKindDeclarations, lineno);
    n->val.declarations.declarations = declarations;
    n->val.declarations.declaration = declaration;
	return n;
}


Node* newDeclaration(Node* ident, Node* varType, Node* exp, int lineno){
    Node *n = newNode(k_NodeKindDeclaration, lineno);
    n->val.declaration.ident = ident;
    n->val.declaration.varType = varType;
    n->val.declaration.exp = exp;
	return n;
}


Node* newStatements(Node* statements, Node* statment, int lineno){
    Node *n = newNode(k_NodeKindStatements, lineno);
    n->val.statements.statements = statements;
    n->val.statements.statement = statment;
}

Node *newStatementRead(Node* ident, int lineno){
    Node *n = newNode(k_NodeKindStatementRead, lineno);
    n->val.node = ident;
}

Node *newStatementPrint(Node* exp, int lineno){
    Node *n = newNode(k_NodeKindStatementPrint, lineno);
    n->val.node = exp;
}

Node *newStatementAssign(Node* ident, Node* exp, int lineno){
    Node *n = newNode(k_NodeKindStatementAssign, lineno);
    n->val.assignStatement.ident = ident;
    n->val.assignStatement.exp = exp;
}

Node *newStatementIf(Node* exp, Node* statements, Node* elseStatement, int lineno){
    Node *n = newNode(k_NodeKindStatementIf, lineno);
    n->val.ifStatement.exp = exp;
    n->val.ifStatement.statements = statements;
    n->val.ifStatement.elseStatement = elseStatement;
}

Node *newStatementElse(Node* statements, int lineno){
    Node *n = newNode(k_NodeKindStatementElse, lineno);
    n->val.node = statements;
}

Node *newStatementWhile(Node* exp, Node* statements, int lineno){
    Node *n = newNode(k_NodeKindStatementWhile, lineno);
    n->val.whileStatement.exp = exp;
    n->val.whileStatement.statements = statements;
}


// expression
Node *expressionIdentifier(char* val, int lineno){
    Node *n = newNode(k_NodeKindExpIdentifier, lineno);
    n->val.identifier = val;
}

Node *expressionIntLiteral(int val, int lineno){
    Node *n = newNode(k_NodeKindExpIntLiteral, lineno);
    n->val.intLiteral = val;
}
Node *expressionFloatLiteral(float val, int lineno){
    Node *n = newNode(k_NodeKindExpFloatLiteral, lineno);
    n->val.floatLiteral = val;
}
Node *expressionStringLiteral(char* val, int lineno){
    Node *n = newNode(k_NodeKindExpStringLiteral, lineno);
    n->val.stringLiteral = val;
}
Node *expressionBoolLiteral(bool val, int lineno){
    Node *n = newNode(k_NodeKindExpBoolLiteral, lineno);
    n->val.boolLiteral = val;
}
Node *expressionBinary(NodeKind op, Node *lhs, Node *rhs, int lineno){
    Node *n = newNode(op, lineno);
    n->val.binary.lhs = lhs;
    n->val.binary.rhs = rhs;
}
Node *expressionUnary(NodeKind op, Node *node, int lineno){
    Node *n = newNode(op, lineno);
    n->val.node = node;
}
