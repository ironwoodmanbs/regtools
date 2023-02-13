CFLAGS= -Wall -O2 -std=c99 -c -o
all: rgset.o ava.o calculation.o rgsetpars.o common.o avapars.o list.o listdir.o avaprint.o avasql.o norm.o normpars.o avaedit.o array.o normread.o test_rgset.o
	gcc -o avasql avasql.o rgset.o ava.o list.o common.o calculation.o listdir.o -lm -lsqlite3
	gcc -o rgsetpars rgsetpars.o rgset.o common.o
	gcc -o avapars avapars.o ava.o common.o rgset.o list.o
	gcc -o avaedit avaedit.o ava.o common.o list.o
	gcc -o avaprint avaprint.o listdir.o rgset.o ava.o list.o common.o calculation.o -lm
	gcc -o normpars normpars.o norm.o common.o
	gcc -o normread normread.o norm.o common.o rgset.o
	gcc -o test_rgset test_rgset.o rgset.o common.o

calculation.o: calculation.c
	gcc $(CFLAGS) calculation.o calculation.c

rgset.o: rgset.c
	gcc $(CFLAGS) rgset.o rgset.c

ava.o: ava.c
	gcc $(CFLAGS) ava.o ava.c

rgsetpars.o: rgsetpars.c
	gcc $(CFLAGS) rgsetpars.o rgsetpars.c

common.o: common.c common.h
	gcc $(CFLAGS) common.o common.c

list.o: list.c
	gcc $(CFLAGS) list.o list.c

avapars.o: avapars.c
	gcc $(CFLAGS) avapars.o avapars.c

avaedit.o: avaedit.c
	gcc $(CFLAGS) avaedit.o avaedit.c

listdir.o: listdir.c
	gcc $(CFLAGS) listdir.o listdir.c

avaprint.o: avaprint.c
	gcc $(CFLAGS) avaprint.o avaprint.c

avasql.o: avasql.c
	gcc -std=c99 -Wall -c -o avasql.o avasql.c

norm.o: norm.c
	gcc $(CFLAGS) norm.o norm.c

normpars.o: normpars.c
	gcc $(CFLAGS) normpars.o normpars.c

normread.o: normread.c
	gcc $(CFLAGS) normread.o normread.c

array.o: array.c
	gcc $(CFLAGS) array.o array.c

test_rgset.o: test_rgset.c
	gcc $(CFLAGS) test_rgset.o test_rgset.c


install:
	install ./avapars /usr/local/bin
	install ./rgsetpars /usr/local/bin
	install ./avasql /usr/local/bin
	install ./avaprint /usr/local/bin
	install ./normpars /usr/local/bin
	install ./sqlc /usr/local/bin
	

clear:
	rm *.o avasql rgsetpars avapars avaprint normpars

tr:
	./test_rgset
