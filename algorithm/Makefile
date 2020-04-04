##
#	Makefile for my ICDE18 paper
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: LAF AAM

LAF: monitor.h input.h output.h global.h LAF.cpp
	$(CXX) $(CFLAGS) -o LAF LAF.cpp $(LIBS)  -D WATCH_MEM

AAM: monitor.h input.h output.h global.h AAM.cpp
	$(CXX) $(CFLAGS) -o AAM AAM.cpp $(LIBS)  -D WATCH_MEM

.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm LAF AAM 2> /dev/null || true
