#ifndef __defs_h
#define __defs_h

#ifdef DEBUG
    #define debug(...) do { \
        fputs("DEBUG: ", stderr); fprintf(stderr, __VA_ARGS__); \
    } while(0)
#else
    #define debug(...)
#endif /* DEBUG */

#define panic(...) do { \
    fprintf(stderr, "fatal: %s: ", __func__); \
    fprintf(stderr, __VA_ARGS__); \
    exit(1); \
} while(0)

/* syntax: [label:] pseudp-op|op [operand] */

typedef enum {
	PSEUDO, INST
} line_type_t;

typedef struct {
    char* label; /* may be NULL */
    line_type_t type;
    char* op;
    char* arg;
} line_t;

extern line_t parse(char*);

#endif /* __defs_h */
