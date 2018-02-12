#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
typedef enum {
	k_NodeKindProg,
	k_NodeKindExpIdentifier,
	k_NodeKindExpIntLiteral,
	k_NodeKindExpFloatLiteral,
	k_NodeKindExpStringLiteral,
	k_NodeKindExpBoolLiteral,
	k_NodeKindExpAddition,
	k_NodeKindExpSubtraction,
	k_NodeKindExpMultiplication,
	k_NodeKindExpDivision,
	k_NodeKindExpEqual,
	k_NodeKindExpNotEqual,
	k_NodeKindExpAnd,
	k_NodeKindExpOr,
	k_NodeKindExpUMinus,
	k_NodeKindExpNeg,
	k_NodeKindTypeInt,
	k_NodeKindTypeBool,
	k_NodeKindTypeFloat,
	k_NodeKindTypeString,
	k_NodeKindDeclaration,
	k_NodeKindDeclarations,
	k_NodeKindStatements,
	k_NodeKindStatementRead,
	k_NodeKindStatementPrint,
	k_NodeKindStatementAssign,
	k_NodeKindStatementIf,
	k_NodeKindStatementElse,
	k_NodeKindStatementWhile,
} NodeKind;

typedef struct Node Node;
struct Node {
	int lineno;
	NodeKind kind;
	union {
		char *identifier;
		char* stringLiteral;
		int intLiteral;
		float floatLiteral;
		bool boolLiteral;

		Node* node;
		struct { Node *declarations; Node *statements; } prog;
		struct { Node *lhs; Node *rhs; } binary;
		struct { Node *declarations; Node *declaration;} declarations;
		struct { Node *ident; Node *varType; Node *exp;} declaration;
		struct { Node *statements; Node *statement;} statements;
		struct { Node *ident; Node *exp;} assignStatement;
		struct { Node *exp; Node *statements; Node *elseStatement;} ifStatement;
		struct { Node *exp; Node *statements;} whileStatement;
	} val;
};


Node *newProg(Node* declarations, Node* statements, int lineno);

Node *newType(NodeKind type, int lineno);

Node *newDeclarations(Node* declarations, Node* declaration, int lineno);
Node *newDeclaration(Node* ident, Node* varType, Node* exp, int lineno);
Node *newStatements(Node* statements, Node* statment, int lineno);
Node *newStatementRead(Node* ident, int lineno);
Node *newStatementPrint(Node* exp, int lineno);
Node *newStatementAssign(Node* ident, Node* exp, int lineno);
Node *newStatementIf(Node* exp, Node* statements, Node* elseStatement, int lineno);
Node *newStatementElse(Node* statements, int lineno);
Node *newStatementWhile(Node* exp, Node* statements, int lineno);

Node *expressionIdentifier(char* val, int lineno);
Node *expressionIntLiteral(int val, int lineno);
Node *expressionFloatLiteral(float val, int lineno);
Node *expressionStringLiteral(char* val, int lineno);
Node *expressionBoolLiteral(bool val, int lineno);
Node *expressionBinary(NodeKind op, Node *lhs, Node *rhs, int lineno);
Node *expressionUnary(NodeKind op, Node *node, int lineno);

#endif /* !TREE_H */
