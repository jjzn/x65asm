#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

line_t parse(char* buff) {
    /* TODO: add support for comments */

    char* label = calloc(1024, sizeof(char));
    if (label == NULL)
        panic("could not allocate memory\n");

    char* op = calloc(1024, sizeof(char));
    if (op == NULL)
        panic("could not allocate memory\n");

    char* arg = calloc(1024, sizeof(char));
    if (arg == NULL)
        panic("could not allocate memory\n");

    line_type_t type = -1;

    char* tk = strtok(buff, " \t\n");
    while (tk != NULL) {
        size_t len = strlen(tk);
        if (tk[len - 1] == ':') {
            if (*label == '\0')
                strncpy(label, tk, 1024);
            else
                debug("parse: error: too many labels in this line\n"); /* TODO: should be a panic */

        } else if (*op == '\0')
            strncpy(op, tk, 1024);
        else if (*arg == '\0')
            strncpy(arg, tk, 1024);
        else
            debug("parse: error: too many arguments in this line\n"); /* TODO: should be a panic */

        if (*tk == '.') {
            if (type == (line_type_t) -1)
                type = PSEUDO;
            else
                debug("parse: error: too many pseudo-ops in this line\n"); /* TODO: should be a panic */
        }

        tk = strtok(NULL, " \t\n");
    }

    return (line_t) { label, type, op, arg };
}
