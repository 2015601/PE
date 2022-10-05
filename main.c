#include <stdio.h>
#include "dlf.h"
#include "grammar.h"

int main (int argc, char *argv[])
{
	struct dlf_file *file;

	file = dlf_file_create(argv[1]);
	DLF_SCRIPT_LOAD(file);

	dlf_execute(file->context);

	return 0;
}
