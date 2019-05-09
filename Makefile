CC = g++
CFLAGS = -std=c++11 -Wall -O3 -lm
all:
	g++ ${CFLAGS} -o proj proj2.cpp

	