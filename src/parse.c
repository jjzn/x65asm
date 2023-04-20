#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "maybe.h"

make_maybe(arg_t);

maybe(arg_t) parse_arg(char* buff) {
    #define make_arg(type, value) (arg_t) {(type), {(value)}}

    if (*buff == '\0')
        return some(arg_t, make_arg(NONE, 0));

    if (strcmp("A", buff) == 0)
        return some(arg_t, make_arg(ACC, 0));

    if (*buff == '#')
        return some(arg_t, make_arg(IMM, strtoul(buff + 1, NULL, 0)));

    char* rest;
    unsigned long val = strtoul(buff, &rest, 0);
    if (*rest == '\0') {
        if (val <= 0xFF)
            return some(arg_t, make_arg(ZP, (uint8_t) val));
        else
            return some(arg_t, make_arg(ABS, (uint16_t) val));
    }
    /* TODO: handle indirect/indexed arguments */

    return some(arg_t, make_arg(NONE, 0));
}

line_t parse(char* buff) {
    /* TODO: add support for comments */

    char* label = calloc(1024, sizeof(char));
    if (label == NULL)
        panic("could not allocate memory\n");

    char* op = calloc(1024, sizeof(char));
    if (op == NULL)
        panic("could not allocate memory\n");

    maybe(arg_t) arg = some(arg_t, make_arg(NONE, 0));

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
        else if (!arg.ok || arg.val.type == NONE)
            arg = parse_arg(tk);
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

    return (line_t) { label, type, op, unwrap(arg, buff) };
}
