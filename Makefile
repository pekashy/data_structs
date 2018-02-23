CC:= gcc
CFLAGS = -g -Wall# -g for debug, -O2 for optimise and -Wall additional messages
SOURCES = structure.c
OBJECTS = structure.o
EXECUTABLE = a.out

all: build
build: $(OBJECTS) $(EXECUTABLE) clean

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@ -MD
	-(include *.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $< -o $@

#$(EXECUTABLE): $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf *.d
