#ifndef dlf_NEEDLE_H
#define dlf_NEEDLE_H

#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>

#include "list.h"
#include "dlf_error.h"
#include "dlf_memory.h"

struct dlf_identifier;
struct dlf_expression;
struct dlf_statement;
struct dlf_block;
struct dlf_value;

enum {
	DLF_V_NUMBER,
};

struct dlf_value {
	int vtype;
	union {
		unsigned number;
	};
};

enum {
	DLF_I_FUNC,
	DLF_I_VAR,
};

struct dlf_identifier {
	char *name;
	int itype;
	unsigned refcnt;
	union {
		struct dlf_value ivar;
		struct {
			slist_construct(struct dlf_identifier) args;
			slist_construct(struct dlf_statement) statements;
		} ifunc;
	};
	slist_entry(struct dlf_identifier) _n;
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
};


struct dlf_statement {
	int stype;
	unsigned line_n;
	union {
		struct {
			struct dlf_identifier *i;
			struct dlf_expression *e;
		} s_assign;
	} ;
	slist_entry(struct dlf_statement) _n;
};

struct dlf_context {
	slist_construct(struct dlf_statement) statements;
	slist_construct(struct dlf_identifier) idents;
};

struct dlf_value * dlf_expression_eva (struct dlf_expression *expression);

int dlf_execute (struct dlf_context *context);

// util
struct dlf_identifier * dlf_identifier_get (const char *name);

struct dlf_context * dlf_current_context_get(void);

struct dlf_file {
	const char *file_name;
	FILE *file;
	unsigned offset;
};

extern struct dlf_file *current_script_file;

#define DLF_FILESET(file) current_script_file=file
#define DLFFILE current_script_file

struct dlf_file * dlf_file_create (const char *filename);

#endif
