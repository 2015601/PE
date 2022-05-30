#ifndef DLF_ERROR_H
#define DLF_ERROR_H

#include <stdio.h>

#define dlf_error(fmt, ...) do { fprintf (stderr, fmt, ##__VA_ARGS__); fprintf(stderr, "\n"); } while(0)
#define dlf_log (fmt, ...) do { fprintf (stdout, fmt, ##__VA_ARGS__); fprintf(stdout, "\n"); } while (0)

#endif
