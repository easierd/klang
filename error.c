#include <stdio.h>

#include "error.h"


bool has_error = false;

void error_report(int line, char *msg) {
    fprintf(stderr, "[line %d] ERROR: %s\n", line, msg);
    has_error = true;
}
