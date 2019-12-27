sources = main.cpp measurement.cpp

all: elogger

elogger: $(sources)
	g++ -g -Og -o $@ $(sources)

clean:
	-rm elogger

.PHONY: all clean
