#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

line_t parse(char* buff) {
    /* TODO: add support for comments */

    char *label, *op, *arg;
    label = op = arg = NULL;
    line_type_t type = -1;

    char* tk = strtok(buff, " \t");
    while (tk != NULL) {
        size_t len = strlen(tk);
        if (tk[len - 1] == ':') {
            if (label == NULL)
                label = tk;
            else
                debug("parse: error: too many labels in this line\n"); /* TODO: should be a panic */

        } else if (*tk == '.') {
            if (type == (line_type_t) -1)
                type = PSEUDO;
            else
                debug("parse: error: too many pseudo-ops in this line\n"); /* TODO: should be a panic */

        } else if (op == NULL)
            op = tk;
        else if (arg == NULL)
            arg = tk;
        else
            debug("parse: error: too many arguments in this line\n"); /* TODO: should be a panic */

        tk = strtok(NULL, " \t");
    }

    return (line_t) { label, type, op, arg };
}
