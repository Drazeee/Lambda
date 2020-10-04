main.o:
	gcc -W -Wall -Wextra -std=c99 src/main.c src/Detection/segmentation.c src/Tools/tools.c src/Detection/detect_char.c src/ImageTreatment/filters.c `pkg-config --cflags --libs gtk+-3.0` -lSDL2
	mv a.out OCR\ -\ Bitarrays
clean:
	rm OCR\ -\ Bitarrays