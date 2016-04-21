CC     = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 gmodule-2.0`
LIBS   = `pkg-config --libs gtk+-3.0 gmodule-2.0`
DEBUG  = -Wall -g
RDYN   = -export-dynamic

OBJECTS = glc-gui.o glc-config.o callbacks.o

.PHONY: clean

all: glc-gui

glc-gui: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(DEBUG) $(LIBS) $(RDYN)

glc-gui.o: glc-gui.c support.h glc-config.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@ $(RDYN)

glc-config.o: glc-config.c support.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@ $(RDYN)

callbacks.o: callbacks.c support.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@ $(RDYN)

clean:
	rm -f *.o glc-gui ~/.glc-gui
