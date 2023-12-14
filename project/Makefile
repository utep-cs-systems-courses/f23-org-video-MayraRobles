# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/


#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c


all: project.elf


#additional rules for files
project.elf: ${COMMON_OBJECTS} blinkBuzzMain.o wdInterruptHandler.o switches.o p2InterruptHandler.o led.o lcddraw.o lcdutils.o buzzer.o stateMachines.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd


load: project.elf
	msp430loader.sh $^


clean:
	rm -f *.o *~ *# *.elf


led.o: led.c led.h


wdInterruptHandler.o: stateMachines.h led.h switches.h buzzer.h


stateMachines.o: led.h stateMachines.h buzzer.h notes.h lcdutils.h lcddraw.h


buzzer.o: buzzer.h


p2InterruptHandler.o : switches.h


switches.o: switches.h led.h buzzer.h


blinkBuzMain.o: led.h switches.h buzzer.h lcddraw.h lcdutils.h 
