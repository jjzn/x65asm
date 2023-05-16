#ifndef __table_h
#define __table_h

typedef struct {
    char** keys;
    uint16_t* vals;

    size_t len;
    size_t cap;
} table_t;

make_maybe(uint16_t);

bool table_set(table_t*, char*, uint16_t);
size_t table_index(table_t*, char*);
maybe(uint16_t) table_get(table_t*, char*);

#endif /* __table_h */
