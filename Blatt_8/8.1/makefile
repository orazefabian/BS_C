CC = gcc
# -g    adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
CFLAGS = -Wall -g -pthread

EXECUTABLE = main

# $(wildcard pattern…) - This string, used anywhere in a makefile, is replaced by a space-separated list of names of existing files that match one of the given file name patterns.
SOURCES = $(wildcard *.c) # get a list of all the C source files in a directory
HEADERS = $(wildcard *.h) # get a list of all the C header files in a directory
# $(patsubst pattern,replacement,text) - Finds whitespace-separated words in text that match pattern and replaces them with replacement.
# $(var:pattern=replacement) is equivalent to $(patsubst pattern,replacement,$(var))
OBJECTS = $(SOURCES:.c=.o) # replaces all .c in src variable with .o


# A phony target is one that is not really the name of a file; rather it is just a name for a recipe to be executed when you make an explicit request. There are two reasons to use a phony target: to avoid a conflict with a file of the same name, and to improve performance. 
.PHONY: all
all: $(EXECUTABLE)
	@echo -e "\nSource files: $(SOURCES)\nExecutable: '$(EXECUTABLE)' has been compiled..\n"

# $< - The name of the first prerequisite.
# %.o and %.c is like a regex that matches *.o and *.c, so every file with ending .o or .c
.PHONY: $(SOURCES) # Forces all files to be compiled on each execution!
%.o: %.c 
	$(CC) $(CFLAGS) -c $<

# $@ - The file name of the target of the rule.
# $^ - The names of all the prerequisites, with spaces between them.
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# $(RM) := rm -f
.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS) 