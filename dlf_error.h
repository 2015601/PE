#ifndef DLF_ERROR_H
#define DLF_ERROR_H

#include <stdio.h>

#define dlf_error(fmt, ...) fprintf (stderr, fmt, ##__VA_ARGS__)
#define dlf_log (fmt, ...) fprintf (stdout, fmt, ##__VA_ARGS__)

#endif
