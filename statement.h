struct nd_expression expression;
#define ND_STATEMENT_CONSTRUCT_expression() \
do { \
	struct nd_statement *new_statement = malloc(sizeof (struct nd_statement)); \
	new_statement->etype = 0; \
} while(0)