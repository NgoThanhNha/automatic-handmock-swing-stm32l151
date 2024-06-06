CFLAGS += -I./common
CPPFLAGS += -I./common

VPATH += ./common

# C source files
SOURCES += ./common/xprintf.c
SOURCES += ./common/screen_manager.c

# CPP source files
SOURCES_CPP += ./common/view_render.cpp