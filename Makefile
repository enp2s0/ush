CC=gcc
CFLAGS=-MD -MP -c
LDFLAGS=
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
DEPS=$(SOURCES:.c=.d)
EXECUTABLE=ush

BUILDFILES=$(OBJECTS) $(DEPS) $(EXECUTABLE)
.PHONY=all

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

-include $(DEPS)
