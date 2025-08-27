#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "scanner.h"


static char *scan_line;
static int current = 0;
static int start = 0;


char *lex_malloc(size_t len) {
    char *lex = malloc(len + 1);
    if (lex == NULL) {
        perror("scan_tokens");
        return NULL;
    }
    strncpy(lex, scan_line + start, len);
    lex[len] = 0;

    return lex;
}


bool append_token(struct Vector *token_list, enum TokenType type) {
    char *lex = lex_malloc(current - start);
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
    scan_line = line;

    struct Vector *token_list = vector_new();
    if (token_list == NULL) {
        return NULL;
    }

    while (scan_line[current]){
        start = current;
        char c = scan_line[current++];
        switch(c) {
            case '(':
                if (!append_token(token_list, LEFT_PAREN)) {
                    vector_free(token_list, token_free);
                    return NULL;
                }
                break;
            case ')':
                if (!append_token(token_list, RIGHT_PAREN)) {
                    vector_free(token_list, token_free);
                    return NULL;
                }
                break;
            case '{':
                if (!append_token(token_list, LEFT_BRACE)) {
                    vector_free(token_list, token_free);
                    return NULL;
                }
                break;
            case '}':
                if (!append_token(token_list, RIGHT_BRACE)) {
                    vector_free(token_list, token_free);
                    return NULL;
                }
                break;
        }
    }

    return token_list;
}
