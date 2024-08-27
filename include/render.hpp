#ifndef RENDER_H
#define RENDER_H

#include "../include/player.hpp"
#include "../include/map.hpp"


void render_rays(SDL_Renderer *renderer, Player *player, const struct Map &map);


#endif