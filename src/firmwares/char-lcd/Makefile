TARGET = char-lcd

CC = avr-gcc
OBJCOPY = avr-objcopy

CLOCK = 16000000

SOURCES = main.c lcd.c

# Из каждого файла с расширением .c будем делать объектный файл
OBJECTS = $(SOURCES:.c=.o)

MCU = atmega8
PROGRAMMER = usbasp

CFLAGS = -mmcu=$(MCU) -Wall -g -Os -Werror -lm  -mcall-prologues -DF_CPU=$(CLOCK)
LDFLAGS = -mmcu=$(MCU)  -Wall -g -Os  -Werror 

ifeq ($(OS),Windows_NT)
        DEL_FILE = del
else # Linux
        DEL_FILE = rm -f
        PORT = -P /dev/ttyUSB0
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@.elf  $(OBJECTS) -lm
	$(OBJCOPY) -O binary -R .eeprom -R .nwram $@.elf $@.bin
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram $@.elf $@.hex

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(DEL_FILE) *.elf *.bin *.hex $(OBJECTS) *.map

flash: $(TARGET)
	avrdude $(PORT) -B 2 -c $(PROGRAMMER) -p $(MCU) -e -U flash:w:$(TARGET).hex

	
