bin_PROGRAMS = elogger
elogger_SOURCES = main.cpp measurement.cpp measurement.h

check_SCRIPTS = difftest.sh
TESTS = $(check_SCRIPTS)

TZ = @TZ@ # necessary because test(s) use locale for strftime	\
formatting and timestamps in test files use CET timezone
diff_var = @diff_var@

difftest.sh:
	echo '$(diff_var) $(top_srcdir)/tests/a0086944.txt <(TZ=$(TZ) ./elogger $(top_srcdir)/tests/A0086944.BIN)' > difftest.sh
	chmod +x difftest.sh

CLEANFILES = difftest.sh
