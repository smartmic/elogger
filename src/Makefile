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
	install -d $(DESTDIR)$(bindir)
	install -m 0755 elogger $(DESTDIR)$(bindir)

uninstall:
	rm -f $(DESTDIR)$(bindir)/elogger
	-rmdir $(DESTDIR)$(bindir)  >/dev/null 2>&1
clean:
	-rm elogger

.PHONY: all clean check install
