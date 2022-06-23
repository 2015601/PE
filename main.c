#include <stdio.h>
#include "dlf.h"
#include "grammar.h"

int main (int argc, char *argv[])
{

	DLF_FILESET(dlf_file_create(argv[1]));

	yyparse();

	return 0;
}
