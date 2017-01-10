SOURCES=test_system.cpp adder_signed.cpp multiplier_signed.cpp gt.cpp mux2.cpp divider_signed.cpp subtractor_signed.cpp
SYSTEMC_HOME=/data/systemc-2.3.1
SYSTEMC_LIB_PATH=/usr/bin
SYSTEM_ARCH=linux64
FLAGS=-Wall
LFLAGS=-lsystemc -lm
CC=g++

compile:
	sed s/IN_SIZE/$(INSIZE)/g test_system.cpp.sed >test_system_temp.cpp.sed
	sed s/OUT_SIZE/$(OUTSIZE)/g test_system_temp.cpp.sed >test_system.cpp
	$(CC) $(FLAGS) -I. -I$(SYSTEMC_HOME)/include -L. -L$(SYSTEMC_HOME)/lib-$(SYSTEM_ARCH) -o system $(SOURCES) $(LFLAGS)

execute:
	./system -L$(SYSTEMC_LIB_PATH)
