#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>


class Player {
public:
    Player(int startx, int starty, int size);

    SDL_Rect rect;
    void update(void);
    void render(SDL_Renderer *renderer);
};


#endif