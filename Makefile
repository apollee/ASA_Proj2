CC = g++
CFLAGS = -std=c++11 -Wall -lm -g
all:
	g++ ${CFLAGS} -o proj proj2.cpp

	