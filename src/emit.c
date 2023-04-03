#include <stdlib.h>

#include "defs.h"
#include "maybe.h"

maybe(emit_t) emit(line_t line) {
    /* TODO: handle pseudo-ops somewhere */
    if (line.type == PSEUDO)
        return (maybe(emit_t)) none();

    return (maybe(emit_t)) none(); /* TODO: implement */
}
