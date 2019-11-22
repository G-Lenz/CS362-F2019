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
	gcc unittest1.c dominion.o rngs.o -o unittest1 -coverage -fpic -lm -g
unittest2: unittest2.c dominion.o rngs.o
	gcc unittest2.c dominion.o rngs.o -o unittest2 -coverage -fpic -lm -g
unittest3: unittest3.c dominion.o rngs.o
	gcc unittest3.c dominion.o rngs.o -o unittest3 -coverage -fpic -lm -g
unittest4: unittest4.c dominion.o rngs.o
	gcc unittest4.c dominion.o rngs.o -o unittest4 -coverage -fpic -lm -g
unittest5: unittest5.c dominion.o rngs.o
	gcc unittest5.c dominion.o rngs.o -o unittest5 -coverage -fpic -lm -g
unittests: unittest1 unittest2 unittest3 unittest4 unittest5

rununittests:
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out

cleanunittests:
	rm -f unittest1 unittest2 unittest3 unittest4 unittest5
randomtest1: randomtestcard1.c dominion.o rngs.o
	gcc randomtestcard1.c dominion.o rngs.o -o randomtest1 -coverage -fpic -lm -g

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc randomtestcard2.c dominion.o rngs.o -o randomtest2 -coverage -fpic -lm -g
randomtest3: randomtestcard3.c dominion.o rngs.o
	gcc randomtestcard3.c dominion.o rngs.o -o randomtest3 -coverage -fpic -lm -g
randomtests: randomtest1 randomtest2 randomtest3 

runrandomtests: 
	./randomtest1 | sort -r | uniq >> randomtestresults.out
	./randomtest2 | sort -r | uniq >> randomtestresults.out
	./randomtest3 | sort -r | uniq >> randomtestresults.out
coverageinfo: 
	gcov dominion.c -b -f >> randomtestresults.out
randomtestresults: randomtests runrandomtests coverageinfo

cleanrandomtests:
	rm randomtestresults.out randomtest1 randomtest2 randomtest3 

