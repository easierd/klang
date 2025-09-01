#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "scanner.h"
#include "error.h"


struct Scanner *scanner_new(char *line) {
    struct Scanner *s = malloc(sizeof(struct Scanner));
    if (s == NULL) {
        perror("scanner_new");
        return NULL;
    }

    s->line = line;
    s->start = 0;
    s->current = 0;

    return s;
}


void scanner_delete(struct Scanner *scanner) {
    free(scanner);
}


char *lex_malloc(struct Scanner *s, size_t len) {
    char *lex = malloc(len + 1);
    if (lex == NULL) {
        perror("scan_tokens");
        return NULL;
    }
    strncpy(lex, s->line + s->start, len);
    lex[len] = 0;

    return lex;
}


bool append_token(struct Scanner *s, struct Vector *token_list, enum TokenType type) {
    char *lex = lex_malloc(s, s->current - s->start);
    if (lex == NULL) {
        return false;
    }
    struct Token *t = token_new(type, lex);
    if (t == NULL) {
        return false;
    }

    return vector_push_back(token_list, t);
}


struct Vector *scan_tokens(struct Scanner *s) {
    struct Vector *token_list = vector_new();
    if (token_list == NULL) {
        return NULL;
    }

    while (s->line[s->current]){
        s->start = s->current;
        char c = s->line[s->current++];

        switch(c) {
            case '(':
                if (!append_token(s, token_list, LEFT_PAREN)) {
                    goto cleanup;
                }
                break;
            case ')':
                if (!append_token(s, token_list, RIGHT_PAREN)) {
                    goto cleanup;
                }
                break;
            case '{':
                if (!append_token(s, token_list, LEFT_BRACE)) {
                    goto cleanup;
                }
                break;
            case '}':
                if (!append_token(s, token_list, RIGHT_BRACE)) {
                    goto cleanup;
                }
                break;
            case ',':
                if (!append_token(s, token_list, COMMA)) {
                    goto cleanup;
                }
                break;
            case '.':
                if (!append_token(s, token_list, DOT)) {
                    goto cleanup;
                }
                break;
            case ';':
                if (!append_token(s, token_list, SEMICOLON)) {
                    goto cleanup;
                }
                break;
            case '-':
                if (!append_token(s, token_list, MINUS)) {
                    goto cleanup;
                }
                break;
            case '+':
                if (!append_token(s, token_list, PLUS)) {
                    goto cleanup;
                }
                break;
            case '*':
                if (!append_token(s, token_list, STAR)) {
                    goto cleanup;
                }
                break;
            case '!':
                if (s->line[s->current] == '=') {
                    s->current++;
                    if (!append_token(s, token_list, BANG_EQUAL)) {
                        goto cleanup;
                    }
                    break;
                }

                if (!append_token(s, token_list, BANG)) {
                    goto cleanup;
                }
                break;
            case '=':
                if (s->line[s->current] == '=') {
                    s->current++;
                    if (!append_token(s, token_list, EQUAL_EQUAL)) {
                        goto cleanup;
                    }
                } else {
                    if (!append_token(s, token_list, EQUAL)) {
                        goto cleanup;
                    }
                }
                break;
            default:
                if (isspace(c)) {
                    break;
                }

                char err[32];
                snprintf(err, 32, "Unexpected character %c", c); 
                err[31] = 0;
                klang_error_report(0, err);
        }
    }

    return token_list;

cleanup:
    vector_delete(token_list, token_delete);
    return NULL;
}
