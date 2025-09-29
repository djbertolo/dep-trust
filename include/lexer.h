#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

/*
	ENUMS & STRUCTS
*/

enum TokenType
{
	TOKEN_IDENTIFIER,
	TOKEN_COLON,
	TOKEN_EQUALS,
	TOKEN_PLUS_EQUALS,
	TOKEN_NEWLINE,
	TOKEN_TAB,
	TOKEN_VARIABLE,
	TOKEN_EOF
};

struct Token
{
	enum TokenType type;
	char *value;
};

struct TokenNode
{
	struct Token *value;
	struct TokenNode *next;
};

/*
	FUNCTION PROTOTYPES
*/

/**
 * @brief Tokenizes the content of a makefile/
 * @param makefile_content An array of strings, where each string is a line from the makefile.
 * @param line_count The number of lines in the makefile_content array
 * @return A pointer to the head of the linked list of tokens
 */
struct TokenNode *tokenize_makefile(char *makefile_content[], unsigned int line_count);

/**
 * @brief Prints all tokens in the list for debugging purposes.
 * @param head a Pointer to the head of the token list.
 */
void print_tokens(struct TokenNode *head);

/**
 * @brief Frees all memory allocated for the token list.
 * @param head A pointer to the head of the token list.
 */
void free_tokens(struct TokenNode *head);

#endif