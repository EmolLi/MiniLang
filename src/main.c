#include "stdio.h"
#include <string.h>
#include "tree.h"
#include "comm.h"
#include "pretty.h"
#include "symbol.h"
#include "type.h"
#include "code.h"

void yyparse();
Node* root;
enum modes mode;
int main(int argc, char **argv)
{
	if (strcmp(argv[1], "scan") == 0) mode = scan;
	if (strcmp(argv[1], "tokens") == 0) mode = tokens;
	if (strcmp(argv[1], "parse") == 0) mode = parse;
	if (strcmp(argv[1], "pretty") == 0) mode = pretty;
	if (strcmp(argv[1], "symbol") == 0) mode = symbol;
	if (strcmp(argv[1], "typecheck") == 0) mode = typecheck;
	if (strcmp(argv[1], "codegen") == 0) mode = codegen;

	// printf("%s\n", argv[2]);

	yyparse();
	if (mode == scan || mode == tokens) return 0;
	if (mode == parse) {
		printf("OK\n");
		return 0;
	}
	if (mode == pretty) {
		prettyNode(root);
		return 0;
	}
	if (mode == symbol) {
		symProgram(root, true);
		return 0;
	}
	symProgram(root, false);
	typeProgram(root);
	if (mode == typecheck) {
		printf("OK\n");
		return 0;
	}
	codeProgram(root, argv[2]);
	printf("OK\n");
	return 0;
}
