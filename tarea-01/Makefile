SRCDIR=src
INCDIR=include
TESTDIR=test

TESTFLAGS=-g3 -O3 \
	-fsanitize=address \
	-fsanitize=undefined \
	-fno-sanitize-recover=all \
	-fsanitize=float-divide-by-zero \
	-fsanitize=float-cast-overflow

CC=gcc
CFLAGS=-std=c18 -Wall -Wpedantic -Werror -Wextra -I$(INCDIR)/

all: test

test: $(TESTDIR)/test_sorting.o
	@./$<

$(TESTDIR)/test_sorting.o: $(TESTDIR)/test_sorting.c $(SRCDIR)/sorting_methods.o
	@echo "Compilando casos de prueba..."
	@$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compilando $<"
	@$(CC) $(CFLAGS) $(TESTFLAGS) -c -o $@ $<

$(SRCDIR)/sorting_methods.o: $(INCDIR)/sorting_methods.h

clean:
	@rm -rf test/*.o src/*.o
