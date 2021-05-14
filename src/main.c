#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

extern line_t parse(char*);

static char* replace_suffix(const char* str, const char* suff) {
    char* dot = strrchr(str, '.');

    size_t stem = dot == NULL ? strlen(str) : (size_t) (dot - str);
    size_t len = strlen(suff) + stem + 1;
    
    char* ret = calloc(len, sizeof(char));
    if (ret == NULL)
        return NULL;

    strncpy(ret, str, stem); /* copy the stem of str */
    strcat(ret, suff); /* append the suffix */
    ret[len - 1] = '\0'; /* ensure the string is null-terminated */

    return ret;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        return 0;
    }

    char* name = argv[1];
    char* output = replace_suffix(name, ".img");

    if (output == NULL) {
        fputs("fatal: memory allocation error, aborting...\n", stderr);
        return 1;
    }

    debug("assembling %s --> %s\n", name, output);

    FILE* in = fopen(name, "r");
    if (in == NULL) {
        perror(name);
        free(output);
        return 1;
    }

    char buff[1024];
    while (fgets(buff, sizeof(buff), in) != NULL) {
        debug("reading line: %s\n", buff);

        line_t line = parse(buff);
        debug(line.type == PSEUDO ? "got pseudo-op" : "got instruction");
    }

    if (ferror(in)) {
        perror(name);
        fclose(in);
        free(output);
        return 1;
    }

    fclose(in);
    free(output);
    return 0;
}
