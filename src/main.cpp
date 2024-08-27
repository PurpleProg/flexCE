/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <graphx.h>
#include "gfx/gfx.h"
#include "../include/render.hpp"
#include "../include/player.hpp"
#include "../include/map.hpp"


uint64_t get_current_time(void);

void handle_events(bool *running);
void update(Player *player, Rect *boundaries, const struct Map &map);
void render(Player *player, const struct Map &map);


int main(void) {
    // init screen
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetDrawBuffer();
    gfx_ZeroScreen();

    // constant declaration
    const struct Map map;


    // declare objects
    static Player player = Player(256, 256, map.TILE_SIZE/2);
    Rect boundaries = {0, 0, map.TILE_SIZE*map.COLUMNS, map.TILE_SIZE*map.ROWS};


    // mainloop
    bool running = true;
    while (running) {
        update(&player, &boundaries, map);
        render(&player, map);
    }

    // quit the game
    return 0;
}

void update(Player *player, Rect *boundaries, const struct Map &map) {
    player->update(boundaries, map);
}


void render(Player *player, const struct Map &map) {
    // clear the screen
    gfx_ZeroScreen();


    // draw sky
    gfx_SetColor(0);
    gfx_FillRectangle(
        0,
        0,
        map.WIDTH,
        map.HEIGHT/2
    );

    // draw floor
    gfx_SetColor(0);
    gfx_FillRectangle(
        map.HEIGHT/2,
        0,
        map.WIDTH,
        map.HEIGHT/2
    );

    // the fun part is here
    render_rays(player, map);

    // update the screen
    gfx_BlitBuffer();
}
