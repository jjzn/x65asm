#ifndef __defs_h
#define __defs_h

#ifdef DEBUG
    #define debug(...) do { \
        fputs("DEBUG: ", stderr); fprintf(stderr, __VA_ARGS__); \
    } while(0)
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

extern line_t parse(char*);

#endif /* __defs_h */
