#include "utils.h"
#include <stdio.h>
#include <string.h>

void format_size(off_t bytes, char *out, size_t outlen) {
    const double KB = 1024.0;
    const double MB = 1024.0 * 1024.0;
    const double GB = 1024.0 * 1024.0 * 1024.0;

    if (bytes >= (off_t)GB) {
        snprintf(out, outlen, "%.2f GB", bytes / GB);
    } else if (bytes >= (off_t)MB) {
        snprintf(out, outlen, "%.2f MB", bytes / MB);
    } else if (bytes >= (off_t)KB) {
        snprintf(out, outlen, "%.2f KB", bytes / KB);
    } else {
        snprintf(out, outlen, "%ld B", (long)bytes);
    }
}

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr) return 0;
    return strcmp(str + lenstr - lensuffix, suffix) == 0;
}


