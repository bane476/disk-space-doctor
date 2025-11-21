#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#include "utils.h"

int compare_desc(const void *a, const void *b) {
    const FileEntry *fa = (const FileEntry*)a;
    const FileEntry *fb = (const FileEntry*)b;
    if (fa->size < fb->size) return 1;
    if (fa->size > fb->size) return -1;
    return 0;
}

/* prints top N files and top N directories from results */
void generate_report() {
    int n;
    FileEntry *list = get_results(&n);
    if (!list || n == 0) {
        printf("No results to report.\n");
        return;
    }

    /* sort all entries descending by size */
    qsort(list, n, sizeof(FileEntry), compare_desc);

    printf("\n%s=== DISK SPACE DOCTOR REPORT ===%s\n", COLOR_BOLD, COLOR_RESET);
    printf("Total items scanned: %d\n\n", n);

    /* Top files */
    printf("%sTop 10 Largest Files:%s\n", COLOR_BOLD, COLOR_RESET);
    int printed = 0;
    for (int i = 0; i < n && printed < 10; ++i) {
        if (list[i].is_dir) continue;
        char h[32];
        format_size(list[i].size, h, sizeof(h));
        /* sizes bold, path normal */
        printf("%s%s%s - %s\n", COLOR_BOLD, h, COLOR_RESET, list[i].path);
        printed++;
    }
    if (printed == 0) printf("No regular files found.\n");

    /* Top directories */
    printf("\n%sTop 10 Largest Directories:%s\n", COLOR_BOLD, COLOR_RESET);
    printed = 0;
    for (int i = 0; i < n && printed < 10; ++i) {
        if (!list[i].is_dir) continue;
        char h[32];
        format_size(list[i].size, h, sizeof(h));
        printf("%s%s%s - %s\n", COLOR_BOLD, h, COLOR_RESET, list[i].path);
        printed++;
    }
    if (printed == 0) printf("No directories found.\n");

    /* Junk detection (minimal rules) */
    printf("\nDetected Junk Files/Paths:\n");
    int junk_count = 0;
    for (int i = 0; i < n; ++i) {
        const char *p = list[i].path;
        if (!p) continue;
        /* simple patterns */
        if (ends_with(p, ".tmp") ||
            ends_with(p, ".log") ||
            ends_with(p, ".old") ||
            strstr(p, "/.cache") ||
            strstr(p, "/Trash") ||
            strstr(p, "/.local/share/Trash") ||
            strstr(p, "/node_modules") ||
            strstr(p, "/__pycache__"))
        {
            /* junk highlighted in red */
            printf("%s%s%s\n", COLOR_RED, p, COLOR_RESET);
            junk_count++;
        }
    }
    if (junk_count == 0) printf("No obvious junk found.\n");

    printf("\n%s=== END OF REPORT ===%s\n", COLOR_BOLD, COLOR_RESET);
}

