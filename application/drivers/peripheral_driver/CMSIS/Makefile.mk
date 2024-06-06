CFLAGS += -I./drivers/peripheral_driver/CMSIS/Device/ST/STM32L1xx/Include
CFLAGS += -I./drivers/peripheral_driver/CMSIS/Include
CPPFLAGS += -I./drivers/peripheral_driver/CMSIS/Device/ST/STM32L1xx/Include
CPPFLAGS += -I./drivers/peripheral_driver/CMSIS/Include

VPATH += drivers/peripheral_driver/CMSIS/Device/ST/STM32L1xx/Source/Templates

# C source files
SOURCES += ./drivers/peripheral_driver/CMSIS/Device/ST/STM32L1xx/Source/Templates/system_stm32l1xx.c