#ifndef dlf_NEEDLE_H
#define dlf_NEEDLE_H

#include "list.h"

struct dlf_identifier;
struct dlf_expression;
struct dlf_statement;
struct dlf_block;
struct dlf_value;

union {
	DFL_VALUE
}

struct dlf_value {
	int vtype;
	union {
		unsigned number;
	} value;
};

struct dlf_identifier {
	char *name;
	int itype;
	unsigned refcnt;
	union {
		struct dlf_value iconst;
		struct {
			slist_construct(struct dlf_identifier) args;
			struct dlf_block *fb;
		} ifunc;
	} ident;
	slist_entry(struct dlf_identifier) _n;
};

struct dlf_expression {
	int etype;
	union {
		struct {
			struct dlf_expression *l;
			struct dlf_expression *r;
		} binary;
		struct {
			struct dlf_identifier *fi;
		} function_call;
	} expression;
	struct dlf_value ev;
};

struct dlf_statement {
	int stype;
	unsigned line_n;
	union {
		struct {
			struct dlf_identifier i;
			struct dlf_expression e;
		} s_assign;
	} statement;
	slist_entry(struct dlf_statements) _n;
};

struct dlf_block {
	slist_construct(struct dlf_statements) statements;
};

#endif
