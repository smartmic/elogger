SHELL = /bin/bash
CPPFLAGS ?= -g -O0
sources = main.cpp measurement.cpp

all: elogger

elogger: $(sources)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(sources)

check: all
	diff a0086944.txt <(./elogger A0086944.BIN)
	@echo "*** ALL TESTS PASSED ***"
clean:
	-rm elogger

.PHONY: all clean check
