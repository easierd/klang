#pragma once
#include <stdio.h>

void error(int line, char *msg) {
    fprintf(stderr, "[line %d] ERROR: %s\n", line, msg);
}
