objects = main.o hash.o indexfile.o rccload.o xovi.o libqmldiff.a

CXX += -I ${SDKTARGETSYSROOT}/usr/include/QtCore/
CC += -D_GNU_SOURCE -fPIC
VPATH = src
name = qt-resource-rebuilder

fileman : $(objects)
	${CC} ${CFLAGS} -shared -o $(name).so $(objects)

libqmldiff.a	:
	cd qmldiff && cargo build --target aarch64-unknown-linux-gnu --release --lib
	cp qmldiff/target/aarch64-unknown-linux-gnu/release/libqmldiff.a .

xovi.c xovi.h	&: $(name).xovi
	python3 ${XOVI_REPO}/util/xovigen.py -o xovi.c -H xovi.h $(name).xovi

main.o		: xovi.h types.h indexfile.h qmldiff.h ../util.h
hash.o		: hash.h
indexfile.o	: xovi.h rccload.h ../util.h ../system.h


.PHONY  : clean
clean :
	rm -f $(name).so $(objects) xovi.c xovi.h
