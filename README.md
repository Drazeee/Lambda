# Lambda

Education project at EPITA | Optical Character Recognition

We are a groupe composed of 4 students at EPITA, a french IT engineer school. We do an OCR from scratch ans we are doing everything to achieve this project as sucessful as possible.

# Table of Contents

* [Team Members](#team-members)
* [The project](#the-project)
* [Compilation](#compilation)
* [Execution](#execution)
* [Features](#features)

# <a name="team-members"></a>Team Members

* "Charles SIMON-MEUNIER" [https://draze.fr](https://draze.fr)
* "Quentin FISCH" [https://qfisch.fr](https://qfisch.fr)
* "Maxime MADRAU" [https://madrau.fr](https://madrau.fr)
* "Nathan AVÉ"

# <a name="the-project"></a>The project

See the specificatons for this project [here](http://debug-pro.com/epita/prog/s3/project/s3_project_en.pdf) (french version [here](http://debug-pro.com/epita/prog/s3/project/s3_project_fr.pdf))

All this project is written is C language. Defense reports are written in TeX and could be found [here](https://bitarrays.fr/projects/lamba)

# <a name="compilation"></a>Compilation

To compile our OCR project, ensure you have installed the SDL2 library as well as GTK on your machine.

Our Makefile allows you to compile by simply using the make command at the root of the project

```bash
➜  Lambda git:(master) ✗ make
gcc -c src/Detection/segmentation.c
gcc -c src/Tools/tools.c
gcc -c src/Detection/detect_char.c
gcc -c src/ImageTreatment/filters.c
gcc -c src/main.c
gcc -W -Wall -Wextra -Werror -std=c99 main.o segmentation.o tools.o detect_char.o filters.o -o OCR\ -\ Bitarrays -lSDL2 -lm
```

# <a name="execution"></a>Execution

For instance, our project only got 3 commands. If you want to use our grayscale filter just execute the command line below

```bash
./OCR\ -\ Bitarrays grayscale "image-path" "destination"
```

Use our filters on your image by using this command line

```bash
./OCR\ -\ Bitarrays filters "image-path" "destination"
```

To finish, try our segmentation algorithm with this command line

```bash
./OCR\ -\ Bitarrays segmentation "image-path" "destination"
```

# <a name="features"></a> Features

* [X] Loading images and removing colors
* [X] Detection and division into blocks, lines and characters
* [X] Neural network able to learn XOR function
* [X] Pre-treatment of image
* [X] Saving and loading of neural network weights
* [X] Dataset for learning
* [X] Manipulation of files for saving results
* [ ] Complete neural network for reconizing characters
* [ ] Text reconstruction and saving
* [ ] User interface
* [ ] Spell checker
* [ ] Multi column, layout and images in text management
