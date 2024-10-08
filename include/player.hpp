#ifndef PLAYER_H
#define PLAYER_H

#include <keypadc.h>
#include "../include/map.hpp"


class Player {
public:
    Player(int startx, int starty, int size);

    Rect rect;
    double angle;
    // player direction vector
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    void update(kb_key_t *key, const struct Map &map);
    void render();
private:
    float BASE_SPEED;
    float speed;
    float angle_rotation_speed;
    void collide_map(const struct Map &map);
    double normalize_angle(double angel);
};


#endif