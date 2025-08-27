#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "scanner.h"


char *lex_malloc(char *line, size_t len, size_t pos) {
    char *lex = malloc(len + 1);
    if (lex == NULL) {
        perror("scan_tokens");
        return NULL;
    }
    strncpy(lex, line + pos, len);
    lex[len] = 0;

    return lex;
}


bool append_token(struct Vector *token_list, enum TokenType type, size_t lex_len, char *line, int i) {
    char *lex = lex_malloc(line, lex_len, i);
    if (lex == NULL) {
        return false;
    }
    struct Token *t = token_new(type, lex);
    if (t == NULL) {
        return false;
    }

    return vector_push_back(token_list, t);
}


struct Vector *scan_tokens(char *line) {
    struct Vector *token_list = vector_new();
    if (token_list == NULL) {
        return NULL;
    }
    for (int i = 0; line[i] != 0; i++) {
        switch(line[i]) {
            case '(':
                if (!append_token(token_list, LEFT_PAREN, 1, line, i)) {
                    vector_free(token_list, token_free);
                    return NULL;
                }
                break;
            case ')':
                if (!append_token(token_list, RIGHT_PAREN, 1, line, i)) {
                    vector_free(token_list, token_free);
                    return NULL;
                }
                break;
        }
    }

    return token_list;
}
