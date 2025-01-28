objects = main.o hash.o indexfile.o rccload.o xovi.o libqmldiff.a

CXX += -I ${SDKTARGETSYSROOT}/usr/include/QtCore/ -fPIC
CC += -D_GNU_SOURCE -fPIC
VPATH = src
name = qt-resource-rebuilder

fileman : $(objects)
	${CC} ${CFLAGS} -shared -o $(name).so $(objects)

libqmldiff.a	:
	cd qmldiff && cargo build --release --lib
	cp qmldiff/target/${CARGO_BUILD_TARGET}/release/libqmldiff.a .

xovi.c xovi.h	&: $(name).xovi
	python3 ${XOVI_REPO}/util/xovigen.py -o xovi.c -H xovi.h $(name).xovi

main.o		: xovi.h types.h indexfile.h qmldiff.h ../util.h
hash.o		: hash.h
indexfile.o	: xovi.h rccload.h ../util.h ../system.h


.PHONY  : clean
clean :
	rm -f $(name).so $(objects) xovi.c xovi.h
	cd qmldiff && cargo clean
