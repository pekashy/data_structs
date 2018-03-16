CC:= gcc
CFLAGS = -g -fprofile-arcs -ftest-coverage -Wall# -g for debug, -O2 for optimise and -Wall additional messages
LFLAGS = --coverage
SOURCES = structure.c test.c
OBJECTS = structure.o test.o
EXECUTABLE = run
.PHONY: clean

all: build link clean

build: $(SOURCES)

link: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $(OBJECTS)

$(SOURCES):
	$(CC) $(CFLAGS) -o $@ -c $< -MD

clean:
	rm -rf *.d *.o

-include *.d