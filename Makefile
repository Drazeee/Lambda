CFLAGS= -Wall -Wextra -std=c99 -lm -lSDL2 -rdynamic
CC=gcc
SDLFLAGS = -lSDL2
GTKFLAGS = `pkg-config --cflags --libs gtk+-3.0`
NNFLAGS = -Isrc/NeuralNetwork/include -Isrc/NeuralNetwork/src
NAME = Lambda

all: main

main: main.o segmentation.o tools.o detect_char.o filters.o recognition.o
	$(MAKE) -C src/NeuralNetwork lib
	gcc -o ${NAME} *.o src/NeuralNetwork/lib/LambdaNeuralNetwork.o $(CFLAGS) -Werror $(GTKFLAGS) $(NNFLAGS)

main.o: src/Interface/MacOSDarkMode.c src/main.c segmentation.o tools.o detect_char.o filters.o recognition.o
	gcc -c src/main.c src/Interface/MacOSDarkMode.c $(NNFLAGS) $(GTKFLAGS)

recognition.o: src/Recognition/recognition.c
	gcc -c src/Recognition/recognition.c $(NNFLAGS)

segmentation.o: src/Detection/segmentation.c
	gcc -c src/Detection/segmentation.c $(NNFLAGS) $(GTKFLAGS)

tools.o: src/Tools/tools.c
	gcc -c src/Tools/tools.c 

detect_char.o: src/Detection/detect_char.c
	gcc -c src/Detection/detect_char.c

filters.o: src/ImageTreatment/filters.c
	gcc -c src/ImageTreatment/filters.c

clean:
	$(MAKE) -C src/NeuralNetwork clean
	rm -f ${NAME}
	rm -f *.o
	rm -rf columns
	rm -rf lines*
	rm -rf chars
	rm -rf exampleChars
	rm -rf results
	mkdir results
	cp src/.resultText results/WHAT_IS_IT
