SHELL = /bin/bash
CPPFLAGS ?= -g -O0
sources = main.cpp measurement.cpp

all: elogger

elogger: $(sources)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(sources)

check: all
	diff a0086944.txt <(./elogger A0086944.BIN)
	@echo "*** ALL TESTS PASSED ***"

install:
	install -d $(prefix)/bin
	install -m 0755 elogger $(prefix)/bin

uninstall:
	rm -f $(prefix)/bin/elogger
	-rmdir $(prefix)/bin >/dev/null 2>&1
clean:
	-rm elogger

.PHONY: all clean check install
