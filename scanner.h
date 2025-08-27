#pragma once

#include "vector.h"

/*
 * Return a Vector of tokens from the given line.
 */
struct Vector *scan_tokens(char *line);
