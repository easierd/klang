#include <stdlib.h>
#include <stdio.h>

#include "token.h"


struct Token *token_new(enum TokenType type, char *lexeme) {
    struct Token *t = malloc(sizeof(struct Token));
    if (t == NULL) {
        perror("token_new");
        return NULL;
    }

    t->type = type;
    t->lexeme = lexeme;

    return t;
}


void token_free(void *t) {
    struct Token *tok = (struct Token*) t;
    free(tok->lexeme);
    free(tok);
}


const char *token_type_name(enum TokenType type) {
    static const char *name[] = {
        "LEFT_PAREN",
        "RIGHT_PAREN",
        "LEFT_BRACE",
        "RIGHT_BRACE",
        "COMMA",
        "DOT",
        "SEMICOLON",
        "MINUS",
        "PLUS",
        "STAR",
        "SLASH"
    };

    return name[type];
}


void token_print(struct Token *token) {
    printf("%s %s", token_type_name(token->type), token->lexeme);
}

