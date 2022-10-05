%{
#include "dlf.h"
#include "lexical.h"

static void dlf_statement_insert (struct dlf_statement *statement)
{
	struct dlf_context * context;

	context = current_script_file->context;

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

static void yyerror(const char * error) {
	puts(error);
}

#define YYDEBUG 0
#define YYPRINT(file, type, value) { \
}

static int current_func_call_arg_cnt;

%}

%error-verbose

%union {
	struct dlf_statement *s;
	struct dlf_expression *e;
	struct dlf_value args[MAX_ARG_COUNT];
	struct dlf_value v;
	struct dlf_identifier *i;
	const char *string;
	int number;
}

%token LP RP LB RB SEMICOLON EQ COMMA
%token FUNCTION IF ELIF ELSE WHILE FOR RETURN EQUAL
%token FALSE TRUE
%token <number> NUMBER
%token <string> STRING
%token <i> IDENTIFIER
%type <args> ARGS FUNC_ARG
%type <v> ARG
%type <s> ASSIGN_STATEMENT FUN_CALL
%type <e> EXPRESSION BINARY_EXPRESSION
%left ADD SUB

%%

STATEMENTS : /* empty */
	|	STATEMENTS ASSIGN_STATEMENT { dlf_statement_insert($2); }
	|	STATEMENTS FUN_CALL { dlf_statement_insert($2); }
	;

ASSIGN_STATEMENT : IDENTIFIER EQUAL EXPRESSION {
		if ($1->itype == DLF_I_NIL) {
			$1->itype = DLF_I_VAR;
		} else if ($1->itype != DLF_I_VAR) {
			dlf_panic("error statement, var cant assign");
		}
		$$ = dlf_calloc (sizeof(struct dlf_statement), 1);
		$$->stype = DLF_S_ASSIGN;
		$$->s_assign.i = $1;
		$$->s_assign.e = $3;
	}
	;

EXPRESSION : BINARY_EXPRESSION /* default $$ = $1 */
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

FUN_CALL : IDENTIFIER LP FUNC_ARG RP {
		if ($1->itype != DLF_I_FUNC) {
			dlf_panic("var is not func");
		}
		$$ = dlf_calloc (sizeof(struct dlf_statement), 1);
		$$->stype = DLF_S_FUNCALL;
		$$->s_func.fi = $1;
		$$->s_func.arg_count = current_func_call_arg_cnt;
		current_func_call_arg_cnt = 0;
		memcpy($$->s_func.args, $3, sizeof($3));
	}
	;

FUNC_ARG: /* empty */ { memset($$, 0, sizeof($$)); }
	| ARGS { (void*)0; }
	;

ARGS : ARG {
		$$[current_func_call_arg_cnt++] = $1;
	}
	| ARGS SEMICOLON ARG {
		if (current_func_call_arg_cnt == MAX_ARG_COUNT) {
			dlf_panic("error arg");
		}
		$$[current_func_call_arg_cnt++] = $3;
	}
	;

ARG : NUMBER {
		$$.vtype = DLF_V_NUMBER;
		$$.number = $1;
	}
	| STRING {
		$$.vtype = DLF_V_STRING;
		$$.str = strdup($1) ;
	}
	| IDENTIFIER {
		$$.vtype = DLF_V_VAR;
		$$.id = $1;
	}
	;

%%
