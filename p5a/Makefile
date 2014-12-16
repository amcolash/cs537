main:: server

all: mfs.c mfs.h udp.o
	gcc -c -fPIC mfs.c -Wall -Werror
	gcc -c -fPIC udp.c -Wall -Werror
	gcc -shared -o libmfs.so mfs.o udp.o -fPIC
	gcc server.c -Wall -Werror -o server udp.o

server: all server.c udp.o
	gcc server.c -Wall -Werror -o server udp.o
	rm -f test.img
	touch test.img
	chmod 755 test.img
	./server 9870 test.img

client: all client.c
	gcc -g -L. -lmfs -Xlinker -rpath=. -o client client.c
	./client 9870

test:
	python ~cs537-2/testing/p5a/runtests.py

test1:
	python ~/Desktop/p5a-tests/runtests.py

clean:
	rm -rf *.o *.so client server test.img
