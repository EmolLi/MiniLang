#include "tree.h"

void typeProgram(Node *n);




//-------------
SymbolType typeBinaryASMD(Node* lhs, Node* rhs, NodeKind op);
SymbolType typeBinaryAO(Node* lhs, Node* rhs);
SymbolType typeBinaryEN(Node* lhs, Node* rhs);
SymbolType typeUNeg(Node* exp);
void typeAssign(Node* lhs, Node* rhs);
void typeBool(Node* exp);
