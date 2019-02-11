#!/usr/bin/make -f
SHELL = /bin/sh
CFLAGS = `pkg-config --cflags guile-2.0`
LIBS = `pkg-config --libs guile-2.0`
EXE = tortoise.exe
OBJECT = tortoise.o
SOURCE = tortoise.c

$(EXE): $(OBJECT)
	gcc $(OBJECT) ${LIBS} -o $(EXE)

$(OBJECT): $(SOURCE)
	gcc -c $(CFLAGS) $(SOURCE)

.PHONY: backup indent run clean
backup:
	cp -f $(SOURCE) $(SOURCE).backup

indent:
	cp -f $(SOURCE) $(SOURCE).preindent
	indent $(SOURCE)

run: $(EXE)
	./$(EXE)

clean:
	rm $(EXE) $(OBJECT) 
