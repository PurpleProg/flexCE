#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include <SDL.h>


class Player {
public:
    Player(int startx, int starty, int size);

    SDL_Rect rect;
    void update(std::set<SDL_Keycode> *keys);
    void render(SDL_Renderer *renderer);
private:
    int speed;
};


#endif