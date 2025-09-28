#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*
	ENUMS
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

/*
	STRUCTS
*/

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
	GLOBALS
*/

const unsigned int max_rules = 15;
const unsigned int max_commands = 10;
const unsigned int max_line_length = 256;

const char makefile_directory[] = "Makefile";

// Initialize global pointers to NULL
struct TokenNode *token_list_head = NULL;
struct TokenNode *token_list_tail = NULL;

/*
	FUNCTIONS
*/

int read_makefile(char *makefile_content[]); // returns number of lines read
void add_token(enum TokenType token_type, const char *value);
void convert_token(char *token);
void tokenize_line(char *line);
void tokenize_makefile(char *makefile_content[], unsigned int line_count);
void print_tokens();
void free_makefile(char *makefile_content[], unsigned int length);
void free_tokens();

int main()
{
	// Read content from makefile
	unsigned int makefile_length = max_rules * (1 + max_commands);
	char *makefile_content[makefile_length];
	int lines = read_makefile(makefile_content);
	if (lines < 0)
	{
		perror("Error reading makefile content");
		return EXIT_FAILURE;
	}

	// Tokenize contents of makefile
	tokenize_makefile(makefile_content, lines);

	// Print tokens
	print_tokens();

	// Free all allocated memory
	free_tokens();
	free_makefile(makefile_content, lines);

	return EXIT_SUCCESS;
}

int read_makefile(char *makefile_content[])
{
	// Open makefile to read contents
	FILE *p_makefile = fopen(makefile_directory, "r");
	if (p_makefile == NULL)
	{
		perror("Error opening Makefile");
		return -1;
	}

	char buffer[max_line_length];
	unsigned int index = 0;

	while (fgets(buffer, max_line_length, p_makefile) != NULL)
	{
		makefile_content[index] = strdup(buffer);
		if (makefile_content[index] == NULL)
		{
			perror("Failed to allocate memory for line");
			free_makefile(makefile_content, index);
			fclose(p_makefile);
			return -1;
		}
		index++;
	}

	fclose(p_makefile);
	return index;
}

void free_makefile(char *makefile_content[], unsigned int length)
{
	for (unsigned int i = 0; i < length; i++)
	{
		free(makefile_content[i]);
	}
}

void add_token(enum TokenType token_type, const char *value)
{
	struct Token *new_token = malloc(sizeof(struct Token));
	if (new_token == NULL)
	{
		perror("Error: Memory allocation for token failed!");
		return;
	}

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
		// Add as first node in the list
		token_list_head = new_token_node;
		token_list_tail = new_token_node;
	}
	else
	{
		// Add to end of list and increment tail pointer
		token_list_tail->next = new_token_node;
		token_list_tail = token_list_tail->next;
	}
}

void convert_token(char *token)
{
	// Skip empty strings
	if (strlen(token) == 0)
	{
		return;
	}

	enum TokenType token_type;
	if (strcmp(token, ":") == 0)
	{
		token_type = TOKEN_COLON;
	}
	else if (strcmp(token, "=") == 0)
	{
		token_type = TOKEN_EQUALS;
	}
	else if (strcmp(token, "+=") == 0)
	{
		token_type = TOKEN_PLUS_EQUALS;
	}
	else if (strcmp(token, "\t") == 0)
	{
		token_type = TOKEN_TAB;
	}
	else if (strncmp(token, "$(", 2) == 0)
	{
		token_type = TOKEN_VARIABLE;
	}
	else
	{
		token_type = TOKEN_IDENTIFIER;
	}

	add_token(token_type, token);
}

void tokenize_line(char *line)
{
	// Remove \n character from end of line
	line[strcspn(line, "\n")] = 0;

	// Remove line after #
	char *p_comment_start = strchr(line, '#');
	if (p_comment_start != NULL)
	{
		// Terminate string where comment starts
		*p_comment_start = '\0';
	}

	// Handle tab for command lines
	if (line[0] == '\t')
	{
		add_token(TOKEN_TAB, "\t");
		// Pass remaining line as one token
		convert_token(line + 1);
		return;
	}

	char *token = strtok(line, " ");
	while (token != NULL)
	{
		convert_token(token);
		token = strtok(NULL, " ");
	}
}

void tokenize_makefile(char *makefile_content[], unsigned int line_count)
{
	for (unsigned int i = 0; i < line_count; i++)
	{
		tokenize_line(makefile_content[i]);
		add_token(TOKEN_NEWLINE, "\n");
	}
	add_token(TOKEN_EOF, "EOF");
}

void free_tokens()
{
	struct TokenNode *current = token_list_head;
	struct TokenNode *next;
	while (current != NULL)
	{
		next = current->next;
		free(current->value->value);
		free(current->value);
		free(current);
		current = next;
	}
	token_list_head = NULL;
	token_list_tail = NULL;
}

void print_tokens()
{
	struct TokenNode *current = token_list_head;
	while (current != NULL)
	{
		printf("Type: %d, Value: '%s'\n", current->value->type, current->value->value);
		current = current->next;
	}
}