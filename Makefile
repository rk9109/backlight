CC := gcc
CFLAGS := -Wall -Os
PREFIX = /usr/local

SRC = backlight.c
OBJ = ${SRC:.c=.o}

backlight: ${OBJ}
	@echo CC -o $@
	@$(CC) -o $@ ${OBJ}

clean:
	@rm -f backlight ${OBJ}

install: backlight
	@echo installing executable to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f backlight ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/backlight
	@chmod u+s ${DESTDIR}${PREFIX}/bin/backlight

uninstall:
	@echo uninstalling executable from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/backlight
