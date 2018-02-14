#include "tree.h"

struct EXPEvalResult {
	int lineno;
	NodeKind kind;
	SYMBOL *symbol;		// optional
	SymbolType type;	// optional
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

void codeProgram(Node* n);
void codeInit();
void codeGenerate(Node* n);
