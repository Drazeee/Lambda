CFLAGS= -Wall -Wextra -std=c99 -lm
CC=gcc
SDLFLAGS = -lSDL2
GTKFLAGS = `pkg-config --cflags --libs gtk+-3.0`
NAME = Lambda

all: main

main: main.o segmentation.o tools.o detect_char.o filters.o recognition.o
	gcc -o ${NAME} *.o src/NeuralNetwork/lib/LambdaNeuralNetwork.o -Wall -Wextra -Werror -std=c99 `pkg-config --cflags --libs gtk+-3.0` -lSDL2 -lm -rdynamic

main.o: src/main.c segmentation.o tools.o detect_char.o filters.o recognition.o
	gcc -c src/main.c `pkg-config --cflags --libs gtk+-3.0`

recognition.o: src/Recognition/recognition.c
	gcc -c src/Recognition/recognition.c

segmentation.o: src/Detection/segmentation.c
	gcc -c src/Detection/segmentation.c `pkg-config --cflags --libs gtk+-3.0`

tools.o: src/Tools/tools.c
	gcc -c src/Tools/tools.c 

detect_char.o: src/Detection/detect_char.c
	gcc -c src/Detection/detect_char.c

filters.o: src/ImageTreatment/filters.c
	gcc -c src/ImageTreatment/filters.c

clean:
	rm -f ${NAME}
	rm -f *.o
	rm -rf columns
	rm -rf lines*
	rm -rf chars
	rm -rf exampleChars
	rm -rf results
	mkdir results
	cp src/.resultText results/WHAT_IS_IT
