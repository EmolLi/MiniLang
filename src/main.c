#include "stdio.h"
#include <string.h>
#include "tree.h"
#include "comm.h"
#include "pretty.h"
#include "symbol.h"

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

	yyparse();
	if (mode == parse) printf("OK\n");

	if (mode == pretty) prettyNode(root);


	symProgram(root, true);
	// if (mode == symbol) symProgram(root, true);
	return 0;
}
