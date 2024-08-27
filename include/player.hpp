#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include <SDL.h>


class Player {
public:
    Player(float startx, float starty, float size);

    SDL_FRect rect;
    double angle;
    void update(std::set<SDL_Keycode> *keys, SDL_Rect *boundaries);
    void render(SDL_Renderer *renderer);
private:
    float BASE_SPEED;
    float speed;
    float angle_rotation_speed;
    void collide_boundaries(SDL_Rect *boundaries);
    double normalize_angle(double angel);
};


#endif