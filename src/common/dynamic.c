//
// Created by walid on 22/11/2026.
//
#include "dynamic.h"
#include <stdlib.h>
#include <string.h>

#define DA_INITIAL_CAP 8

DArray* da_create(size_t elem_size) {

    if (elem_size == 0) return NULLl;

    DArray *darr;
    darr = malloc(sizeof(DArray));
    if (darr == NULL) {
        return NULL;
    }

    darr->elem_size = elem_size;
    darr->len = 0;
    darr->cap = DA_INITIAL_CAP;
    darr->data = malloc(darr->elem_size * darr->cap);


    if (darr->data == NULL) {
        free(darr);
        return NULL;
    }
    return darr;
}

void da_destroy(DArray *darr) {

    if (darr == NULL) return;

    free(darr->data);
    free(darr);
}

int da_push(DArray *darr, const void *elem) {

    if (darr == NULL) return -1;
    if (elem == NULL) return -1;

    if (darr->len >= darr->cap) {
        void * tmp = realloc(darr->data, darr->cap * darr->elem_size * 2);

        if (tmp == NULL) {
            return -1;
        }

        darr->data = tmp;
        darr->cap *= 2;
    }

    void *dest = (char *)darr->data + darr->len * darr->elem_size;
    memcpy(dest, elem, darr->elem_size);

    darr->len++;
    return 0;
}

void *da_get(const DArray *darr, size_t idx) {
    if (darr == NULL) return NULL;
    if (idx >= darr->len) return NULL;

    return (char *)darr->data + idx * darr->elem_size;
}

int da_pop(DArray *darr) {
    if (darr == NULL) return -1;
    if (darr->len == 0) return -1;

    // no need to clear the bytes, anything at index >= len is considered free
    darr->len--;

    return 0;
}