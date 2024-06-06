CFLAGS 		+= -I./app/screens
CPPFLAGS 	+= -I./app/screens

VPATH += ./app/screens

#CPP source files
SOURCES_CPP += ./app/screens/screen_idle.cpp
SOURCES_CPP += ./app/screens/screen_info.cpp
SOURCES_CPP += ./app/screens/screen_main.cpp
SOURCES_CPP += ./app/screens/screen_setting.cpp
SOURCES_CPP += ./app/screens/bitmaps.cpp