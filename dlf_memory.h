#ifndef DLF_MEMORY_H
#define DLF_MEMORY_H

#include <malloc.h>
#include "dlf_error.h"

static inline void * dlf_calloc(size_t ele_size, unsigned eles)
{
	void * p;

	p = calloc(ele_size, eles);
	if (!p) {
		dlf_error("calloc error, size = %lu", ele_size * eles);
	}

	return p;
}

static inline void * dlf_alloc(size_t size)
{
	void *p;

	p = malloc (size);
	if (!p) {
		dlf_error ("alloc error, size = %lu", size);
	}

	return p;
}

static inline void dlf_free(void *p)
{
	free (p);
}

#endif
