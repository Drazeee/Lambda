all: main

main: main.o segmentation.o tools.o detect_char.o filters.o
	# gcc -W -Wall -Wextra -Werror -std=c99 main.o segmentation.o tools.o detect_char.o filters.o -o OCR\ -\ Bitarrays `pkg-config --cflags --libs gtk+-3.0` -lSDL2
	gcc -W -Wall -Wextra -Werror -std=c99 main.o segmentation.o tools.o detect_char.o filters.o -o OCR\ -\ Bitarrays -lSDL2 -lm

main.o: src/main.c segmentation.o tools.o detect_char.o filters.o
	# gcc -c src/main.c `pkg-config --cflags --libs gtk+-3.0`
	gcc -c src/main.c

segmentation.o: src/Detection/segmentation.c
	gcc -c src/Detection/segmentation.c

tools.o: src/Tools/tools.c
	gcc -c src/Tools/tools.c 

detect_char.o: src/Detection/detect_char.c
	gcc -c src/Detection/detect_char.c

filters.o: src/ImageTreatment/filters.c
	gcc -c src/ImageTreatment/filters.c

clean:
	rm OCR\ -\ Bitarrays
	rm *.o