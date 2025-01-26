objects = fileman.o utils.h xovi.o

CC += -D_GNU_SOURCE
VPATH = src

fileman : $(objects)
	${CC} ${CFLAGS} -shared -o fileman.so $(objects)


xovi.c xovi.h	&: fileman.xovi
	python3 ${XOVI_REPO}/util/xovigen.py -o xovi.c -H xovi.h fileman.xovi

fileman.o	: xovi.h utlist.h fileman.h ../util.h
utils.o		: xovi.h fileman.h
