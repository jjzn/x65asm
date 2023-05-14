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

extern void _macro_expand_panic(const char*, const char*, int, char*, ...);
#define panic(...) _macro_expand_panic(__func__, __FILE__, __LINE__, __VA_ARGS__)

#define MAX_BYTES_PER_INST 4

typedef enum {
    NONE, ACC, IMM, ZP, ABS, IDX_X, IDX_Y, IND, IDX_IND, IND_IDX
} arg_type_t;

typedef struct {
    arg_type_t type;
    uint16_t as_16;
} arg_t;

typedef enum {
	PSEUDO, INST
} line_type_t;

typedef struct {
    char* label; /* may be NULL */
    line_type_t type;
    char* op;
    arg_t arg;
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
