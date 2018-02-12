#include "stdio.h"
#include <string.h>
#include "tree.h"
#include "comm.h"
#include "pretty.h"

void yyparse();
Node* root;
enum modes mode;
int main(int argc, char **argv)
{
	if (strcmp(argv[1], "scan") == 0) mode = scan;
	if (strcmp(argv[1], "tokens") == 0) mode = tokens;
	if (strcmp(argv[1], "parse") == 0) mode = parse;

	yyparse();
	printf("OK\n");

	prettyNode(root);
	return 0;
}
