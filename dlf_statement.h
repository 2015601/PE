enum {
	DLF_S_ASSIGN,
	DLF_S_IDENT,
};


struct dlf_statement {
	int stype;
	unsigned line_n;
	union {
		struct {
			struct dlf_identifier i;
			struct dlf_expression e;
		} s_assign;
	} ;
	slist_entry(struct dlf_statement) _n;
};

static inline int dlf_s_assign (struct dlf_statement * statement) {
	
}