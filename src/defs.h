#ifndef __defs_h
#define __defs_h

#include <stdint.h>
#include "maybe.h"

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

#define MAX_BYTES_PER_INST 4

typedef enum {
	PSEUDO, INST
} line_type_t;

typedef struct {
    char* label; /* may be NULL */
    line_type_t type;
    char* op;
    char* arg;
} line_t;

typedef enum {
    LABEL, CODE
} emit_type_t;

typedef struct {
    emit_type_t type;
    size_t len;
    uint8_t value[MAX_BYTES_PER_INST];
} emit_t;

make_maybe(emit_t);

extern line_t parse(char*);
extern maybe(emit_t) emit(line_t);

#endif /* __defs_h */
