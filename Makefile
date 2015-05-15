all: elogger.o
	g++ -O -o elogger elogger.o

.cpp.o:
	g++ -c -Wall $<

clean:
	rm -f *.o
	rm -f elogger
