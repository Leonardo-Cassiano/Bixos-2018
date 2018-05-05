.PHONY: all clean flash load

IDMC = atmega328p

all: main.hex

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf: main.o motors.o sensors.o timer.o utils.o usart.o
	avr-gcc -o main.elf main.o motors.o sensors.o timer.o utils.o usart.o -mmcu=$(IDMC) -std=c99 -Wall -Wextra -Os

.c.o:
	avr-gcc -DF_CPU=8000000 -c $< -o $@ -mmcu=atmega328p -std=c99 -Wall -Wextra -Os

flash load:
	avrdude -c usbasp -p m328p -U flash:w:main.hex:i

clean:
	rm -f *.o main.hex main.elf
