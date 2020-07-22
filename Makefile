#!/usr/bin/make -f

# Note: this make file has been updated to work on a 64 bit linux machine
# by adding -fPIC to the gcc command, and by using the /usr/lib64 folder

.DEFAULT_GOAL=mysqlxxhash.so

LIB=mysqlxxhash.so
TARGETDIR=$(DESTDIR)/usr/lib/mysql/plugin

mysqlxxhash.so: mysqlxxhash.cc
	        gcc -Wall -O3 -funroll-loops `mysql_config --cflags` -fPIC -finline-functions -pipe -o mysqlxxhash.so  -shared `mysql_config --libs` mysqlxxhash.cc

install: mysqlxxhash.so
	mkdir -p $(TARGETDIR)
	install -m755 $(LIB) $(TARGETDIR)

clean:
	rm -f $(LIB)
