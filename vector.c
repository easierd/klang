#include <stdio.h>

#include "vector.h"


enum {
    DEFAULT_CAPACITY = 32,
};


bool vector_reallocate(struct Vector **v) {
    (*v)->items = realloc((*v)->items, (*v)->capacity * 2 * sizeof(void*));
    if ((*v)->items == NULL) {
        perror("vector_push_back");
        return false;
    }
    (*v)->capacity *= 2;
    return true;
}


struct Vector *vector_new() {
    struct Vector *v = malloc(sizeof(struct Vector));
    if (v == NULL) {
        perror("vector_init");
        return NULL;
    }

    v->items = malloc(sizeof(void*) * DEFAULT_CAPACITY);
    if (v->items == NULL) {
        perror("vector_init");
        free(v);
        return NULL;
    }

    v->sz = 0;

    v->capacity = DEFAULT_CAPACITY;

    return v;
}


void vector_free(struct Vector *v, void (*free_callback)(void *)) {
    if (free_callback != NULL) {
        for (size_t i = 0; i < v->sz; i++) {
            free_callback(v->items[i]);
        }
    }
    free(v->items);
    free(v);
}


bool vector_push_back(struct Vector *v, void *item) {
    if (v->sz == v->capacity) {
        if (!vector_reallocate(&v)) {
            return false;
        }
    }

    v->items[v->sz++] = item;
    return true;
}


void *vector_get(struct Vector *v, size_t pos) {
    if (pos >= v->sz) {
        fprintf (stderr, "Index %zu out of bound", pos);
        return NULL;
    }

    return v->items[pos];
}
