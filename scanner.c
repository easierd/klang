#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "scanner.h"
#include "error.h"


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
    current = 0;
    start = 0;

    struct Vector *token_list = vector_new();
    if (token_list == NULL) {
        return NULL;
    }

    while (scan_line[current]){
        start = current;
        char c = scan_line[current++];

        if (isspace(c)) {
            continue;
        }

        switch(c) {
            case '(':
                if (!append_token(token_list, LEFT_PAREN)) {
                    goto cleanup;
                }
                break;
            case ')':
                if (!append_token(token_list, RIGHT_PAREN)) {
                    goto cleanup;
                }
                break;
            case '{':
                if (!append_token(token_list, LEFT_BRACE)) {
                    goto cleanup;
                }
                break;
            case '}':
                if (!append_token(token_list, RIGHT_BRACE)) {
                    goto cleanup;
                }
                break;
            case ',':
                if (!append_token(token_list, COMMA)) {
                    goto cleanup;
                }
                break;
            case '.':
                if (!append_token(token_list, DOT)) {
                    goto cleanup;
                }
                break;
            case ';':
                if (!append_token(token_list, SEMICOLON)) {
                    goto cleanup;
                }
                break;
            case '-':
                if (!append_token(token_list, MINUS)) {
                    goto cleanup;
                }
                break;
            case '+':
                if (!append_token(token_list, PLUS)) {
                    goto cleanup;
                }
                break;
            case '*':
                if (!append_token(token_list, STAR)) {
                    goto cleanup;
                }
                break;
            default:
                char err[32];
                snprintf(err, 32, "Unexpected character %c", c); 
                err[31] = 0;
                error(0, err);
        }
    }

    return token_list;

cleanup:
    vector_free(token_list, token_free);
    return NULL;
}
