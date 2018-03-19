CC=gcc
CFLAGS=-c
LDFLAGS=
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ush

BUILDFILES=$(OBJECTS) $(EXECUTABLE)
.PHONY=all rebuild

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	@echo "[ LD ]  " $(OBJECTS) " -> " $(EXECUTABLE)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	@echo "[ CC ]  " $< " -> " $@
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@for FILE in $(BUILDFILES); do \
		echo "[ RM ]  " $$FILE; \
		rm -rf $$FILE; \
	done
