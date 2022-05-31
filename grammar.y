%{
#include "dlf.h"

void dlf_statement_insert (struct dlf_statement *statement);
static struct dlf_identifier * dlf_identifier_new (const char * name);

static struct dlf_expression * dlf_binary_expression_calloc (int type,
	struct dlf_expression *l, struct dlf_expression *r)
{
	struct dlf_expression *e = dlf_calloc(sizeof (struct dlf_expression), 1);
	e->etype = type;
	e->binary.l = l;
	e->binary.r = r;
}

static struct dlf_identifier_new (const char *name)
{
	struct dlf_identifier *i;

	i = dlf_identifier_get (name);
	if (i) {
		return i;
	}
	
}


%}

%union {
	struct dlf_statement *s;
	struct dlf_expression *e;
	int number;
}

%token LP RP LB RB SEMICOLON EQ COMMA
%token FUNCTION IF ELIF ELSE WHILE FOR RETURN EQUAL
%token FALSE TRUE
%token <number> NUMBER
%token IDENTIFIER STRING
%type BLOCK
%type STATEMENT
%type STATEMENTS
%type <s> ASSIGN_STATEMENT
%type IDENTIFIER_STATEMENT
%type EXPRESSION
%type <e> ADD_EXPRESSION SUB_EXPRESSION
%left ADD SUB

%%

STATEMENTS : /* empty */
	|	STATEMENTS STATEMENT { dlf_statement_insert($2); }
	;

STATEMENT : ASSIGN_STATEMENT
	;

ASSIGN_STATEMENT :	IDENTIFIER EQUAL EXPRESSION {
		struct dlf_identifier *i = dlf_identifier_new ($1);
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
