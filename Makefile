all: elogger.o
	g++ -O -o elogger elogger.o

elogger.o: elogger.cpp
	gcc -Wall -c elogger.cpp
