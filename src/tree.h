#ifndef TREE_H
#define TREE_H

typedef enum {
	k_NodeKindExpIdentifier,
	k_NodeKindExpIntLiteral,
	k_NodeKindExpFloatLiteral,
	k_NodeKindExpAddition,
	k_NodeKindExpSubtraction,
	k_NodeKindExpMultiplication,
	k_NodeKindExpDivision,
	k_NodeKindExpEqual,
	k_NodeKindExpNotEqual,
	k_NodeKindExpAnd,
	k_NodeKindExpOr,
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
		int intLiteral;
		struct { Node *lhs; Node *rhs; } binary;
	} val;
};



Node *expressionIdentifier(char *id);
Node *makeNode_intLiteral(int intLiteral);
Node *makeNode_binary(NodeKind op, Node *lhs, Node *rhs);


Node *newIntType();
Node *newBoolType();
Node *newFloatType();
Node *newStringType();

Node *newDeclaration();
Node *newDeclarations();

Node *newStatements();
Node *newStatementRead();
Node *newStatementPrint();
Node *newStatementAssign();
Node *newStatementIf();
Node *newStatementElse();
Node *newStatementWhile();

Node *expressionIdentifier();
Node *expressionIntLiteral();
Node *expressionFloatLiteral();
Node *expressionAddition();
Node *expressionSubtraction();
Node *expressionMultiplication();
Node *expressionDivision();
Node *expressionEqual();
Node *expressionNotEqual();
Node *expressionAnd();
Node *expressionOr();

#endif /* !TREE_H */
