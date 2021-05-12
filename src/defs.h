#ifndef __defs_h
#define __defs_h

#ifdef DEBUG
    #define debug(...) fprintf(stderr, "DEBUG: " __VA_ARGS__)
#else
    #define debug(...)
#endif /* DEBUG */

/* syntax: [label:] pseudp-op|op [operand] */

typedef struct {
    char* label; /* may be NULL */
    enum { PSEUDO, INST } type;
    char* op;
    char* arg;
} line_t;

#endif /* __defs_h */
