# makefile, R.G, May 03, 2020

MCU=attiny85
F_CPU = 16500000L
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues

#-------------------
all: main.hex
main.hex : main.out 
	$(OBJCOPY) -R .eeprom -O ihex main.out main.hex
main.out : main.o
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o
main.o : main.c
	$(CC) $(CFLAGS) -Os -c main.c
#-------------------
help: 
	@echo "Type make or make install"	
#-------------------
install:
	sudo -E env "PATH=$(PATH)" micronucleus --run main.hex	
clean:
	rm -f *.o *.map *.out main.hex
#-------------------
