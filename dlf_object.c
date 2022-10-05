#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "list.h"
#include "dlf_object.h"
#include "dlf_error.h"
#include "dlf_memory.h"

struct dlf_file *current_script_file;

struct dlf_identifier * dlf_identifier_get (const char *name)
{
	struct dlf_identifier *i;

	slist_walk (&current_script_file->context->idents, i, _n) {
		if (!strcmp (i->name, name)) {
			return i;
		}
	}

	return NULL;
}

struct dlf_identifier *  dlf_identifier_new (const char *name, int type)
{
	struct dlf_identifier *i;
	struct dlf_context *context;

	i = dlf_identifier_get (name);
	if (i) {
		return i;
	}

	context = current_script_file->context;

	i = dlf_calloc(sizeof (struct dlf_identifier), 1);
	i->itype = type;
	i->name = strdup (name);

	slist_insert_tail(&context->idents, i, _n);

	return i;
}

struct dlf_value *dlf_value_new(int type)
{
	struct dlf_value *value = dlf_calloc(1, sizeof(struct dlf_value));

	value->vtype = type;


	return value;
}

struct dlf_file * dlf_file_create (const char *filename)
{
	struct dlf_file *file;

	file = dlf_calloc(sizeof (struct dlf_file), 1);

	file->file = fopen (filename, "r");
	if (!file->file) {
		dlf_log("open file %s error", filename);
		goto err;
	}

	file->file_name = filename;

	file->context = dlf_calloc(sizeof(struct dlf_context), 1);

	return file;

err:
	if (file->file) {
		fclose(file->file);
	}
	dlf_free(file);
}
