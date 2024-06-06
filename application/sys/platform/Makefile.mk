CFLAGS 		+= -I./sys/platform/platform
CPPFLAGS 	+= -I./sys/platform/platform

CFLAGS 		+= -I./sys/platform
CPPFLAGS 	+= -I./sys/platform

VPATH += ./sys/platform

# C source files
SOURCES += ./sys/platform/platform.c