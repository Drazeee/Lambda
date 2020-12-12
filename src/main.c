#include "main.h"
#include <SDL2/SDL_surface.h>

char *columnRecognition(char *directory, int isItalic)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(directory);
	char *resultColumns = "";
	int columnsNumber = 0; // total number of columns in the DIR
	int len = strlen(directory);
	if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
			if (dir->d_name[0] != '.' && dir->d_name[0] != 'l') {
				columnsNumber++;
			}
		}
	}
	char *temp = "";
	int columnIndex = 0;
	for (int i = 0; i < columnsNumber; i++) {
		char path[len + 40];
		snprintf(path, len + 40, "%s/%i.bmp", directory, i);
		temp = paragraphSegmentation(path, "results/tempParagraphs", 0, 
			isItalic);
		strcat(temp, "\n===========\n");

		char *result = malloc(strlen(resultColumns) + strlen(temp) + 1);
		strcpy(result, resultColumns);
		strcat(result, temp);
		resultColumns = result;
	}
	//free(temp);
	return resultColumns;
}

char *columnSegmentation(char *path, char *destination, int print, int isItalic)
{
	remove_directory(destination);
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return "";
	}
	imgDefault = cutColumn(imgDefault);
	convertColumns(imgDefault, destination);
	char *result = columnRecognition(destination, isItalic);
	if (print)
	{
		printf("%s", result);
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return result;
}



char *paragraphSegmentation(char *path, char *destination, int print, 
	int isItalic)
{
	remove_directory(destination);
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return "";
	}
	imgDefault = cutLine(imgDefault, 1);
	char *result = removeLines(imgDefault, destination, 0, isItalic);
	if (print)
	{
		printf("%s\n", result);
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return result;
}

char *lineSegmentation(char *path, char *destination, int print)
{
	remove_directory(destination);
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return NULL;
	}
	imgDefault = cutLine(imgDefault, 0);
	char *allLines = removeLines(imgDefault, destination, 1, 0);
	if (print)
	{
		printf("result: %s\n", allLines);
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return allLines;
}


char *lineSegmentationWithoutLoad(SDL_Surface *imgDefault, char *destination, 
	int print, int isItalic)
{
	remove_directory(destination);
	imgDefault = cutLine(imgDefault, 0);
	char *allLines;
	allLines = removeLines(imgDefault, destination, 1, isItalic);
	if (print)
	{
		printf("result: %s\n", allLines);
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return allLines;
}


int wordSegmentation(char *path, char *destination, int print)
{
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return 1;
	}
	imgDefault = cutWord(imgDefault);
	removeLinesForWords(imgDefault, destination);
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return 0;
}

char *characterSegmentation(char *path, char *destination, int print)
{
	remove_directory(destination);
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return NULL;
	}
	int *allPos = cutCharacters(imgDefault, destination);
	char *result;
	result = removeLinesForCharacters(imgDefault, destination, allPos);
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return result;
}

char *characterSegmentationWithoutLoad(SDL_Surface *imgDefault,
	char *destination, int print, int isItalic)
{
	remove_directory(destination);
	int *allPos;
	char *result;
	if (!isItalic) {
		allPos = cutCharacters(imgDefault, destination);
		result = removeLinesForCharacters(imgDefault, destination, allPos);
	}
	else {
		allPos = cutCharactersItalic(imgDefault, destination);
		result = removeLinesForItalicChars(imgDefault, destination, allPos);
	}
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return result;
}

void array_print(int *begin)
{
    int *i = begin;
    for (int line = 0; *i != -42; ++i)
    {
        if (line > 72)
        {
            printf("|`|\n");
            line = 0;
        }

        line += printf("| %4d ", *i);
    }

    printf("|\n");
}


int remove_directory(const char *path) {
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d) {
      struct dirent *p;

      r = 0;
      while (!r && (p=readdir(d))) {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
             continue;

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf) {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)) {
                if (S_ISDIR(statbuf.st_mode))
                   r2 = remove_directory(buf);
                else
                   r2 = unlink(buf);
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }

   if (!r)
      r = rmdir(path);

   return r;
}



// INTERFACE

int columns = 1;
int contrast = 0;
int noise = 0;
int correction = 0;
int italic = 0;
int rotate = 0;

GtkBuilder *builder;
SDL_Surface *img;
char *filename;

typedef struct {
    GtkWidget *errorImageLabel;
    GtkWidget *resultLabel;
} app_widgets;

app_widgets        *widgets;

void interface()
{
    gtk_disable_setlocale();
    setlocale(LC_NUMERIC, "en_US"); // We use . instead ,
    widgets = g_slice_new(app_widgets);
    gtk_init(NULL, NULL);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/Interface/interface.glade", NULL);
    GtkWidget       *window;
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main"));
    widgets->errorImageLabel  = GTK_WIDGET(gtk_builder_get_object(builder, 
		"errorImage"));
    widgets->resultLabel  = GTK_WIDGET(gtk_builder_get_object(builder, 
		"resultOutput"));
	
	if (macOSDarkMode()) { // Of course!
		AddCSS("src/Interface/MacOSDarkMode.css");
	}

	
    gtk_builder_connect_signals(builder, widgets);

    gtk_widget_show(window);
    g_object_unref(builder);

    gtk_main();

    printf("%i|%i|%i|%i", columns, contrast, noise, correction);
}

// called when window is closed
void on_destroy()
{
    gtk_main_quit();
}

void file_set (GtkFileChooser *file_chooser, gpointer data)
{
    filename = gtk_file_chooser_get_preview_filename (file_chooser);
    img = SDL_LoadBMP(filename);
    if (!img) {
        gtk_label_set_text(GTK_LABEL(widgets->errorImageLabel),
    "We cant't load your image. Please make sur that this is a .bmp extension");
    }
    else {
        gtk_label_set_text(GTK_LABEL(widgets->errorImageLabel), "");
    }
}


void toggleColumns()
{
    columns = !columns;
}

void toggleContrast()
{
    contrast = !contrast;
}

void toggleNoise()
{
    noise = !noise;
}

void toggleCorrection()
{
    correction = !correction;
}

void toggleItalic()
{
	italic = !italic;
}

void toggleRotation()
{
	rotate = !rotate;
}

void startRecognition()
{
	remove_directory("results/resultColumn");
	remove_directory("results/resultParagraph");
	remove_directory("results/tempParagraphs");
	remove_directory("results/temp.bmp");
	remove_directory("results/tempChar");
	remove_directory("results/test");
	GtkTextBuffer *buffer;
	buffer =gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->resultLabel));
    if (img) {
		if (rotate) {
			img = autoRotation(img);
		}
		grayscale(img, 1, "results/temp.bmp");
		if (noise)
			img = noiseReduction(img);
		if (contrast)
			img = contrastImage(img);
		img = blackAndWhite(img, 1, "results/temp.bmp");
		char *result;
		if (columns) {
			result = columnSegmentation("results/temp.bmp", "results/test", 1,
				italic);
		}
		else {
			result = paragraphSegmentation("results/temp.bmp", 
				"results/test", 1, italic);
		}
        gtk_text_buffer_set_text (buffer, result, -1);
        //free(result);
    }
    else {
        gtk_text_buffer_set_text (buffer, "Invalid image", -1);
    }
}



// END INTERFACE




int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	remove_directory("results/resultColumn");
	remove_directory("results/resultParagraph");
	remove_directory("results/tempParagraphs");
	remove_directory("results/temp.bmp");
	remove_directory("results/tempChar");
	remove_directory("results/test");
	if (argc < 2) {
		interface();
		//printf("Lambda: Error during parsing command\n");
		return 1;
	} 


	// ITALIC TEST
	if (strcmp(argv[1], "italic") == 0){
		SDL_Surface *imgDefault;
		char *destination = "results/resultItalic";
		imgDefault = SDL_LoadBMP(argv[2]);
		if (!imgDefault) {
			if (1) 
			{
				printf("\033[0;31m"); 
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				printf("\033[0m");
			}
			return 1;
		}
		int *allPos = cutCharactersItalic(imgDefault, destination);
		array_print(allPos);
		removeLinesForItalicChars(imgDefault, destination, allPos);
		if (1)
		{
			printf("\33[0;32mLambda: segmentation ended successfully.\n");
			printf("The result is here: \"%s\"\033[0m\n\n", destination);
		}
		return 0;
	}
	
	if (strcmp(argv[1], "column") == 0) {
		columnSegmentation(argv[2], "results/resultColumn", 1, italic);
		return 0;
	}
	if (strcmp(argv[1], "wordpos") == 0) {
		SDL_Surface *img  = SDL_LoadBMP("exampleItalic.bmp");
		wordPositionsItalic(img);
		SDL_SaveBMP(img, "salut.bmp");
		return 0;
	}
	if (strcmp(argv[1], "autorotate") == 0) {
		SDL_Surface *img;
		img = SDL_LoadBMP(argv[2]);
		if (!img) {
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", argv[2]);
			printf("\033[0m");
			return 1;
		}
		img = autoRotation(img);
		SDL_SaveBMP(img, "results/rotation.bmp");
		SDL_FreeSurface(img);
		return 0;
	}
	else if (strcmp(argv[1], "paragraph") == 0) {
		paragraphSegmentation(argv[2], "results/resultParagraph", 1, italic);
		return 0;
	}
	else if (strcmp(argv[1], "line") == 0) {
		lineSegmentation(argv[2], "results/resultLine", 1);
		return 0;
	}
	else if (strcmp(argv[1], "word") == 0) {
		return wordSegmentation(argv[2], "results/resultWord", 1);
	}
	else if (strcmp(argv[1], "character") == 0) {
		return characterSegmentation(argv[2], "results/resultChar", 1) != NULL;
	}
	else if (strcmp(argv[1], "grayscale") == 0) {
		if (argc == 4) {
			SDL_Surface *imgDefault;
			imgDefault = SDL_LoadBMP(argv[2]);
			if (!imgDefault) {
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				return 1;
			}
			imgDefault = grayscale(imgDefault, 1, argv[3]);
			printf("Lambda: Grayscale ended successfully\n");
			return 0;
		}
		else {
			printf("Lambda: Grayscale take exactly 2 paramaters but was ");
			printf("called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}
	else if (strcmp(argv[1], "resize") == 0) {
		if (argc == 5) {
			SDL_Surface *imgDefault;
			imgDefault = SDL_LoadBMP(argv[2]);
			if (!imgDefault) {
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				return 1;
			}
			if (atoi(argv[3]) && atoi(argv[4])) {
				SDL_SaveBMP(resize(imgDefault, atoi(argv[3]), atoi(argv[4])),
					"results/resize.bmp");
				printf("Lambda: Resize ended successfully\n");
				return 0;
			}
			else {
				printf("Lambda: Grayscale can't cast arg 2 and 3 to int\n");
				return 1;
			}
		}
		else {
			printf("Lambda: Grayscale take exactly 3 paramaters but ");
			printf("was called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}
	else if (strcmp(argv[1], "contrast") == 0)
	{
		if (argc == 4 || argc == 5) {
			SDL_Surface *imgDefault;
			imgDefault = SDL_LoadBMP(argv[2]);
			if (!imgDefault) {
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				return 1;
			}
			if (argc == 5 && strcmp(argv[4], "true") == 0)
			{
				imgDefault = noiseReduction(imgDefault);
				printf("Lambda: Noise reduction ended successfully\n");
			}
			
			//imgDefault = contrastImage(imgDefault);
			printf("Lambda: Contrast ended successfully\n");
			SDL_SaveBMP(imgDefault, argv[3]);
			return 0;
		}
		else {
			printf("Lambda: Contrast take 2 or 3 paramaters but was ");
			printf("called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}
	else if (strcmp(argv[1], "blackwhite") == 0) {
		if (argc == 4) {
			SDL_Surface *imgDefault;
			imgDefault = SDL_LoadBMP(argv[2]);
			if (!imgDefault) {
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				return 1;
			}
			imgDefault = blackAndWhite(imgDefault, 1, argv[3]);
			printf("Lambda: Black and White ended successfully\n");
			return 0;
		}
		else {
			printf("Lambda: Black and White take exactly 2 paramaters but");
			printf(" was called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}
	else {
		interface();
		return 1;
	}
	SDL_Quit();
	return 0;
}
