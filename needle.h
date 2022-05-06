#ifndef ND_NEEDLE_H
#define ND_NEEDLE_H

#include "list.h"

struct nd_identifier;
struct nd_expression;
struct nd_statement;
struct nd_block;

struct nd_identifier {
	char *name;
};

struct nd_value {
	int vtype;
	union {
		
	} value;
};

struct nd_expression {
	int etype;
	struct nd_expression *l;
	struct nd_expression *r;
	struct nd_value v;
};

struct nd_statement {
	int stype;
	unsigned line_n;
	union {
		#include "statement.h"
	} statement;
	slist_entry(struct nd_statements) _n;
};

struct nd_block {
	slist_construct(struct nd_statements) statements;
};


#endif
