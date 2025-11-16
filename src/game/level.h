#ifndef LEVEL_H
#define LEVEL_H

#include <stdlib.h>

typedef struct Legend {
    char* key;
    char* value;
} Legend;

typedef struct Level {
    char** mapArr;
    size_t mapArrSizeX;
    size_t mapArrSizeY;
    int playerStartX;
    int playerStartY;
    int* zombiesSpawnX;
    int* zombiesSpawnY;
} Level;

#endif
