CFLAGS 		+= -I./sys/irq
CPPFLAGS 	+= -I./sys/irq

VPATH += ./sys/irq

# C source files
SOURCES += ./sys/irq/system_irq.c