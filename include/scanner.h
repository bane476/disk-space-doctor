#ifndef SCANNER_H
#define SCANNER_H

#include <sys/types.h>

typedef struct FileEntry {
    char path[4096];
    off_t size;
    int is_dir;
} FileEntry;

void scan_directory(const char *path);
FileEntry *get_results(int *count);

#endif

