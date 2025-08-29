#pragma once

#include "vector.h"

struct Scanner {
    char *line;
    int start;
    int current;
};


/*
 * Create a new Scanner to retrieve tokens from the given line
 *
 * Each Scanner object created with this function must be deleted
 * with a call to scanner_delete.
 */
struct Scanner *scanner_new(char *line);


/*
 * Delete the scanner.
 *
 * Each Scanner object deleted with this function must
 * have been created with a call to scanner_new.
 */
void scanner_delete(struct Scanner*);


/*
 * Return a Vector of tokens from the scanner line
 */
struct Vector *scan_tokens(struct Scanner *s);
