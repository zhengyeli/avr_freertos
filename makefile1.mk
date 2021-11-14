hex:
	@avr-objcopy -j .data -j .text -O ihex all main.hex  
