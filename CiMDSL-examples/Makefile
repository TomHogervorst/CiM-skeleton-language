PS_LIB_PATH=/home/tahogervorst/Downloads/pslib-0.4.5/libtool-dir/lib
LFLAGS=-lm -lps
CC=gcc

compile:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:PS_LIB_PATH
	$(CC) -o ps $(SOURCE) $(LFLAGS)

execute:
	./ps
