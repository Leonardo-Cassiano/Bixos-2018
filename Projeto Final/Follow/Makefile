.PHONY: all clean flash load

IDMC = m8

all: main.hex

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf: hardware.o main.o motors.o sensors.o timer.o utils.o
	avr-gcc -o main.elf hardware.o main.o motors.o sensors.o timer.o utils.o -mmcu=atmega8 -std=c99 -Wall -Wextra -Os

.c.o:
	avr-gcc -DF_CPU=8000000 -c $< -o $@ -mmcu=atmega8 -std=c99 -Wall -Wextra -Os

flash load:
	avrdude -c usbasp -p m8 -U flash:w:main.hex:i

clean:
	rm -f *.o main.hex main.elf
