#pragma once


enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,

    COMMA, 
    DOT,
    SEMICOLON,

    MINUS,
    PLUS,
    STAR,
    SLASH
};


struct Token {
    enum TokenType type;
    char *lexeme;
};


/*
 * Return a new Token of the given type, with the given lexeme
 *
 * N.B. The lexeme must be a malloc-allocated pointer.
 */
struct Token *token_new(enum TokenType type, char *lexeme);


/*
 * Free the token pointed by the given pointer.
 *
 * This function frees the pointer to the lexeme.
 *
 * N.B. It's responsibility of the caller to guarantee that
 * the pointer points to a proper Token.
 */
void token_free(void *);


/*
 * Print a representation of the given token
 * on stdout.
 */
void token_print(struct Token *token);

