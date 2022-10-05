%{
#include <stdlib.h>
#include "dlf.h"
#include "grammar.h"
#undef YY_INPUT

#define YY_INPUT(buf, result, max_size) \
	result = fread(buf, 1, max_size, DLFFILE->file)

static char string_buffer[0xffff];
static int string_length;

%}

%option noyywrap
%x LSTRING

%%

<INITIAL>"function"	return FUNCTION;
<INITIAL>"if"	return IF;
<INITIAL>"elif"	return ELIF;
<INITIAL>"else"	return ELSE;
<INITIAL>"while"	return WHILE;
<INITIAL>"for"	return FOR;
<INITIAL>"return"	return RETURN;
<INITIAL>";"	return SEMICOLON;
<INITIAL>"="	return EQUAL;
<INITIAL>","	return COMMA;
<INITIAL>"+"	return ADD;
<INITIAL>"-"	return SUB;
<INITIAL>"("	return LP;
<INITIAL>")"	return RP;
<INITIAL>"{"	return LB;
<INITIAL>"}"	return RB;

<INITIAL>[0-9]+	{
	/* constant */
	yylval.number = atoi(yytext);
	return NUMBER;
}

<INITIAL>[a-zA-Z_][a-zA-Z_0-9]*	{
	/* identifier */
	struct dlf_identifier *i = dlf_identifier_new (yytext, DLF_I_VAR);
	if (!i) {
		dlf_panic("new identifier error");
	}
	yylval.i = i;
	return IDENTIFIER;
}

<INITIAL>\"	{
	string_length = 0;
	memset(string_buffer, 0, sizeof(string_buffer));
	BEGIN(LSTRING);
}
<LSTRING>\"	{
	BEGIN(0);
	yylval.string = string_buffer;
	return STRING;
}

<LSTRING>\\\"	{ string_buffer[string_length++]='"'; }
<LSTRING>\\n	{ string_buffer[string_length++]='\n'; }
<LSTRING>\\t	{ string_buffer[string_length++]='\t'; }
<LSTRING>\\\\	{ string_buffer[string_length++]='\\'; }
<LSTRING>. { string_buffer[string_length++]=yytext[0]; }


<INITIAL>.
<INITIAL>\n

%%
