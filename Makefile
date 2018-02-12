CC=gcc
CFLAGS=-c
LDFLAGS=
SOURCES=src/main.c src/runcmd.c src/parser.c src/prochelp.c src/builtins.c src/vars.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ush

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	@echo "[ LD ]  " $(OBJECTS) " -> " $(EXECUTABLE)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	@echo "[ CC ]  " $< " -> " $@
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@echo "[ CL ]  " $(OBJECTS)
	@rm -f $(OBJECTS)
	@echo "[ CL ]  " $(EXECUTABLE)
	@rm -f $(EXECUTABLE)
