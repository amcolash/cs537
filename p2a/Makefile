###
#
# This Makefile will compile the c files in this directory
#
###

CC = gcc
args = -O -Wall

all:: mysh

mysh: mysh.c
	$(CC) $(args) -o mysh mysh.c

test: mysh
	@./mysh

tests: mysh
	@python ~cs537-2/testing/ShellTest.pyc .

###
# clean workspace
###
clean::
	rm -f mysh
