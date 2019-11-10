CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

unittest1: unittest1.c dominion.o rngs.o
	gcc unittest1.c dominion.o rngs.o -o unittest1 -coverage -fpic -lm

unittest2: unittest2.c dominion.o rngs.o
	gcc unittest2.c dominion.o rngs.o -o unittest2 -coverage -fpic -lm
unittest3: unittest3.c dominion.o rngs.o
	gcc unittest3.c dominion.o rngs.o -o unittest3 -coverage -fpic -lm
unittest4: unittest4.c dominion.o rngs.o
	gcc unittest4.c dominion.o rngs.o -o unittest4 -coverage -fpic -lm
unittest5: unittest5.c dominion.o rngs.o
	gcc unittest5.c dominion.o rngs.o -o unittest5 -coverage -fpic -lm
unittests: unittest1 unittest2 unittest3 unittest4 unittest5

rununittests: 
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
coverageinfo: 
	gcov dominion.c -b -f >> unittestresults.out
unittestresults: unittests rununittests coverageinfo

cleanunittests:
	rm unittestresults.out unittest1 unittest2 unittest3 unittest4 unittest5 dominion.c.gcov 

