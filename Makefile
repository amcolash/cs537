###
#
# This Makefile will compile the c files in this directory
#
###

CC = gcc
args = -Wall -g

all:: test

bday: bday.c
	$(CC) $(args) bday.c -o bday.o

test: bday
	@./bday.o

###
# clean workspace
###
clean::
	rm -f bday.o sampleOut.txt
	touch sampleOut.txt
