#pragma once

#include <stdlib.h>
#include <stdbool.h>

/*
 * A generic purpose dynamic array
 */
struct Vector {
    void **items;
    size_t capacity;
    size_t sz;
};


/*
 * Create a new vector.
 *
 * Each Vector created with this function must be deleted
 * with a call to vector_free.
 */
struct Vector *vector_new();


/*
 * Insert an item at the end of the vector.
 *
 * Return true if the operation is successful,
 * false otherwise.
 */
bool vector_push_back(struct Vector *v, void *item);


/*
 * Return a raw pointer to the element at the given position.
 *
 * If the position is out of bound, NULL is returned.
 */
void *vector_get(struct Vector *v, size_t pos);


/*
 * Delete a vector.
 *
 * Each vector deleted with this function must have been allocated
 * with a call to vector_new.
 *
 * If free_callback is not NULL it's used on each item to free the 
 * associated memory. 
 * N.B. The callback is called as-is; it's the programmer's responsibility
 * to guarantee that the function properly frees the memory.
 */
void vector_free(struct Vector *v, void (*free_callback)(void*));
