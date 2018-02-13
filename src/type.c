#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "type.h"


void typeProgram(Node *n){
    if (n != NULL){
        switch (n->kind) {

            case k_NodeKindProg:
            typeProgram(n->val.prog.declarations);
            typeProgram(n->val.prog.statements);
            break;

            case k_NodeKindExpIdentifier:
            // definition and redefination already checked at symbol table phase
            break;

            case k_NodeKindExpIntLiteral:
            n->type = st_INT;
            break;

            case k_NodeKindExpFloatLiteral:
            n->type = st_FLOAT;
            break;

            case k_NodeKindExpStringLiteral:
            n->type = st_STRING;
            break;

            case k_NodeKindExpBoolLiteral:
            n->type = st_BOOL;
            break;

            case k_NodeKindExpAddition:
            typeProgram(n->val.binary.lhs);
            typeProgram(n->val.binary.rhs);
            n->type = typeBinaryASMD(n->val.binary.lhs, n->val.binary.rhs, k_NodeKindExpAddition);
            break;

            case k_NodeKindExpSubtraction:
            typeProgram(n->val.binary.lhs);
            typeProgram(n->val.binary.rhs);
            n->type = typeBinaryASMD(n->val.binary.lhs, n->val.binary.rhs, k_NodeKindExpSubtraction);
            break;

            case k_NodeKindExpMultiplication:
            typeProgram(n->val.binary.lhs);
            typeProgram(n->val.binary.rhs);
            n->type = typeBinaryASMD(n->val.binary.lhs, n->val.binary.rhs, k_NodeKindExpMultiplication);
            break;

            case k_NodeKindExpDivision:
            typeProgram(n->val.binary.lhs);
            typeProgram(n->val.binary.rhs);
            n->type = typeBinaryASMD(n->val.binary.lhs, n->val.binary.rhs, k_NodeKindExpDivision);
            break;


            case k_NodeKindExpEqual:
            case k_NodeKindExpNotEqual:
            typeProgram(n->val.binary.lhs);
            typeProgram(n->val.binary.rhs);
            n->type = typeBinaryEN(n->val.binary.lhs, n->val.binary.rhs);
            break;


            case k_NodeKindExpAnd:
            case k_NodeKindExpOr:
            typeProgram(n->val.binary.lhs);
            typeProgram(n->val.binary.rhs);
            n->type = typeBinaryAO(n->val.binary.lhs, n->val.binary.rhs);
            break;

            case k_NodeKindExpUMinus:
            typeProgram(n->val.node);
            n->type = typeUMinus(n->val.node);
            break;

            case k_NodeKindExpNeg:
            typeProgram(n->val.node);
            n->type = typeUNeg(n->val.node);
            break;

            case k_NodeKindDeclaration:
            typeProgram(n->val.declaration.exp);
            typeAssign(n->val.declaration.ident, n->val.declaration.exp);
            break;

            case k_NodeKindDeclarations:
            typeProgram(n->val.declarations.declarations);
            typeProgram(n->val.declarations.declaration);
            break;

            case k_NodeKindStatements:
            typeProgram(n->val.statements.statements);
            typeProgram(n->val.statements.statement);
            break;

            case k_NodeKindStatementRead:
            typeProgram(n->val.node);
            break;

            case k_NodeKindStatementPrint:
            typeProgram(n->val.node);
            break;

            case k_NodeKindStatementAssign:
            typeProgram(n->val.assignStatement.ident);
            typeProgram(n->val.assignStatement.exp);
            typeAssign(n->val.assignStatement.ident, n->val.assignStatement.exp);
            break;

            case k_NodeKindStatementIf:
            typeProgram(n->val.ifStatement.exp);
            typeBool(n->val.ifStatement.exp);
            typeProgram(n->val.ifStatement.statements);
            typeProgram(n->val.ifStatement.elseStatement);
            break;


            case k_NodeKindStatementElse:
            typeProgram(n->val.node);
            break;

            case k_NodeKindStatementWhile:
            typeProgram(n->val.whileStatement.exp);
            typeBool(n->val.whileStatement.exp);
            typeProgram(n->val.whileStatement.statements);
            break;

            default: break;
        }
    }
}



// binary ops +, -, *, /
SymbolType typeBinaryASMD(Node* lhs, Node* rhs, NodeKind op){
    if (lhs->type == st_INT && rhs->type == st_INT) return st_INT;
    if (lhs->type == st_FLOAT && rhs->type == st_FLOAT) return st_FLOAT;
    if ((lhs->type == st_INT && rhs->type == st_FLOAT) ||
        (lhs->type == st_FLOAT && rhs->type == st_INT)) return st_FLOAT;
    if (lhs->type == st_STRING && rhs->type == st_STRING && op == k_NodeKindExpAddition) return st_STRING;
    if ((lhs->type == st_STRING && rhs->type == st_INT) ||
        (lhs->type == st_INT && rhs->type == st_STRING)) return st_STRING;
    fprintf(stderr, "Error: (line %d) binary operation type incorrect.\n", lhs->lineno);
    exit(1);
}

// binary ops &&, || /
SymbolType typeBinaryAO(Node* lhs, Node* rhs){
    if ((lhs->type == st_INT || lhs->type == st_BOOL) &&
        (rhs->type == st_INT || rhs->type == st_BOOL)) return st_BOOL;
    fprintf(stderr, "Error: (line %d) binary operation type incorrect, expecting int or bool.\n", lhs->lineno);
    exit(1);
}

// binary ops ==, !=
SymbolType typeBinaryEN(Node* lhs, Node* rhs){
    if (lhs->type == rhs->type) return st_BOOL;
    fprintf(stderr, "Error: (line %d) binary operation type incorrect, cannot compare two expressions with different types.\n", lhs->lineno);
    exit(1);
}

SymbolType typeUMinus(Node* exp){
    if (exp->type == st_INT || exp->type == st_FLOAT) return exp->type;
    fprintf(stderr, "Error: (line %d) unary minus operation type incorrect, expecting type float or int.\n", exp->lineno);
    exit(1);
}

SymbolType typeUNeg(Node* exp){
    if (exp->type == st_BOOL) return exp->type;
    fprintf(stderr, "Error: (line %d) unary neg operation type incorrect, expecting type bool.\n", exp->lineno);
    exit(1);
}

void typeAssign(Node* lhs, Node* rhs){
    if (lhs->type == st_FLOAT && rhs->type == st_INT) return;
    if (lhs->type == rhs->type) return;
    fprintf(stderr, "Error: (line %d) assignment type incorrect.\n", lhs->lineno);
    exit(1);
}

void typeBool(Node* exp){
    if (exp->type == st_BOOL || exp->type == st_INT) return;
    fprintf(stderr, "Error: (line %d) exp wrong type, expecting int or bool type.\n", exp->lineno);
    exit(1);
}
