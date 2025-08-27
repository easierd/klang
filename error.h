/*
 * Error utilites for the KLANG interpreter
 */

#pragma once

#include <stdbool.h>

/*
 * Global variable used to signal errors among the 
 * components of the interpreter.
 */
extern bool klang_has_error;

/*
 * Report an error message, occurred at the given line, on stderr.
 */
void klang_error_report(int line, char *msg);


/* 
 * Reset the global error flag.
 */
void klang_error_reset(void);
