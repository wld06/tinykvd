//
// Created by walid on 22/11/2026.
//

#ifndef TINYKVD_DYNAMIC_H
#define TINYKVD_DYNAMIC_H

# include  <stddef.h>

typedef struct {
    void * data;
    size_t elem_size;
    size_t len;
    size_t cap;
} DArray;

DArray* da_create(size_t elem_size);
void da_destroy(DArray *darr);
int da_push(DArray *darr, const void *elem);
void *da_get(const DArray *darr, size_t idx);
int da_pop(DArray *darr);

#endif //TINYKVD_DYNAMIC_H
