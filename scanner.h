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
 * scan the tokens from the given line and store 
 * the address of the list containing the tokens 
 * into *tokens.
 *
 * return the length of the tokens scanned.
 */
size_t scan_tokens(char *line, struct Token **tokens);


/*
 * free the list of tokens
 */
void free_tokens(struct Token *tokens, size_t len);


/*
 * print a representation of the given token
 * on stdout
 */
void token_print(struct Token *token);
