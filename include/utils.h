#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>
#include <stddef.h>

#define COLOR_BOLD  "\033[1m"
#define COLOR_RED   "\033[31m"
#define COLOR_RESET "\033[0m"

/* Convert bytes -> human readable string (writes into out with outlen) */
void format_size(off_t bytes, char *out, size_t outlen);

/* simple suffix test */
int ends_with(const char *str, const char *suffix);

/* qsort comparator: descending by size */
int compare_desc(const void *a, const void *b);

#endif

