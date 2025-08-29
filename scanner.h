#pragma once

#include "vector.h"

struct Scanner {
    char *line;
    int start;
    int current;
};


/*
 * Initialize the given scanner to retrieve tokens
 * from the given line
 */
void scanner_init(struct Scanner *s, char *line);

/*
 * Return a Vector of tokens from the given line.
 */
struct Vector *scan_tokens(struct Scanner *s, char *line);
