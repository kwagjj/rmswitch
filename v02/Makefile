FILE=txb2.c
DEVPATH=/dev/bus/usb/001/007

step1:
	avr-gcc -mmcu=atmega328p -Wall -Os -o main.elf $(FILE)

step2:
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
step3:
	sudo avrdude -c usbasp -p m328p -P $(DEVPATH) -U flash:w:main.hex

readfuse:
	sudo avrdude -c usbasp -p m328p -P $(DEVPATH) -U lfuse:r:lfuse.bin:b

fuse1:
	sudo avrdude -c usbasp -p m328p -P $(DEVPATH) -U lfuse:w:0x62:m

rmfile:
	rm main.elf main.hex
