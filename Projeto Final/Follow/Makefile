all: main.hex

main.hex: main.elf
    $ avr-objcopy -j .text -j .data -O ihex main.elf main.hex

