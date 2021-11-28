CC = avr-gcc
CFLAG = -mmcu=atmega16 
CFLAG += -Wall 
CFLAG += -Os # 开优化定时器0启动不了
CFLAG += -std=gnu99 # 暂时没看出区别
TARGET = all;

PATH_AVR = ./avr
INCLUDE_AVR = -I./avr/include/ -I./ 
FILES_AVR = $(wildcard $(PATH_AVR)/*.c ./main.c)
OBJ_AVR   = $(FILES_AVR:.c=.o)
#OBJ_AVR   = main.o

PATH_FREERTOS = ./freertos
INCLUDE_FREERTOS = -I./avr/include/ -I./ -I./freertos/include/
FILES_FREERTOS = $(wildcard $(PATH_FREERTOS)/*.c)
OBJ_FREERTOS   = $(FILES_FREERTOS:.c=.o)

PATH_LFS = ./lfs
INCLUDE_LFS = -I./ -I./lfs/include/ -I./freertos/include/ -I./avr/include/
FILES_LFS = $(wildcard $(PATH_LFS)/*.c)
OBJ_LFS   = $(FILES_LFS:.c=.o)

OBJ_ALL += $(OBJ_FREERTOS)
#OBJ_ALL += $(OBJ_LFS)
OBJ_ALL += $(OBJ_AVR)
#$(OBJ_FREERTOS) $(OBJ_LFS)

hex:
	@make all
	@avr-objcopy -j .data -j .text -O ihex all main.hex  

all: 
	@make lfs
	@make freertos
	@make avr
	@$(CC) $(CFLAG) $(OBJ_ALL) -o $(TARGET)

avr: $(OBJ_AVR)
#$(CC) $(CFLAG) $(INCLUDE_AVR) -o $@ $^

%.o : %.c
	$(CC) $(CFLAG) $(INCLUDE_AVR) -o $@ -c $^

#freertos
freertos: $(OBJ_FREERTOS)
#$(CC) $(CFLAG) $(INCLUDE_FREERTOS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAG) $(INCLUDE_FREERTOS) -o $@ -c $^

#lfs
lfs: $(OBJ_LFS)
#$(CC) $(CFLAG) $(INCLUDE_LFS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAG) $(INCLUDE_LFS) -o $@ -c $^

clean:
	@rm -f *.hex *.o $(PATH_AVR)/*.o  $(PATH_FREERTOS)/*.o $(PATH_LFS)/*.o all

#program:
#	@sudo avrdude -p m16 -c usbasp -e -F -U flash:w:main.hex