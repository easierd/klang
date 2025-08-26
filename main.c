#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"


enum {
    BUF_MAX = 128,
};


void run(char *line) {
    struct Token *tokens = NULL;
    size_t n_tokens = scan_tokens(line, &tokens);
    for (size_t i = 0; i < n_tokens; i++) {
        token_print(tokens + i);
        putchar('\n');
    }

    free_tokens(tokens, n_tokens);
}


void run_script(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fseek(fp, 0, SEEK_END) == -1) {
        perror("fseek");
        exit(EXIT_FAILURE);
    }

    long flength = ftell(fp);
    if (flength == -1) {
        perror("ftell");
        exit(EXIT_FAILURE);
    }

    if (fseek(fp, 0, SEEK_SET) == -1) {
        perror("fseek");
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(flength + 1);
    if (buffer == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    long ret = fread(buffer, 1, flength, fp);
    if (ret != flength && feof(fp)) {
        perror("fread");
        exit(EXIT_FAILURE);
    }

    fclose(fp);

    buffer[flength] = 0;
    run(buffer);
    free(buffer);
}


void run_prompt() {
    char buffer[BUF_MAX];

    printf("klang> ");
    while (fgets(buffer, BUF_MAX, stdin)) {
        run(buffer);
        printf("klang> ");
    }

    putchar('\n');
}


int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "usage: klang [filename]\n");
        exit(EXIT_FAILURE);
    } else if (argc == 2) {
        run_script(*++argv);
    } else {
        run_prompt();
    }
}
