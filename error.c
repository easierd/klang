#include <stdio.h>

#include "error.h"


bool klang_has_error = false;


void klang_error_report(int line, char *msg) {
    fprintf(stderr, "[line %d] ERROR: %s\n", line, msg);
    klang_has_error = true;
}


void klang_error_reset(void) {
    klang_has_error = false;
}
