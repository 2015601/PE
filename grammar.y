%{
#include "dlf.h"
#include "lexical.h"

static void dlf_statement_insert (struct dlf_statement *statement)
{
	struct dlf_context * context;

	context = dlf_current_context_get();

	slist_insert_tail (&context->statements, statement, _n);
}

static struct dlf_expression * dlf_binary_expression_calloc (int type,
	struct dlf_expression *l, struct dlf_expression *r)
{
	struct dlf_expression *e = dlf_calloc(sizeof (struct dlf_expression), 1);
	e->etype = type;
	e->binary.l = l;
	e->binary.r = r;
}

static struct dlf_identifier *  dlf_identifier_new (const char *name, int type)
{
	struct dlf_identifier *i;
	struct dlf_context *context;

	i = dlf_identifier_get (name);
	if (i) {
		return i;
	}

	context = dlf_current_context_get();

	i = dlf_calloc(sizeof (struct dlf_identifier), 1);
	i->itype = type;
	i->name = strdup (name);

	slist_insert_tail(&context->idents, i, _n);

	return i;
}

static void yyerror(const char * error) {

}

%}

%union {
	struct dlf_statement *s;
	struct dlf_expression *e;
	char * id;
	int number;
}

%token LP RP LB RB SEMICOLON EQ COMMA
%token FUNCTION IF ELIF ELSE WHILE FOR RETURN EQUAL
%token FALSE TRUE
%token <number> NUMBER
%token <id> IDENTIFIER
%type <s> ASSIGN_STATEMENT
%type <e> EXPRESSION BINARY_EXPRESSION
%left ADD SUB

%%

STATEMENTS : /* empty */
	|	STATEMENTS ASSIGN_STATEMENT { dlf_statement_insert($2); }
	;

ASSIGN_STATEMENT : IDENTIFIER EQUAL EXPRESSION {
		struct dlf_identifier *i = dlf_identifier_new ($1, DLF_I_VAR);
		$$ = dlf_calloc (sizeof(struct dlf_statement), 1);
		$$->stype = DLF_S_ASSIGN;
		$$->s_assign.i = i;
		$$->s_assign.e = $3;
	}
	;

EXPRESSION : BINARY_EXPRESSION
	;

BINARY_EXPRESSION : NUMBER {
		$$ = dlf_calloc (sizeof(struct dlf_expression), 1);
		$$->etype = DLF_E_CONST;
		$$->ev.vtype = DLF_V_NUMBER;
		$$->ev.number = $1;
	}
	| BINARY_EXPRESSION SUB BINARY_EXPRESSION {
		$$ = dlf_binary_expression_calloc (DLF_E_SUB, $1, $3);
	}
	| BINARY_EXPRESSION ADD BINARY_EXPRESSION {
		$$ = dlf_binary_expression_calloc (DLF_E_ADD, $1, $3);
	}
	;

%%
