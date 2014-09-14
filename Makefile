###
#
# This Makefile will compile the c files in this directory
#
###

CC = gcc
args = -Wall -g

all:: test

paradox.o: paradox.c
	$(CC) $(args) paradox.c -o paradox.o

test: paradox.o
	@echo "----------------------------------------------------------------------"
	@./paradox.o -i sampleIn.txt -o sampleOut.txt
	@echo "----------------------------------------------------------------------"

error: paradox.o
	@echo "----------------------------------------------------------------------"
	@./paradox.o -i in.txt -o out.txt
	@echo "----------------------------------------------------------------------"

###
# clean workspace
###
clean::
	rm -f paradox.o sampleOut.txt
