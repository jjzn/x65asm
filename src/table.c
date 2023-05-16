#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "maybe.h"
#include "table.h"

bool table_set(table_t* t, char* key, uint16_t val) {
    size_t idx = table_index(t, key);

    if (idx >= t->len) {
        idx = t->len;
        t->len++;
    }

    if (t->len >= MAX_TABLE_SIZE)
        return false;

    t->keys[idx] = key;
    t->vals[idx] = val;

    return true;
}

size_t table_index(table_t* t, char* key) {
    /* TODO: guard against overflows */
    size_t idx = t->len + 1;

    for (size_t i = 0; i < t->len; i++) {
        if (strcmp(key, t->keys[i]) == 0) {
            idx = i;
            break;
        }
    }

    return idx;
}


maybe(uint16_t) table_get(table_t* t, char* key) {
    size_t idx = table_index(t, key);

    if (idx < t->len)
        return some(uint16_t, t->vals[idx]);
    else
        return none(uint16_t);
}
