#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"

int main(int argc, char *argv[])
{
	// Handle command-line arguments
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s /path/to/Makefile\n", argv[0]);
		return EXIT_FAILURE;
	}
	const char *makefile_path = argv[1];

	// Read content from makefile using the utility function
	int lines = 0;
	char **makefile_content = read_makefile(makefile_path, &lines);
	if (makefile_content == NULL)
	{
		return EXIT_FAILURE;
	}

	// Tokenize contents of makefile using the lexer module
	struct TokenNode *tokens = tokenize_makefile(makefile_content, lines);

	// Print tokens for verification
	printf("--- Token List ---\n");
	print_tokens(tokens);

	// Free all allocated memory
	free_tokens(tokens);
	free_makefile(makefile_content, lines);

	printf("\nAnalysis complete.\n");

	return EXIT_SUCCESS;
}