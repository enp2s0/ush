CC=gcc
CFLAGS+=-MD -MP -g
LDFLAGS=
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
DEPS=$(SOURCES:.c=.d)
BINDIR=bin
EXECUTABLE=$(BINDIR)/ush-debug
STRIPBIN=$(BINDIR)/ush-bin
VGCORE=$(wildcard vgcore.*)

BUILDFILES=$(OBJECTS) $(DEPS) $(EXECUTABLE) $(STRIPBIN) $(BINDIR) $(VGCORE)
.PHONY=all

all: $(SOURCES) $(BINDIR) $(EXECUTABLE)
strip: $(SOURCES) $(BINDIR) $(EXECUTABLE) $(STRIPBIN)

run: $(SOURCES) $(BINDIR) $(EXECUTABLE) $(STRIPBIN)
	@$(EXECUTABLE)

debug: $(SOURCES) $(BINDIR) $(EXECUTABLE)
	gdb $(EXECUTABLE)

valgrind: $(SOURCES) $(BINDIR) $(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	@echo "[ LD ]  " $(OBJECTS) " -> " $(EXECUTABLE)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(STRIPBIN): $(EXECUTABLE)
	@echo "[STRP]  " $(EXECUTABLE) " -> " $(STRIPBIN)
	@cp $(EXECUTABLE) $(STRIPBIN)
	@strip $(STRIPBIN)

$(BINDIR):
	@echo "[MKDR]  " $(BINDIR) 
	@mkdir $(BINDIR)
	
.c.o:
	@echo "[ CC ]  " $< " -> " $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@for FILE in $(BUILDFILES); do \
		echo "[ RM ]  " $$FILE; \
		rm -rf $$FILE; \
	done

-include $(DEPS)
