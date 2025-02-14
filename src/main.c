#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

#include "table.h"
extern table_t labels;

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

static char* arg_names[] = {
    "NONE", "ACC", "IMM", "ZP", "ABS", "IDX_X", "IDX_Y", "IND", "IDX_IND", "IND_IDX"
};

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
        line_t line = parse(buff);

        if (buff[0] != '\0' && buff[1] != '\0')
            debug("\033[2m%s\033[0m\t%s (arg = %d)\n", buff, arg_names[line.arg.type], line.arg.as_16);

        if (line.type == INST) {
            maybe(emit_t) res = emit(line);
            if (res.ok) {
                debug("\t\t%lu values:\n", res.val.len);
                for (size_t i = 0; i < res.val.len; i++)
                    debug("\t\temit\t%x\n", res.val.value[i]);
            }
        }

        free(line.op);
        if (*line.label == '\0')
            free(line.label); /* only free if label is not included in the table */
    }

    debug("\n");
    debug("table labels\tlen = %lu\n", labels.len);
    for (size_t i = 0; i < labels.len; i++) {
        debug("\t'%s' = %u\n", labels.keys[i], labels.vals[i]);
        free(labels.keys[i]); /* free remaining labels */
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
