#pragma once

#include "vector.h"

/*
 * scan the tokens from the given line and store 
 * the address of the list containing the tokens 
 * into *tokens.
 *
 * return the length of the tokens scanned.
 */
struct Vector *scan_tokens(char *line);
