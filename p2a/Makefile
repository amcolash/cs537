###
#
# This Makefile will compile the c files in this directory
#
###

CC = gcc
args = -O -Wall

all:: test

mysh.o: mysh.c
	$(CC) $(args) mysh.c -o mysh.o

test: mysh.o
	@./mysh.o

###
# clean workspace
###
clean::
	rm -f mysh.o
