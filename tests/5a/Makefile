INSTALL_PATH=$(CURDIR)

runtests:
	echo "#!/bin/bash" > $@
	echo "base=$(INSTALL_PATH)" >> $@
	echo "python \$$base/project5a.py --test-path \$$base \$$@ |"\
		"tee -i runtests.log" >> $@
	echo "exit \$$?" >> $@
	chmod a+x runtests

install: runtests
	mkdir -p $(INSTALL_PATH)
	cp -r * $(INSTALL_PATH)
	afs_rseta $(INSTALL_PATH) system:anyuser read

check:
	pychecker --only *.py

clean:
	rm -f runtests
	rm -f *.pyc
	rm -f libpdrop.so

libpdrop.so: pdrop.c
	gcc -shared -ldl -fPIC $< -o $@
