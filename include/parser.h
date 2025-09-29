#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

/*
	ENUMS & STRUCTS
*/

// Represents a depedency (a file or another target)
struct DependencyNode
{
	char *name;
	struct DependencyNode *next;
};

// Represents a command associated with a rule
struct CommandNode
{
	char *command;
	struct CommandNode *next;
};

// Represents a target (e.g., an object file or an executable)
struct TargetNode
{
	char *name;
	struct DependencyNode *dependencies;
	struct CommandNode *commands;
	struct TargetNode *next; // Link together all targets
};

// Represents entirety of dependency graph
struct DependencyGraph
{
	struct TargetNode *targets;
};

/*
	FUNCTION PROTOTYPES
*/

/**
 * @brief Parses tokenized makefile_content into a graph
 * @param tokens A linked list of token-nodes
 * @return A pointer to root of a Depedency graph
 */
struct DependencyGraph *parse_tokens(struct TokenNode *tokens);

/**
 * @brief Frees memory allocated to Dependency graph
 * @param graph A pointer to a dependency graph to free
 */
void free_dependency_graph(struct DependencyGraph *graph);

#endif