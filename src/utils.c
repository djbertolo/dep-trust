#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Static Constants

static const unsigned int max_line_length = 256;

char **read_makefile(const char *filepath, int *line_count)
{
	FILE *p_makefile = fopen(filepath, "r");
	if (p_makefile == NULL)
	{
		perror("Error opening Makefile");
		return NULL;
	}

	// Allocate initial memory for an array of char pointers
	unsigned int capacity = 100; // Initial capacity
	char **content = malloc(capacity * sizeof(char *));
	if (content == NULL)
	{
		perror("Failed to allocate memory for content");
		fclose(p_makefile);
		return NULL;
	}

	char buffer[max_line_length];
	unsigned int index = 0;
	while (fgets(buffer, max_line_length, p_makefile) != NULL)
	{
		if (index >= capacity)
		{
			// Double the capacity if we run out of space
			capacity *= 2;
			char **new_content = realloc(content, capacity * sizeof(char *));
			if (new_content == NULL)
			{
				perror("Failed to reallocate memory");
				free_makefile(content, index);
				fclose(p_makefile);
				return NULL;
			}
			content = new_content;
		}

		content[index] = strdup(buffer);
		if (content[index] == NULL)
		{
			perror("Failed to allocate memory for line");
			free_makefile(content, index);
			fclose(p_makefile);
			return NULL;
		}
		index++;
	}

	fclose(p_makefile);
	*line_count = index;
	return content;
}

void free_makefile(char **makefile_content, unsigned int length)
{
	if (makefile_content == NULL)
		return;
	for (unsigned int i = 0; i < length; i++)
	{
		free(makefile_content[i]);
	}
	free(makefile_content);
}