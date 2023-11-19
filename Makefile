all:
	cc commands.c print_functions.c input_processing.c open-close_functions.c main.c -o fat32emulator
clean:
	rm -f *.o *.mk
