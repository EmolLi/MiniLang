#include "stdio.h"
#include "tree.h"

void yyparse();

int main()
{
	yyparse();
	printf("OK\n");
	return 0;
}
