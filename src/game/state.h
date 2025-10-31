#ifndef STATE_H
#define STATE_H

typedef enum GameState {
    STATE_MAINMENU,
    STATE_OPTIONSMENU,
    STATE_LEVELSELECTIONMENU,
    STATE_LOADING,
    STATE_INGAME,
    STATE_PAUSED
} GameState;

#endif
