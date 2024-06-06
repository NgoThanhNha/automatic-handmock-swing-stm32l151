include app/screens/Makefile.mk

CFLAGS 		+= -I./app
CPPFLAGS 	+= -I./app

VPATH += ./app

#CPP source files
SOURCES_CPP += ./app/app.cpp
SOURCES_CPP += ./app/bsp.cpp
SOURCES_CPP += ./app/task_polling.cpp
SOURCES_CPP += ./app/task_list.cpp
SOURCES_CPP += ./app/task_display.cpp
SOURCES_CPP += ./app/task_pid.cpp
SOURCES_CPP += ./app/task_safety.cpp
SOURCES_CPP += ./app/task_sm.cpp
SOURCES_CPP += ./app/link_phy.cpp