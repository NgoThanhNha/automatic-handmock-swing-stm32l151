CFLAGS 		+= -I./sys/startup
CPPFLAGS 	+= -I./sys/startup

VPATH += sys/startup

#C source files 
SOURCES += sys/startup/stk_startup.c