%{
	unsigned line_no;
%}

%union {
	unsigned tok;
}

%token LP RP LB RB SEMICOLON EQ COMMA
%token FUNCTION IF ELIF ELSE WHILE FOR RETURN
%token FALSE TRUE
%type IDENTIFIER
%type BLOCK
%left ADD SUB

%%

BLOCK: /* empty */


%%
