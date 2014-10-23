all:
	gcc -c -fpic mem.c -Wall -Werror
	gcc -shared -o libmem1.so mem.o
	gcc -shared -o libmem2.so mem.o
	gcc -shared -o libmem3.so mem.o

test:
	python ~cs537-2/testing/p3a/MemTest.pyc .

clean:
	rm *.so mem.o
