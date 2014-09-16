###
#
# This Makefile will compile the c files in this directory
#
###

CC = gcc
args = -O -Wall

all:: test

paradox: paradox.c
	$(CC) $(args) paradox.c -o paradox

test: paradox
	@echo "----------------------------------------------------------------------"
	@#./paradox -i sampleIn.txt -o sampleOut.txt
	@./paradox -i input -o sampleOut.txt
	@java -jar ~cs537-2/ta/tests/test1a/P1aTest.jar ~/private/537/p1-537/
	@echo "----------------------------------------------------------------------"

error: paradox
	@echo "----------------------------------------------------------------------"
	@./paradox -i in.txt -o out.txt
	@echo "----------------------------------------------------------------------"

###
# clean workspace
###
clean::
	rm -f paradox paradox.o output sampleOut.txt
