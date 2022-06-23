#ifndef DLF_LIST_H
#define DLF_LIST_H

#define slist_entry(type) type *
#define slist_construct(type) struct { \
	type *__tail; \
	type *__head; \
}

#define slist_init(head) (head)->__tail = (head)->__head = NULL

#define slist_walk(head, var, entry) \
for (var = (head)->__head; var != NULL; var = (var)->entry)

#define slist_insert_tail(head, var, entry) \
do { \
	(var)->entry = NULL; \
	if ((head)->__head == NULL) { \
		(head)->__head = (head)->__tail = var; \
	} else { \
		(head)->__tail->entry = var; \
		(head)->__tail = var; \
	} \
} while (0)

#define slist_insert_head(head, var, entry) \
do { \
	(var)->entry = NULL; \
	if ((head)->__head == NULL) { \
		(head)->__head = (head)->__tail = var; \
	} else { \
		(var)->entry = (head)->__head; \
		(head)->__head = var; \
	}\
} while (0)

#define slist_remove(head, var, entry, type) \
do { \
	for (type *prevptr = NULL, *curptr = (head)->__head; curptr != 0; curptr = curptr->entry) { \
		if (curptr == var) { \
			if (curptr == (head)->__head) { \
				(head)->__head = curptr->entry; \
			} \
			if (curptr == (head)->__tail) { \
				(head)->__tail = prevptr; \
			} \
			if (prevptr) { \
				prevptr->entry = curptr->entry; \
			} \
			break; \
		} \
		prevptr = curptr; \
	} \
} while (0)

#define slist_fist(head) (head->__head)
#define slist_last(head) (head->__tail)

#endif
