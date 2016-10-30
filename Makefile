CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-g -lm

SOURCES=$(wildcard ./src/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=./bin/brightsouls

TESTS=$(wildcard ./test/*.c)
TESTOBJECTS=$($(TESTS:.c=.o):/test/=/src/) $(TESTS:.c=.o)
TESTEXECUTABLE=./bin/test

.PHONY: all bin test clean


all: bin test

bin: $(EXECUTABLE)

test: $(TESTEXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(TESTEXECUTABLE): $(TESTOBJECTS)
	$(CC) $(LDFLAGS) $(TESTOBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(OBJECTS)
	-rm $(EXECUTABLE)
	-rm $(TESTOBJECTS)
	-rm $(TESTEXECUTABLE)
