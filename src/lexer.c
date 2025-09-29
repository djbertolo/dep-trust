#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

// Static global pointers, private to this file
static struct TokenNode *token_list_head = NULL;
static struct TokenNode *token_list_tail = NULL;

// --- Static Helper Function Prototypes ---
static void add_token(enum TokenType token_type, const char *value);
static void convert_token(char *token);
static void tokenize_line(char *line);

// --- Public Function Definitions (from lexer.h) ---

struct TokenNode *tokenize_makefile(char *makefile_content[], unsigned int line_count)
{
	// Ensure list is empty before starting
	if (token_list_head != NULL)
	{
		free_tokens(token_list_head);
		token_list_head = NULL;
		token_list_tail = NULL;
	}

	for (unsigned int i = 0; i < line_count; i++)
	{
		tokenize_line(makefile_content[i]);
		add_token(TOKEN_NEWLINE, "\n");
	}
	add_token(TOKEN_EOF, "EOF");

	return token_list_head;
}

void print_tokens(struct TokenNode *head)
{
	struct TokenNode *current = head;
	while (current != NULL)
	{
		printf("Type: %d, Value: '%s'\n", current->value->type, current->value->value);
		current = current->next;
	}
}

void free_tokens(struct TokenNode *head)
{
	struct TokenNode *current = head;
	struct TokenNode *next;
	while (current != NULL)
	{
		next = current->next;
		free(current->value->value);
		free(current->value);
		free(current);
		current = next;
	}
}

// --- Static Helper Function Definitions ---

static void add_token(enum TokenType token_type, const char *value)
{
	struct Token *new_token = malloc(sizeof(struct Token));
	if (new_token == NULL)
	{
		perror("Error: Memory allocation for token failed!");
		return;
	}

	new_token->type = token_type;
	new_token->value = strdup(value);
	if (new_token->value == NULL)
	{
		free(new_token);
		perror("Error: Memory allocation for token value failed!");
		return;
	}

	struct TokenNode *new_token_node = malloc(sizeof(struct TokenNode));
	if (new_token_node == NULL)
	{
		free(new_token->value);
		free(new_token);
		perror("Error: Memory allocation for token node failed!");
		return;
	}

	new_token_node->value = new_token;
	new_token_node->next = NULL;

	if (token_list_head == NULL)
	{
		token_list_head = new_token_node;
		token_list_tail = new_token_node;
	}
	else
	{
		token_list_tail->next = new_token_node;
		token_list_tail = new_token_node;
	}
}

static void convert_token(char *token)
{
	if (strlen(token) == 0)
		return;

	enum TokenType token_type;
	if (strcmp(token, ":") == 0)
		token_type = TOKEN_COLON;
	else if (strcmp(token, "=") == 0)
		token_type = TOKEN_EQUALS;
	else if (strcmp(token, "+=") == 0)
		token_type = TOKEN_PLUS_EQUALS;
	else if (strcmp(token, "\t") == 0)
		token_type = TOKEN_TAB;
	else if (strncmp(token, "$(", 2) == 0)
		token_type = TOKEN_VARIABLE;
	else
		token_type = TOKEN_IDENTIFIER;

	add_token(token_type, token);
}

static void tokenize_line(char *line)
{
	line[strcspn(line, "\n")] = 0; // Remove newline

	char *p_comment_start = strchr(line, '#');
	if (p_comment_start != NULL)
		*p_comment_start = '\0'; // Terminate at comment

	if (line[0] == '\t')
	{
		add_token(TOKEN_TAB, "\t");
		convert_token(line + 1); // Pass remaining line as one token
		return;
	}

	char *token = strtok(line, " ");
	while (token != NULL)
	{
		convert_token(token);
		token = strtok(NULL, " ");
	}
}