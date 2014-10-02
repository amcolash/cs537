
INSTALL_PATH=$(CURDIR)
PYTHON_PATH=python

all: runtests generate

runtests:
	echo "#!/bin/bash" > $@
	echo "base=$(INSTALL_PATH)" >> $@
	echo "$(PYTHON_PATH) \$$base/project1a-contest.py --test-path \$$base \$$@"\
		" | tee runtests.log" >> $@
	echo "exit \$$?" >> $@
	chmod a+x runtests

install: runtests generate
	mkdir -p $(INSTALL_PATH)
	cp -r * $(INSTALL_PATH)
	afs_rseta $(INSTALL_PATH) system:anyuser read

check:
	pychecker --only *.py

clean:
	rm -f runtests
	rm -f *.pyc
	rm -f generate

generate: generate.c sort.h
	gcc -O -Wall -o $@ $<
