#ifndef TREE_H
#define TREE_H

typedef enum {
	k_NodeKindIdentifier,
	k_NodeKindIntLiteral,
	k_NodeKindAddition,
	k_NodeKindSubtraction,
	k_NodeKindMultiplication,
	k_NodeKindDivision,
	k_NodeKindTypeInt,
	k_NodeKindTypeBool,
	k_NodeKindTypeFloat,
	k_NodeKindTypeString,
	k_NodeKindDeclaration
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


Node *newNode();
Node *makeNode_identifier(char *id);
Node *makeNode_intLiteral(int intLiteral);
Node *makeNode_binary(NodeKind op, Node *lhs, Node *rhs);


Node *newIntType();
Node *newBoolType();
Node *newFloatType();
Node *newStringType();
Node *newDeclaration();
#endif /* !TREE_H */
