#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "maybe.h"

make_maybe(arg_t);

maybe(arg_t) parse_arg(char* buff) {
    #define make_arg(type, value) (arg_t) {(type), (value)}

    if (*buff == '\0')
        return some(arg_t, make_arg(NONE, 0));

    if (strcmp("A", buff) == 0)
        return some(arg_t, make_arg(ACC, 0));

    if (*buff == '#')
        return some(arg_t, make_arg(IMM, (uint16_t) strtoul(buff + 1, NULL, 0)));

    if (*buff == '(') {
        char* rest;
        unsigned long val = strtoul(buff + 1, &rest, 0);

        if (strcmp(")", rest) == 0)
            return some(arg_t, make_arg(IND, (uint16_t) val));
        else if (strcmp(",X)", rest) == 0)
            return some(arg_t, make_arg(IDX_IND, (uint16_t) val));
        else if (strcmp("),Y", rest) == 0)
            return some(arg_t, make_arg(IND_IDX, (uint16_t) val));
        else
            return none(arg_t); /* probably panic or return an error message? */
    }

    char* rest;
    unsigned long val = strtoul(buff, &rest, 0);

    if (*rest == '\0') {
        if (val <= 0xFF)
            return some(arg_t, make_arg(ZP, (uint8_t) val));
        else
            return some(arg_t, make_arg(ABS, (uint16_t) val));
    } else if (rest[0] == ',') {
        if (rest[1] == 'X')
            return some(arg_t, make_arg(IDX_X, (uint16_t) val));
        else if (rest[1] == 'Y')
            return some(arg_t, make_arg(IDX_Y, (uint16_t) val));
        else
            return none(arg_t); /* probably panic or return an error message? */
    }

    return some(arg_t, make_arg(NONE, 0));
}

line_t parse(char* buff) {
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
        /* handle comments by immediately stopping to process the current line */
        if (*tk == ';')
            break;

        size_t len = strlen(tk);
        if (tk[len - 1] == ':') {
            if (*label == '\0')
                strncpy(label, tk, 1024);
            else
                panic("too many labels in this line\n");

        } else if (*op == '\0')
            strncpy(op, tk, 1024);
        else if (!arg.ok || arg.val.type == NONE)
            arg = parse_arg(tk);
        else
            panic("too many arguments in this line\n");

        if (type == (line_type_t) -1) {
            if (*tk == '.')
                type = PSEUDO;
            else
                type = INST;
        } else if (*tk == '.')
            panic("too many pseudo-ops in this line\n");

        tk = strtok(NULL, " \t\n");
    }

    return (line_t) { label, type, op, unwrap(arg, buff) };
}
