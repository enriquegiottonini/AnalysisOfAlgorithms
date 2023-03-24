SRCDIR=src
INCDIR=include
TESTDIR=test
OBJDIR=obj

TESTFLAGS=-g3 -O3 \
	-fsanitize=address \
	-fsanitize=undefined \
	-fno-sanitize-recover=all \
	-fsanitize=float-divide-by-zero \
	-fsanitize=float-cast-overflow

CC=gcc
CFLAGS=-std=c18 -Wall -Wpedantic -Werror -Wextra -I $(INCDIR) -g3 -O3

# build the project compiling all the source files from the src folder
build: $(SRCDIR)/*.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/main $^

# test the project compiling all the source files from the test folder
tests: $(TESTDIR)/*.c
	$(CC) $(CFLAGS) $(TESTFLAGS) -o $(OBJDIR)/test $^
	./$(OBJDIR)/test

# run the project
run: build
	./$(OBJDIR)/main

# clean the project
clean:
	rm -rf $(OBJDIR)/*


# TODO- FIX MAKE TESTS BECAUSE IS NOT WORKING