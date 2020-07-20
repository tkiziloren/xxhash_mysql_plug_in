This repo contains user defined function "xxhash" for MySQL.
This function is used in SureChEMBL project.

Note:
xxhash_mysql_plug_in does not install dependencies on libmysqlclient or mysql-server or anything like that.

In order to compile the library make sure **gcc**, **gpp**, **libmysqlclient-dev** and **make** tools installed on your system. 

Example configuration for required tools for debian based distributions. 


```
sudo apt install make
sudo apt install gcc
sudo apt install g++
sudo apt install libmysqlclient-dev
```

> Note: If you need to install this plug in to non-debian based distributions, please update the paths in the Makefile to match with mysql path in your system. 

Compiling:
```
make \\ creates mysqlxxhash.so in the local folder
make install \\ creates mysqlxxhash.so and installs it to /usr/lib/mysql/plugin directory.
```

You can register this function manually (or automate this task for your particular database)
this way:

```
$ mysql -uroot -p<PASSWORD> <DB> -e "CREATE FUNCTION xxhash RETURNS INTEGER SONAME 'mysqlxxhash.so'"
```

<DB> parameter is optional. If you omit it, then this function will be available for all
databases served by your particular instance of MySQL.


To drop the function run:
```
$ mysql -uroot -p<PASSWORD> <DB> -e "DROP FUNCTION xxhash"
```
(again <DB> parameter is optional)


> **Disclaimer1:** xxHash is an extremely fast non-cryptographic hash algorithm, working at speeds close to RAM limits. It is proposed in two flavors, 32 and 64 bits. The algorithm is developed by Yann Collet(@Cyan4973)

> **Disclaimer2:** xxhash64.h is a library which contains xxhash implementation of Yann Collet's xxHash64 algorithm. This library developed by [Stephan Brumme](https://github.com/stbrumme/xxhash) Also see [Stephan Brumme's explanation of xxhash algorithm](https://create.stephan-brumme.com/xxhash/)  
