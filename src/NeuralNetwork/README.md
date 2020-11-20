# DigitsLearning
Un projet "Brique" pour l'apprentissage et la prédiction de chiffres/lettres/symboles sur des images

Le réseau arrive à apprendre/reconnaître les lettres minuscules, majuscules et les chiffres avec une précision globale de 91-93% (encore en training).

Il y a deux programmes dans ce projet:
 - Learning, qui va faire l'apprentissage,
 - Analyze, qui en fonction des résultats de l'apprentissage, va reconnaitre des caractères et donner des statistiques (nombre de succès, d'échecs,...).


Reconnaît les symboles ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789 !?-%()&$":;/+=@# avec une précision de 93%.

<br/>

Le réseau est le même que celui pour la fonction XOR, mais au lieu de prendre 2 entrées, il va en prendre 1024. Ces 1024 entrées correspondent aux pixels des images d'entrées (32x32).
Le dataset est générable avec le script Python generateDataset.py (dépendence: PIL / Pillow). Les paramètres du haut sont modifiables (nombre d'images, polices, chemin de sortie).


<br><br>
Des datasets pré-générés sont trouvables à l'adresse https://madrau.fr/ocr/.<br>Dataset2000 est un "gros" dataset de 2000 images/char (450 Mo).<br>Dataset100 est un dataset "light" de 100 images/char (24 Mo).<br>
Le réseau tel qu'il est entraîné au jour du 27/10 est disponible à l'adresse https://madrau.fr/ocr/Network.zip.

# Documentation

### Dataset

Tout ce qui se trouve dans le dossier Dataset sont des fonctions/methodes/structures qui vont permettre de charger et utiliser les images du dataset.
 
 Les images sont sous la forme d'une structure **MMImage**.
 Une struct image a 4 attributs:
  - w (int32_t) : Sa largeur
  - h (int32_t) : Sa hauteur
  - character (char) : Le chiffre qui y est représenté
  - pixelsTable (MMPixelsTable) : Ses pixels   
 Une struct pixelsTable a un seul attribut:
  - pixelValue (double) : 1.0 si le pixel est noir, 0.0 si il est blanc.
  
 <br/>

Il y a deux fonction pour charger les images:

 - `MMImage LoadImage(char* path);`
   
   va charger l'image au chemin path sous la forme d'une struct image (son paramètre digit n'est alors pas initialisé)
   
   
 - `MMImage* LoadDataset(char* path, int noChars, int imagesPerChar);`
   va charger *imagesPerChar* images du dataset au chemin *path* pour les *noChars* premiers caractères et les renvoie sous la forme d'un pointeur vers un tableau de struct image.
   
En gros: `LoadDataset(3, 500);` va charger 500 images pour les lettres A, B et C.


<br/><br/>
Examples:
```c
images* dataSet = LoadDataset("/Users/maxime/OCR/Dataset", 2, 1500);
char c = dataSet[1234].character;  (c = 'A': le caractère de la 1234e image du dataset)
double p = dataSet[1234].pixelsTable[42].pixelValue; (p sera égal à 1.0 si le 42e pixel de la 1234e image du dataset est noir, 0.0 si blanc)
```

### Network
Les networks sont sous la forme d'un MMNetwork. Ils contiennent les informations comme les poids et les biais de la couche cachée, et de la couche de sortie.

  - numInputs (int) : Nombres de neurones dans la couche d'entrée
  - numHiddenNodes (int) : Nombres de neurones dans la couche intermédiaire
  - numOutputs (int) : Nombres de neurones dans la couche de sortie
  - hiddenWeights (MMNode) : Poids des transitions des entrées vers les neurones cachés
  - outputWeights (MMNode) : Poids des transitions des neurones cachés vers les neurones de sortie
  - hiddenLayerBias (double*) : Biais des neurones de la couche intermédiaire pour une certaine entrée
  - outputLayerBias (double*) : Biais des neurones de la couche de sortie pour une certaine entrée

 Une struct MMNode a un seul attribut:
  - weights (double*) : Tableau de valeurs
<br><br>
On peut enregistrer un réseau de neurones (entrainé ou pas, mais entraîné c'est quand même plus utile) avec la fonction SaveNetwork:

```c
void SaveNetwork(MMNetwork n, char* path)
```

On peut printer les paramètres d'un réseau (pas très utile, à part pour tester) avec la fonction PrintNetwork:

```c
void PrintNetwork(MMNetwork n)
```
    
<br><br>
Pour créer un réseau, on utilise la fonction InitNetwork, avec pour paramètres le nombre de neurones dans chaque couche. Attention: le réseau crée a tous ses paramètres à 0. Pour faire un training, il faut que ses paramètres soient initialisés aléatoirement entre -0.5 et 0.5 avec la fonction InitWeightsForNetwork.

```c
MMNetwork InitNetwork(int numInputs, int numHiddenNodes, int numOutputs)
void InitWeightsForNetwork(MMNetwork network)
```

On peut aussi charger un réseau précédemment enregistré avec LoadNetwork. Plus besoin de spécifier les paramètres, ils sont maintenant enregistrée avec le réseau.

```c
MMNetwork LoadNetwork(char* path)
```

Pour copier un réseau à partir d'un autre, on utilise CopyNetwork.
```c
MMNetwork CopyNetwork(MMNetwork *s)
```
<br><br>
Pour free un réseau, on utilise DestroyNetwork.
```c
void DestroyNetwork(MMNetwork n)
```
<br><br>
Pour faire un test, et reconnaître un caractère sur une image, on utilise la fonction Predict

```c
double* Predict(MMNetwork network, const MMImage* image)
```

Predict renvoie un tableau de double correspondant au "score" de chacuns des caractères. Le caractère détécté est donc celui dont l'index est la plus grande valeur du tableau.<br>
(Exemple: la plus grande valeur du tableau est la 1e valeur du tableau: caractère = A. 36e valeur = caractère 9.)

Pour se simplifier la tâche, la fonction OutputChar fait tout pour nous.

```c
char OutputChar(double* outputLayer)
```


Pour obtenir plus de résultats, on peut utiliser la fonction PredictionDetails, qui renvoie un tableau de struct Guess dans l'ordre de "chance" (voir 2e programme ci dessous).
```c
Guess* PredictionDetails(double* outputLayer)
```

Une struct Guess contient 3 paramètres:
  - character (char) : le caractère associé
  - score (double) : le score de détéction (la valeur dans la couche de sortie)
  - rate (double) : Pourcentage de chance que ce soit ce caractère

 
<br>
Au final, avec toutes ces fonctions, on peut reconnaitre le caractère sur une image avec un programme tout simple comme ça:


```c
  #include <stdio.h>
  #include "LambdaNeuralNetwork.h"

  int main(int argc, const char * argv[]) {
    
    srand((unsigned)time(NULL));
      
      
    MMImage img = LoadImage("/Users/maxime/#.bmp");
    
    MMNetwork n = LoadNetwork("/Users/maxime/IAC");
    
    double* output = Predict(n, &img);
    char recognized = OutputChar(output);
    
    printf("Recognized as a %c\n\n", recognized);
    
    return 0;
  }
```

Pour obtenir plus de détails (plusieurs prédictions avec leur pourcentages):

```c
  #include <stdio.h>
  #include "Predict.h"

  int main(int argc, const char * argv[]) {
    
    srand((unsigned)time(NULL));
      
      
    MMImage img = LoadImage("/Users/maxime/W.bmp");
    
    MMNetwork n = LoadNetwork("/Users/maxime/IAC");
    
    double* output = Predict(n, &img);
    Guess* recognized = PredictionDetails(output);
    
    
    for (int place = 0; place < 10; place ++) {
      Guess rec = recognized[place];
      printf("	- %c (%.2f%%)\n", rec.character, rec.rate);
    }
    printf("\n");
    
    return 0;
  }
```

Note: Les images DOIVENT avoir une taille de 32×32, avoir un fond blanc pour un foreground foncé, et le caractère sur l'image doit être en x = 0 et y = 0. (Pas de ligne ou de colonne vide avant le début du caractère)

# Compilation

On peut compiler le réseau qui apprend la fonction XOR avec 

```
    make xor
```

Cela créera un exécutable ./bin/xor.
Ce programme crée un réseau qui va apprendre la fonction XOR, puis effectuera des prédictions.

Pour build la lib ou les programme:

```
    make lib
    make analyze
    make learning
    make all
    make clean
```

Effectuer une de ces commandes créera des dossiers *bin*, *include* et *lib* dans le dossier actuel.

Les libs seront dans le dossier *lib*. Linker le fichier LambdaNeuralNetwork.o suffit: il contient lui même toutes les fonctions des autres .o.

Les executables seront dans le dossier *bin*.

Les headers seront dans le dossier *include*. Inclure le fichier "LambdaNeuralNetwork.h" suffit: il inclut lui même tous les autres headers.
  
<br>

Pour compiler un programme en incluant le réseau de neurones, il faut inclure lib/LambdaNeuralNetwork.o et les headers du dossier include.

    gcc -IDigitsLearning/include DigitsLearning/lib/LambdaNeuralNetwork.o MonProgramme.c  $(sdl2-config --libs --cflags)
