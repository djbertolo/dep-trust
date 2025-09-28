#
# Example Makefile for testing
#

# Compiler and flags
CC = gcc
CFLAGS += -Wall -Wextra -std=c99
LDFLAGS = -lm

# Project files
# Use a variable to list all source files.
SRCS = main.c logger.c utils.c

# Automatically generate object file names from source files
# This replaces the .c extension with .o
OBJS = $(SRCS:.c=.o)

# The name of the final executable
EXEC = my_program

# --- Targets ---

# The default target, which is the first one in the file.
# .PHONY declares 'all' as a target that doesn't represent a file.
.PHONY: all
all: $(EXEC)

# Rule to link the final executable.
# $@ is an automatic variable for the target name (my_program)
# $^ is an automatic variable for all prerequisites (the .o files)
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Linking complete."

# A pattern rule to compile .c files into .o files.
# This single rule handles main.c -> main.o, logger.c -> logger.o, etc.
# $< is an automatic variable for the first prerequisite (the .c file)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# --- Housekeeping Targets ---

# Target to remove all generated files.
.PHONY: clean
clean:
	@echo "Cleaning up project files..."
	rm -f $(OBJS) $(EXEC)

# Target to force a complete rebuild.
.PHONY: rebuild
rebuild: clean all