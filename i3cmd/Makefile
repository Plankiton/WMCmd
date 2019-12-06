# i3cmd - dynamic menu
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c i3cmd.c  util.c
OBJ = $(SRC:.c=.o)

all: options i3cmd

options:
	@echo i3cmd build options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "CC       = $(CC)"

.c.o:
	$(CC) -c $(CFLAGS) $<

config.h:
	cp config.def.h $@

$(OBJ): arg.h config.h config.mk drw.h

i3cmd: i3cmd.o drw.o util.o
	$(CC) -o $@ i3cmd.o drw.o util.o $(LDFLAGS)

clean:
	rm -f i3cmd $(OBJ) i3cmd-$(VERSION).tar.gz
