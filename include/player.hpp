#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include <SDL.h>
#include "../include/map.hpp"


class Player {
public:
    Player(float startx, float starty, float size);

    SDL_FRect rect;
    SDL_FRect prev_rect;
    double angle;
    float FOV;
    // player direction vector
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    void update(std::set<SDL_Keycode> *keys, SDL_Rect *boundaries, const struct Map &map);
    void render(SDL_Renderer *renderer);
private:
    float BASE_SPEED;
    float speed;
    float angle_rotation_speed;
    void collide_boundaries(SDL_Rect *boundaries);
    void collide_map(const struct Map &map);
    double normalize_angle(double angel);
};


#endif