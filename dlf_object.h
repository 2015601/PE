#ifndef DLF_OBJECT_H
#define DLF_OBJECT_H

#include "list.h"

#define MAX_ARG_COUNT 7

struct dlf_identifier;
struct dlf_expression;
struct dlf_statement;
struct dlf_block;
struct dlf_value;

enum {
	DLF_V_NIL,
	DLF_V_NUMBER,
	DLF_V_STRING,
	DLF_V_VAR,
};

struct dlf_value {
	int vtype;
	union {
		unsigned number;
		char *str;
		struct dlf_identifier *id;
	};
};

enum {
	DLF_I_NIL,
	DLF_I_FUNC,
	DLF_I_VAR,
};

#define ARGN(args, n) (args[n-1])
#define check_number(args, n) ({ \
	if (ARGN(args, n).vtype != DLF_V_NUMBER) { \
		dlf_panic("panic"); \
	} \
	(int) (ARGN(args, n).number); \
})

#define check_string(args, n) ({ \
	if (ARGN(args, n).vtype != DLF_V_STRING) { \
		dlf_panic("panic"); \
	} \
	(const char *) (ARGN(args, n).str); \
})

struct dlf_function_call {
	struct dlf_value (*func_call)(struct dlf_value *args, int argc);
};

struct dlf_identifier {
	char *name;
	int itype;
	unsigned refcnt;
	struct dlf_value ivar;
	struct dlf_function_call func;
	slist_entry(struct dlf_identifier) _n;
};

struct dlf_block {
	slist_construct(struct dlf_statement) statements;
	slist_construct(struct dlf_identifier) idents;
};

enum {
	DLF_E_CONST,
	DLF_E_ADD,
	DLF_E_SUB,
};

struct dlf_expression {
	int etype;
	uint8_t eva_complete;
	union {
		struct {
			struct dlf_expression *l;
			struct dlf_expression *r;
		} binary;
		struct {
			struct dlf_identifier *fi;
		} function_call;
	};
	struct dlf_value ev;
};

enum {
	DLF_S_ASSIGN,
	DLF_S_IDENT,
	DLF_S_FUNCALL,
};

struct dlf_statement {
	int stype;
	unsigned line_n;
	union {
		struct {
			struct dlf_identifier *i;
			struct dlf_expression *e;
		} s_assign;
		struct {
			struct dlf_identifier *fi;
			struct dlf_value args[MAX_ARG_COUNT];
			int arg_count;
		} s_func;
	};
	slist_entry(struct dlf_statement) _n;
};

#define dlf_context dlf_block

extern struct dlf_file *current_script_file;

#define DLF_FILESET(file) current_script_file=file
#define DLF_SCRIPT_LOAD(file) do { \
	DLF_FILESET(file); \
	dlf_cfunc_load(); \
	yyparse(); \
} while(0)
#define DLFFILE current_script_file


struct dlf_file {
	const char *file_name;
	FILE *file;
	unsigned offset;
	struct dlf_context *context;
};

extern struct dlf_file * dlf_file_create (const char *filename);

struct dlf_identifier * dlf_identifier_get (const char *name);
extern struct dlf_identifier * dlf_identifier_new (const char *name, int type);
extern struct dlf_value *dlf_value_new(int type);

#define DLF_CFUNC_REGISTER(fun_cb, function) do { \
	struct dlf_identifier *new_ident = dlf_identifier_new(#function, DLF_I_FUNC); \
	new_ident->func.func_call = fun_cb; \
} while(0)

extern void dlf_cfunc_load(void);

static inline struct dlf_value *dlf_var_value_get(struct dlf_identifier *id)
{
	return &id->ivar;
}

#endif
