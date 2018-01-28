#ifndef TREE_H
#define TREE_H

typedef enum {
	k_NodeKindIdentifier,
	k_NodeKindIntLiteral,
	k_NodeKindAddition,
	k_NodeKindSubtraction,
	k_NodeKindMultiplication,
	k_NodeKindDivision
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

Node *makeNode_identifier(char *id);
Node *makeNode_intLiteral(int intLiteral);
Node *makeNode_binary(NodeKind op, Node *lhs, Node *rhs);
#endif /* !TREE_H */
