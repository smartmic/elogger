SHELL = /bin/sh
OBJ = main.o measurement.o
NAME = elogger

all: $(OBJ)
	g++ -O -o $(NAME) $(OBJ) 

%.o: src/%.cpp
	g++ -c -Wall $<

clean:
	rm -f *.o
	rm -f elogger
