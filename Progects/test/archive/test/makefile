PROJECT = test

EABI = arm-none-eabi

CMSIS_DIR = /home/saturn/MEGA/Projects/STM32/PROJ_STM32L152/$(PROJECT)/src
CMSIS_INC = $(CMSIS_DIR)
MCU_INC = $(CMSIS_DIR)
MYLIB = /home/saturn/TMP/test/inc/

CC = $(EABI)-gcc
OC = $(EABI)-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb
CFLAGS += -Os
CFLAGS += -I./Inc -I$(CMSIS_INC) -I$(MCU_INC)

LDFLAGS = -T$(CMSIS_DIR)/STM32L152VB_FLASH.ld --specs=nano.specs
LDFLAGS += --specs=nosys.specs
LDFLAGS += -g

SRCS = main.c
SRCS += $(MYLIB)myfunction.c
SRCS += $(MYLIB)USART1.c
SRCS += $(CMSIS_DIR)/startup_stm32l1xx_md.s
load:
	st-flash write $(PROJECT).bin 0x8000000

all: $(PROJECT)
	$(OC) -Obinary $(PROJECT) $(PROJECT).bin

clean:
	$(RM) $(PROJECT)*

$(PROJECT): $(SRCS) makefile
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(PROJECT)
