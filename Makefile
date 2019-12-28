package = elogger
version = 0.1
tarname = $(package)
distdir = $(tarname)-$(version)

all clean check elogger:
	cd src && $(MAKE) $@

dist: $(distdir).tar.gz

$(distdir).tar.gz: $(distdir)
	tar chof - $(distdir) | gzip -9 -c > $@
	rm -rf $(distdir)

$(distdir): FORCE
	mkdir -p $(distdir)/src
	cp Makefile $(distdir)
	cp src/Makefile src/*.cpp src/*.h src/a0086944.txt src/A0086944.BIN $(distdir)/src

distcheck: $(distdir).tar.gz
	gzip -cd $(distdir).tar.gz | tar xvf -
	cd $(distdir) && $(MAKE) all
	cd $(distdir) && $(MAKE) check
	cd $(distdir) && $(MAKE) clean
	rm -rf $(distdir)
	@echo "*** Package $(distdir).tar.gz is ready for distribution. ***"


FORCE:
	-rm $(distdir).tar.gz >/dev/null 2>&1
	rm -rf $(distdir)

.PHONY: FORCE all clean check dist
