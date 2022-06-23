%{
#include "dlf.h"
#include "grammar.h"
#undef YY_INPUT

#define YY_INPUT(buf, result, max_size) \
	result = fread(buf, 1, max_size, DLFFILE->file)

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
<INITIAL>"="	return EQ;
<INITIAL>","	return COMMA;
<INITIAL>"+"	return ADD;
<INITIAL>"-"	return SUB;
<INITIAL>"("	return LP;
<INITIAL>")"	return RP;
<INITIAL>"{"	return LB;
<INITIAL>"}"	return RB;

<INITIAL>[0-9]+	{ 
	/* constant */
}

<INITIAL>[a-zA-Z_][a-zA-Z_0-9]*	{
	/* identifier */
}

<INITIAL>\"	{
	BEGIN(LSTRING);
}
<LSTRING>\"	{
	BEGIN(0);
}
<LSTRING>\\\"	{ }
<LSTRING>\\n	{ }
<LSTRING>\\t	{ }
<LSTRING>\\\\	{ }
