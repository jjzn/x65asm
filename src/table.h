#ifndef __table_h
#define __table_h

#define MAX_TABLE_SIZE 1024

typedef struct {
    size_t len;
    char* keys[MAX_TABLE_SIZE];
    uint16_t vals[MAX_TABLE_SIZE];
} table_t;

make_maybe(uint16_t);

bool table_set(table_t*, char*, uint16_t);
size_t table_index(table_t*, char*);
maybe(uint16_t) table_get(table_t*, char*);

#endif /* __table_h */
