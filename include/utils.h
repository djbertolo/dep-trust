#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Reads the contents of a makefile into an array of strings.
 * @param filepath The path to the makefile.
 * @param line_count A pointer to an integer that will be populated with the number of lines read.
 * @return An array of dynamically allocated strings, or NULL on failure.
 */
char **read_makefile(const char *filepath, int *line_count);

/**
 * @brief Frees the memory allocated by read_makefile.
 * @param makefile_content The array of strings to free.
 * @param length The number of lines in the array.
 */
void free_makefile(char **makefile_content, unsigned int length);

#endif