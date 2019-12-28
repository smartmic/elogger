SHELL = /bin/bash
CPPFLAGS ?= -g -O0
sources = src/main.cpp src/measurement.cpp

src/elogger: $(sources)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(sources)

check: all
	diff tests/a0086944.txt <(./src/elogger tests/A0086944.BIN)
	@echo "*** ALL TESTS PASSED ***"

install:
	install -d $(DESTDIR)$(bindir)
	install -m 0755 src/elogger $(DESTDIR)$(bindir)

uninstall:
	rm -f $(DESTDIR)$(bindir)/elogger
	-rmdir $(DESTDIR)$(bindir)  >/dev/null 2>&1
clean:
	-rm src/elogger
