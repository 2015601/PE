#include <string.h>

#include "dlf.h"

static struct dlf_context *current_context;

static struct dlf_identifier * dlf_i_lookup (const char *name)
{
	struct dlf_identifier *i;

	slist_walk (&current_context->idents, i, _n) {
		if (! strcmp (i->name, name)) {
			return i;
		}
	}

	return NULL;
}

static inline struct dlf_value * dlf_e_const (struct dlf_expression *expression)
{
	return &expression->ev;
}

static struct dlf_value * dlf_e_add (struct dlf_expression *expression)
{
	struct dlf_expression *l, *r;
	struct dlf_value* lv, *rv;

	l = expression->binary.l;
	r = expression->binary.r;

	lv = dlf_expression_eva (l);
	rv = dlf_expression_eva (r);

	if (!lv || !rv) {
		dlf_error("error add expression");
		return NULL;
	}

	expression->ev.number = lv->number + rv->number;

	return &expression->ev;
}

static struct dlf_value * dlf_e_sub (struct dlf_expression *expression)
{
	struct dlf_expression *l, *r;
	struct dlf_value *lv, *rv;

	lv = dlf_expression_eva (l);
	rv = dlf_expression_eva (r);

	if (!lv || !rv) {
		dlf_error("error sub expression");
		return NULL;
	}

	expression->ev.number = lv->number + rv->number;

	return &expression->ev;
}

struct dlf_value * dlf_expression_eva (struct dlf_expression *expression)
{
	struct dlf_value * v;

	v = NULL;

	if (expression->eva_complete) {
		return &expression->ev;
	}

	switch (expression->etype) {
		case DLF_E_ADD:
			v = dlf_e_add(expression);
		case DLF_E_SUB:
			v = dlf_e_sub (expression);
		case DLF_E_CONST:
			v = dlf_e_const(expression);
	}

	if (v)
		expression->eva_complete = 1;
	else
		dlf_error("unknown expression %d", expression->etype);

	return v;
}


static int dlf_s_assign (struct dlf_statement *statement)
{
	struct dlf_value *v;
	struct dlf_identifier *ident;
	struct dlf_expression *expression;

	expression = statement->s_assign.e;
	ident = statement->s_assign.i;

	if (ident->itype != DLF_I_VAR) {
		dlf_error("error ident type");
		return -1;
	}

	v = dlf_expression_eva (expression);
	if (!v) {
		dlf_error ("error assign statement");
		return -1;
	}

	ident->ivar = *v;

	return 0;
}

int dlf_execute (struct dlf_context *context)
{
	struct dlf_statement *statement;
	int ret;

	current_context = context;

	slist_walk(&context->statements, statement, _n) {
		switch (statement->stype) {
			case DLF_S_ASSIGN :
				ret = dlf_s_assign (statement);
				break;
		}
		if (ret != 0) {
			dlf_error("dlf_execute error");
			return ret;
		}
	}
	return 0;

}
