#include <stdio.h>
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

maybe(emit_t) _emit_load(line_t line, uint8_t reg) {
    size_t len = 0;
    uint8_t bin[MAX_BYTES_PER_INST];

    switch (line.arg.type) {
        case IMM:
            len = 2;

            bin[0] = 0xB0 + reg;
            bin[1] = line.arg.as_8;
            break;

        case ZP:
        case ABS:
            len = 4;

            /* the ModR/M byte will be 00 RRR 110, meaning a 16 bit displacement */
            bin[0] = 0x8A;
            bin[1] = 0x06 | (reg << 3);
            bin[2] = line.arg.as_16; /* little-endian encoding */
            bin[3] = line.arg.as_16 >> 8;
            break;

        default:
            return none(emit_t);
    }

    emit_t res = { CODE, len, {0} };
    memcpy(res.value, bin, len);

    return some(emit_t, res);
}

maybe(emit_t) emit_lda(line_t line) {
    allow_args(line, IMM, ZP, ABS);

    debug("emitting --> '%s'\n", __func__);
    return _emit_load(line, REG_AL);
}

maybe(emit_t) emit_ldx(line_t line) {
    allow_args(line, IMM, ZP, ABS);

    debug("emitting --> '%s'\n", __func__);
    return _emit_load(line, REG_BL);
}

maybe(emit_t) emit_ldy(line_t line) {
    allow_args(line, IMM, ZP, ABS);

    debug("emitting --> '%s'\n", __func__);
    return _emit_load(line, REG_CL);
}

static char* inst_6502[] = {
    "lda", "ldx", "ldy"
};

static emitter inst_x86[] = {
    emit_lda, emit_ldx, emit_ldy
};

maybe(emit_t) emit(line_t line) {
    /* TODO: handle pseudo-ops somewhere */
    if (line.type == PSEUDO)
        return none(emit_t);

    for (size_t i = 0; i < sizeof(inst_6502); i++) {
        debug("emitting for %s\n", line.op);

        if (strcmp(inst_6502[i], line.op) == 0) {
            return inst_x86[i](line);
        }
    }

    return none(emit_t);
}
