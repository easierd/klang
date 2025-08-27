#pragma once


enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
};


struct Token {
    enum TokenType type;
    char *lexeme;
};


/*
 * Return a new Token of the given type, with the given lexeme
 * The lexeme must be a malloc-allocated pointer.
 */
struct Token *token_new(enum TokenType type, char *lexeme);


/*
 * Free the token pointed by the given pointer
 * It's responsibility of the caller to guarantee that
 * the pointer points to a proper Token.
 *
 * This function frees the pointer to the lexeme.
 */
void token_free(void *);


/*
 * print a representation of the given token
 * on stdout
 */
void token_print(struct Token *token);

