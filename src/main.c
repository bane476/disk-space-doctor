#include <stdio.h>
#include "scanner.h"
#include "report.h"

int main(int argc, char *argv[]) {
    const char *path = ".";
    if (argc >= 2) path = argv[1];

    printf("Scanning directory: %s\n", path);
    scan_directory(path);
    generate_report();
    return 0;
}

