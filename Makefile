main.o:
	gcc src/main.c src/Detection/segmentation.c src/Tools/tools.c src/Detection/detect_char.c src/ImageTreatment/filters.c -W -Wall -Wextra -std=c99 -lSDL2

clean:
	rm a.out