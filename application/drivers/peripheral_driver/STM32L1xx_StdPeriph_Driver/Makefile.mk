CFLAGS += -I./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/inc
CPPFLAGS += -I./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/inc

VPATH += drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src

# C source files
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_gpio.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rcc.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_usart.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_spi.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/misc.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_exti.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_syscfg.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_tim.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_adc.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rtc.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_pwr.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_iwdg.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_comp.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dac.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_i2c.c
SOURCES += ./drivers/peripheral_driver/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dma.c