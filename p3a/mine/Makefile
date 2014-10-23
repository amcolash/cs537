libmem.so: mem.c mem.h
	gcc -c -Wall -m32 -fpic mem.c -O
	gcc -shared -Wall -m32 -o libmem.so mem.o -O

clean:
	rm -rf mem.o libmem.so
