#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "maybe.h"
#include "encoding.h"

#define allow_args(line, ...) \
    arg_type_t _allowed_args[] = { __VA_ARGS__ }; \
    bool _allowed_ok = false; \
    for (size_t i = 0; i < sizeof(_allowed_args) / sizeof(arg_type_t); i++) \
        _allowed_ok = _allowed_ok || line.arg.type == _allowed_args[i]; \
    if (!_allowed_ok) \
        return none(emit_t);

typedef maybe(emit_t) (*emitter)(line_t);

maybe(emit_t) emit_lda(line_t line) {
    allow_args(line, IMM, ZP, ABS, IDX, IND, IDX_IND, IND_IDX);

    uint8_t bin[] = { 0x8B, REG_AL };

    emit_t res = { CODE, sizeof(bin), bin };
    return some(emit_t, res);
}

static char* inst_6502[] = {
    "lda"
};

static emitter inst_x86[] = {
    emit_lda
};

maybe(emit_t) emit(line_t line) {
    /* TODO: handle pseudo-ops somewhere */
    if (line.type == PSEUDO)
        return none(emit_t);

    for (size_t i = 0; i < sizeof(inst_6502); i++) {
        if (strcmp(inst_6502[i], line.op) == 0) {
            return inst_x86[i](line);
        }
    }

    return none(emit_t);
}
