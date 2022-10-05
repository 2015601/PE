#ifndef DLF_H
#define DLF_H

#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>

#include "list.h"
#include "dlf_error.h"
#include "dlf_memory.h"
#include "dlf_object.h"

struct dlf_value * dlf_expression_eva (struct dlf_expression *expression);

int dlf_execute (struct dlf_context *context);

#endif
