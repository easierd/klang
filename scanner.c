#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


bool append_token(struct Token token_list[], size_t *pos, enum TokenType type, size_t lex_len, char *line, int i) {
    token_list[*pos].type = type;
    char *lex = lex_malloc(line, lex_len, i);
    if (lex == NULL) {
        return false;
    }
    token_list[*pos].lexeme = lex;
    (*pos)++;

    return true;
}


size_t scan_tokens(char *line, struct Token **tokens) {
    struct Token *token_list = malloc(sizeof(struct Token) * 16);
    if (token_list == NULL) {
        perror("scan_tokens");
        return 0;
    }

    size_t k = 0;

    for (int i = 0; line[i] != 0; i++) {
        switch(line[i]) {
            case '(':
                if (!append_token(token_list, &k, LEFT_PAREN, 1, line, i)) {
                    free(token_list);
                    return 0;
                }
                break;

            case ')':
                if (!append_token(token_list, &k, RIGHT_PAREN, 1, line, i)) {
                    free(token_list);
                    return 0;
                }
                break;
        }
    }

    *tokens = token_list;
    return k;
}


void free_tokens(struct Token tokens[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        free((tokens + i)->lexeme);
    }
    free(tokens);
}


const char *token_type_name(enum TokenType type) {
    static const char *name[] = {
        "LEFT_PAREN",
        "RIGHT_PAREN",
    };

    return name[type];
}


void token_print(struct Token *token) {
    printf("%s %s", token_type_name(token->type), token->lexeme);
}
