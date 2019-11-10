testme: testme.c
	gcc -o testme testme.c -coverage -fpic -lm
run: testme
	./testme
coverage: 
	gcov testme.c -b -f 
clean:
	rm -f testme *.gcno *.gcda *.gcov
