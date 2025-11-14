#ifndef LEVEL_H
#define LEVEL_H

typedef struct Legend {
    char key;
    char* value;
} Legend;

typedef struct Level {
    char** mapArr;
    Legend* legend;
} Level;

#endif
