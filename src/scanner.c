#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "scanner.h"

static FileEntry results[50000];
static int idx = 0;

/* compute size recursively; returns 0 on error or empty dir */
static off_t compute_directory_size(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return 0;

    off_t total = 0;
    struct dirent *entry;
    char buf[4096];

    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        /* construct full path */
        int n = snprintf(buf, sizeof(buf), "%s/%s", path, entry->d_name);
        if (n <= 0 || n >= (int)sizeof(buf)) continue;

        struct stat st;
        if (lstat(buf, &st) != 0) continue;

        if (S_ISDIR(st.st_mode)) {
            total += compute_directory_size(buf);
        } else if (S_ISREG(st.st_mode)) {
            total += st.st_size;
        } else {
            /* ignore symlinks, sockets, devices for size accounting */
        }
    }

    closedir(dir);
    return total;
}

void scan_directory(const char *path) {
    /* basic bounds safety */
    if (!path) return;
    if (idx >= (int)(sizeof(results)/sizeof(results[0]))) return;

    struct stat st;
    if (lstat(path, &st) != 0) return;

    off_t size = 0;
    int isdir = S_ISDIR(st.st_mode);

    if (isdir) {
        size = compute_directory_size(path);
    } else if (S_ISREG(st.st_mode)) {
        size = st.st_size;
    }

    /* store entry (path, size, is_dir) */
    strncpy(results[idx].path, path, sizeof(results[idx].path) - 1);
    results[idx].path[sizeof(results[idx].path)-1] = '\0';
    results[idx].size = size;
    results[idx].is_dir = isdir ? 1 : 0;
    idx++;

    /* if directory, recurse into children (to collect per-path sizes) */
    if (!isdir) return;

    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    char child[4096];
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        int n = snprintf(child, sizeof(child), "%s/%s", path, entry->d_name);
        if (n <= 0 || n >= (int)sizeof(child)) continue;
        scan_directory(child);
        if (idx >= (int)(sizeof(results)/sizeof(results[0]))) break;
    }

    closedir(dir);
}

FileEntry *get_results(int *count) {
    if (count) *count = idx;
    return results;
}

