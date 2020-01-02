#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([elogger], [0.2.0], [dev@famic.de])
AC_CONFIG_SRCDIR([src/measurement.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MKTIME
AC_CHECK_FUNCS([memset])

AC_SUBST([SHELL], [/bin/bash])
AC_SUBST([TZ], [CET])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
