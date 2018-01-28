#include "stdio.h"
#include <string.h>
#include "tree.h"

void yyparse();
char* mode;
int main(int argc, char **argv)
{
	mode = strdup(argv[1]);
	yyparse();
	printf("OK\n");
	return 0;
}
