SHELL := /bin/bash
sources = main.cpp measurement.cpp

all: elogger

elogger: $(sources)
	g++ -g -Og -o $@ $(sources)

check: all
	diff a0086944.txt <(./elogger A0086944.BIN)
	@echo "*** ALL TESTS PASSED ***"
clean:
	-rm elogger

.PHONY: all clean check
