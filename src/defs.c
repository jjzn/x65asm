#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void _macro_expand_panic(const char* func, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "fatal: %s: ", func);
    vfprintf(stderr, fmt, args);

    va_end(args);
    exit(1);
}

