#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "maybe.h"
#include "table.h"
#include "encoding.h"

#define allow_args(line, ...) \
    arg_type_t _allowed_args[] = { __VA_ARGS__ }; \
    bool _allowed_ok = false; \
    for (size_t i = 0; i < sizeof(_allowed_args) / sizeof(arg_type_t); i++) \
        _allowed_ok = _allowed_ok || line.arg.type == _allowed_args[i]; \
    if (!_allowed_ok) \
        return none(emit_t);

typedef maybe(emit_t) (*emitter)(line_t);

table_t labels = { 0 };

maybe(emit_t) _emit_load(line_t line, uint8_t reg) {
    size_t len = 0;
    uint8_t bin[MAX_BYTES_PER_INST];

    switch (line.arg.type) {
        case IMM:
            len = 2;

            bin[0] = 0xB0 + reg;
            bin[1] = (uint8_t) line.arg.as_16;
            break;

        case ZP:
        case ABS:
            len = 4;

            /* the ModR/M byte will be 00 RRR 110, meaning a 16 bit displacement */
            bin[0] = 0x8A;
            bin[1] = (uint8_t) (0x06 | (reg << 3));
            bin[2] = (uint8_t) line.arg.as_16; /* little-endian encoding */
            bin[3] = (uint8_t) (line.arg.as_16 >> 8);
            break;

        default:
            return none(emit_t);
    }

    emit_t res = { CODE, len, {0} };
    memcpy(res.value, bin, len);

    return some(emit_t, res);
}

maybe(emit_t) _emit_store(line_t line, uint8_t reg) {
    size_t len = 0;
    uint8_t bin[MAX_BYTES_PER_INST];

    switch (line.arg.type) {
        case ZP:
        case ABS:
            len = 4;

            bin[0] = 0x88;
            bin[1] = (uint8_t) (0x06 | (reg << 3));
            bin[2] = (uint8_t) line.arg.as_16; /* little-endian encoding */
            bin[3] = (uint8_t) (line.arg.as_16 >> 8);
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

maybe(emit_t) emit_sta(line_t line) {
    allow_args(line, ZP, ABS);

    debug("emitting --> '%s'\n", __func__);
    return _emit_store(line, REG_AL);
}

maybe(emit_t) emit_stx(line_t line) {
    allow_args(line, ZP, ABS);

    debug("emitting --> '%s'\n", __func__);
    return _emit_store(line, REG_BL);
}

maybe(emit_t) emit_sty(line_t line) {
    allow_args(line, ZP, ABS);

    debug("emitting --> '%s'\n", __func__);
    return _emit_store(line, REG_CL);
}

maybe(emit_t) emit_inx(line_t line) {
    allow_args(line, NONE);

    debug("emitting --> '%s'\n", __func__);
    emit_t res = { CODE, 1, { 0x40 + REG_AL } };
    return some(emit_t, res);
}

maybe(emit_t) emit_iny(line_t line) {
    allow_args(line, NONE);

    debug("emitting --> '%s'\n", __func__);
    emit_t res = { CODE, 1, { 0x40 + REG_BL } };
    return some(emit_t, res);
}

maybe(emit_t) emit_dex(line_t line) {
    allow_args(line, NONE);

    debug("emitting --> '%s'\n", __func__);
    emit_t res = { CODE, 1, { 0x48 + REG_AL } };
    return some(emit_t, res);
}

maybe(emit_t) emit_dey(line_t line) {
    allow_args(line, NONE);

    debug("emitting --> '%s'\n", __func__);
    emit_t res = { CODE, 1, { 0x48 + REG_BL } };
    return some(emit_t, res);
}

#define INST_MNEMONIC_LEN 4
static char inst_6502[][INST_MNEMONIC_LEN] = {
    "lda", "ldx", "ldy",
    "sta", "stx", "sty",
           "inx", "iny",
           "dex", "dey" /* TODO: implement INC and DEC */
};

static emitter inst_x86[] = {
    emit_lda, emit_ldx, emit_ldy,
    emit_sta, emit_stx, emit_sty,
              emit_inx, emit_iny,
              emit_dex, emit_dey
};

maybe(emit_t) emit(line_t line) {
    /* TODO: handle pseudo-ops somewhere */
    if (line.type == PSEUDO)
        return none(emit_t);

    if (*line.label) {
        uint16_t pos = 0; /* TODO: implement */
        if (!table_set(&labels, line.label, pos))
            debug("emit: error: could not insert label into table\n"); /* TODO: should be a panic */
    }

    for (size_t i = 0; i < sizeof(inst_6502) / INST_MNEMONIC_LEN; i++) {
        if (strcmp(inst_6502[i], line.op) == 0) {
            return inst_x86[i](line);
        }
    }

    return none(emit_t);
}
