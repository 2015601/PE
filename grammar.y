%{
#include "dlf.h"

void dlf_statement_insert (struct dlf_statement *statement);
static struct dlf_identifier * dlf_identifier_new (const char * name);

%}

%union {
	struct 
}

%token LP RP LB RB SEMICOLON EQ COMMA
%token FUNCTION IF ELIF ELSE WHILE FOR RETURN EQUAL
%token FALSE TRUE
%token IDENTIFIER STRING NUMBER
%type BLOCK
%type STATEMENT
%type STATEMENTS
%type ASSIGN_STATEMENT
%type IDENTIFIER_STATEMENT
%type EXPRESSION ADD_EXPRESSION SUB_EXPRESSION
%left ADD SUB

%%

STATEMENTS : /* empty */
	|	STATEMENTS STATEMENT { dlf_statement_insert($2); }
	;

STATEMENT : ASSIGN_STATEMENT
	;

ASSIGN_STATEMENT :	IDENTIFIER EQUAL EXPRESSION {
		struct dlf_identifier *i = dlf_identifier_add ($1);
		$$ = dlf_alloc (sizeof(struct dlf_statement));
		$$->stype = DLF_S_ASSIGN;
		$$->s_assign.i = i;
		$$->s_assign.e = $3;
	}
	;

EXPRESSION : ADD_EXPRESSION
	| SUB_EXPRESSION
	| EXPRESSION ADD_EXPRESSION
	| EXPRESSION SUB_EXPRESSION
	;

SUB_EXPRESSION : NUMBER SUB NUMBER {
		struct dlf_expression *e = dlf_alloc ()
		$$ = $1 - $2;
	}
	;

ADD_EXPRESSION : NUMBER ADD NUMBER {
		$$ = $1 + $2;
	}
	;

%%

static struct dlf_statement * dlf_statement_insert (const char *name)
{

	return NULL;
}

static struct dlf_identifier * dlf_identifier_add (const char * name)
{
	return NULL;
}