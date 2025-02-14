#ifndef __defs_h
#define __defs_h

#include <stdint.h>
#include "maybe.h"

#ifdef DEBUG
    #define debug(...) do { \
        fputs("\033[2mDEBUG:\033[0m ", stderr); fprintf(stderr, __VA_ARGS__); \
    } while(0)
#else
    #define debug(...) {}
#endif /* DEBUG */

extern void _macro_expand_panic(const char*, const char*, int, char*, ...);
#define panic(...) _macro_expand_panic(__func__, __FILE__, __LINE__, __VA_ARGS__)

#define MAX_BYTES_PER_INST 4

/* REGISTER ENCODINGS FOR X86 */
#define REG_AL 0x00 /* 0b00 */
#define REG_BL 0x03 /* 0b11 */
#define REG_CL 0x01 /* 0b01 */
#define REG_DL 0x02 /* 0b10 */

/* 6502 addressing modes
 *
 * NONE, ACCumulator, IMMediate, Zero Page, ABSolute
 *
 * IDX - indexed, adds the contents of the X/Y register
 * IND - indirect, references the value stored at the pointed memory location
 * IDX_IND - indexed indirect, as in `LDA ($20,X)`, an indirect lookup to the
             memory at $20 + X
 * IND_IDX - indirect indexed, as in `LDA ($20),Y`, fetches the address at the
             specified memory location and adds the contents of Y
 */

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
