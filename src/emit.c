#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "maybe.h"
#include "encoding.h"

typedef emit_t (*emitter)(line_t);

emit_t emit_lda(line_t line) {
    uint8_t bin[] = { 0x8B, REG_AL };

    return (emit_t) { CODE, sizeof(bin), bin };
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
        return (maybe(emit_t)) none();

    for (size_t i = 0; i < sizeof(inst_6502); i++) {
        if (strcmp(inst_6502[i], line.op) == 0)
            return (maybe(emit_t)) some(inst_x86[i](line));
    }

    return (maybe(emit_t)) none();
}
