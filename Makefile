CC:= gcc
CFLAGS = -g -Wall# -g for debug, -O2 for optimise and -Wall additional messages
SOURCES = structure.c test.c
OBJECTS = structure.o test.o
EXECUTABLE = run

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $< -MD

clean:
	rm -rf *.d

-include *.d