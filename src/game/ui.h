#ifndef UI_H
#define UI_H

#include <stdbool.h>

struct GameWorld;

typedef struct
{
    struct GameWorld* world;
    char cmdBuf[256];
    int cmdBufLetterCount;
    bool bConsoleEnabled;
} UI;

UI* ConstructUI(struct GameWorld* world);
void UpdateUI(UI* ui);
void DrawUI(UI* ui);

#endif