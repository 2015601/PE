#include <stdio.h>
#include "dlf.h"

static struct dlf_value dlf_cprint (struct dlf_value *args, int argc)
{
	char print_buffer[10*1024];
	struct dlf_value *v;
	size_t str_len = 0;
	struct dlf_value value = {
		.vtype = DLF_V_NIL,
	};

	for (int i = 0; i < argc; ++i) {
		v = args+i;
begin:
		switch (v->vtype)
		{
			case DLF_V_NUMBER:
				str_len += snprintf(print_buffer, sizeof(print_buffer)-str_len, "%d", v->number);
				break;
			case DLF_V_STRING:
				str_len += snprintf(print_buffer, sizeof(print_buffer)-str_len, "%s", v->str);
				break;
			case DLF_V_NIL:
				str_len += snprintf(print_buffer, sizeof(print_buffer)-str_len, "nil");
				break;
			case DLF_V_VAR:
				v = dlf_var_value_get(v->id);
				goto begin;
			default:
				continue;
		}
	}

	puts(print_buffer);

	return value;
}

void dlf_cfunc_load(void)
{
	DLF_CFUNC_REGISTER(dlf_cprint, print);
}
