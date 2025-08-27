/*
 * Error utilites for the KLANG interpreter
 */

#pragma once

#include <stdbool.h>

/*
 * Global variable used to signal errors among the 
 * components of the interpreter
 */
extern bool has_error;

/*
 * Report an error message, occurred at the given line, on stderr
 */
void error_report(int line, char *msg);
