#!/usr/bin/make -f

# Note: this make file has been updated to work on a 64 bit linux machine
# by adding -fPIC to the gcc command, and by using the /usr/lib64 folder

.DEFAULT_GOAL=mysqlxxhash.so

LIB=mysqlxxhash.so
TARGETDIR=$(DESTDIR)/usr/lib/mysql/plugin

mysqlxxhash.so: mysqlxxhash.cc
	gcc -Wall -O3 -funroll-loops -I/usr/include/mysql -fPIC -finline-functions -pipe -o $(LIB) -shared -L/usr/lib64 -lmysqlclient mysqlxxhash.cc

install: mysqlxxhash.so
	mkdir -p $(TARGETDIR)
	install -m755 $(LIB) $(TARGETDIR)

clean:
	rm -f $(LIB)
