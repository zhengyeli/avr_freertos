CC = avr-gcc
CFLAG = -mmcu=atmega16 -Wall -Os

TARGET = all;

PATH_AVR = ./avr
INCLUDE_AVR = -I./avr/include/ -I./
FILES_AVR = $(wildcard $(PATH_AVR)/*.c ./main.c)
OBJ_AVR   = $(FILES_AVR:.c=.o)

PATH_FREERTOS = ./freertos
INCLUDE_FREERTOS = -I./avr/include/ -I./ -I./freertos/include/
FILES_FREERTOS = $(wildcard $(PATH_FREERTOS)/*.c)
OBJ_FREERTOS   = $(FILES_FREERTOS:.c=.o)

all:$(OBJ_AVR) $(OBJ_FREERTOS) 
	$(CC) $(CFLAG) $(INCLUDE_FREERTOS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAG) $(INCLUDE_FREERTOS) -o $@ -c $^

hex:
	@avr-objcopy -j .data -j .text -O ihex all main.hex  


clean:
	@rm -f *.hex *.o $(PATH_AVR)/*.o  $(PATH_FREERTOS)/*.o

program:
	@sudo avrdude -p m16 -c avrisp -P COM4 -e -U flash:w:main.hex