#include <stdio.h>
#include "dlf.h"


static struct dlf_value dlf_cprint (struct dlf_value *args)
{
	struct dlf_value value = {
		.vtype = DLF_V_NIL,
	};

	puts(check_string(args, 1));

	return value;
}


void dlf_cfunc_load(void)
{
	DLF_CFUNC_REGISTER(dlf_cprint, print);
}
