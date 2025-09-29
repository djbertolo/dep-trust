#include <stdio.h>
#include <string.h>
#include "parser.h"

static struct TokenNode *current_token = NULL; // Static pointer to current token being processed
static struct TokenNode *next_token = NULL;	   // Static pointer to next token to be processed

/*
	PRIVATE HELPER FUNCTIONS
*/

/**
 * @brief Gets current token and increments pointer
 * @returns A pointer to current_token prior to update
 */
static struct Token *pop_current_token()
{
	if (current_token == NULL)
	{
		return NULL;
	}

	struct Token *token = current_token->value;
	current_token = current_token->next;
	next_token = current_token->next;
	return token;
}

/**
 * @brief Gets current token and pointer
 * @returns A pointer to current_token
 */
static struct Token *get_current_token()
{
	if (current_token == NULL)
	{
		return NULL;
	}

	struct Token *token = current_token->value;
	return token;
}

/**
 * @brief Gets next token and pointer
 * @returns A pointer to next_token
 */
static struct Token *get_next_token()
{
	if (next_token == NULL)
	{
		return NULL;
	}

	struct Token *token = next_token->value;
	return token;
}

/**
 * @brief Parses dependencies list for rule
 * @param target Target-node to add dependencies
 */
static void parse_dependencies_list(struct TargetNode *target)
{
	// Loop and collect all dependencies
	struct DependencyNode *last_dependency = target->dependencies;
	while (get_current_token()->type == TOKEN_IDENTIFIER)
	{
		struct DependencyNode *new_dependency = calloc(1, sizeof(struct DependencyNode));
		new_dependency->name = strdup(pop_current_token()->value);
		new_dependency->next = NULL;

		// Add new_dependency to dependency list
		if (target->dependencies == NULL)
		{
			target->dependencies = new_dependency;
			last_dependency = target->dependencies;
		}
		else
		{
			last_dependency->next = new_dependency;
			last_dependency = last_dependency->next;
		}
	}
}

/**
 * @brief Parses commands list for rule
 * @param target Target-node to add commands
 */
static void parse_commands_list(struct TargetNode *target)
{
	// Check for command lines after rule definition
	struct CommandNode *last_command = target->commands;
	while (get_current_token()->type == TOKEN_TAB)
	{
		// Consume TOKEN_TAB
		pop_current_token();

		struct CommandNode *new_command = calloc(1, sizeof(struct CommandNode));
		new_command->command = strdup(pop_current_token()->value);
		new_command->next = NULL;

		// Add command to command list
		if (target->commands == NULL)
		{
			target->commands = new_command;
			last_command = target->commands;
		}
		else
		{
			last_command->next = new_command;
			last_command = last_command->next;
		}

		// Consume TOKEN_NEWLINE
		pop_current_token();
	}
}

/**
 * @brief Parses current_token as a rule
 * @returns A pointer to a target-node
 */
static struct TargetNode *parse_rule()
{
	struct TargetNode *new_target = calloc(1, sizeof(struct TargetNode));

	// First token must be target's name
	new_target->name = strdup(pop_current_token()->value);

	// Second token must be a colon
	pop_current_token();

	// Collect all dependencies
	parse_dependencies_list(new_target);

	// Pop the TOKEN_NEWLINE
	pop_current_token();

	// Collect all commands
	parse_commands_list(new_target);

	return new_target;
}

/**
 * @brief Parses current_token
 * @returns A pointer to a target-node
 */
static struct TargetNode *parse_current_token()
{
	enum TokenType current_token_type = get_current_token()->type;
	enum TokenType next_token_type = get_next_token()->type;
	if (current_token_type == TOKEN_IDENTIFIER)
	{
		// Check if token is a rule
		if (next_token_type == TOKEN_COLON)
		{
			// Parse token as rule
			struct TargetNode *new_target = parse_rule();
			return new_target;
		}
	}
	return NULL;
}

/**
 * @brief Clears remaining tokens on current line
 */
void clear_current_line()
{
	while (get_current_token() != NULL && get_current_token()->type != TOKEN_NEWLINE)
	{
		pop_current_token();
	}
}

/*
	PUBLIC FUNCTIONS
*/
struct DependencyGraph *parse_tokens(struct TokenNode *tokens)
{
	// Update current_token to start of token list
	current_token = tokens;
	next_token = current_token->next;

	// Initialize new Dependency Graph
	struct DependencyGraph *graph = calloc(1, sizeof(struct DependencyGraph));

	// Keep tail of target list
	struct TargetNode *last_target = graph->targets;

	while (get_current_token() != NULL && get_current_token()->type != TOKEN_EOF)
	{
		struct TargetNode *new_target = parse_current_token();

		if (new_target == NULL)
		{
			clear_current_line();

			// Pop TOKEN_NEWLINE
			pop_current_token();

			continue;
		}

		if (graph->targets == NULL)
		{
			graph->targets = new_target;
			last_target = graph->targets;
		}
		else
		{
			last_target->next = new_target;
			last_target = last_target->next;
		}
	}
}