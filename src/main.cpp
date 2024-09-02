/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <graphx.h>
#include <keypadc.h>
#include "gfx/gfx.h"
#include "../include/render.hpp"
#include "../include/player.hpp"
#include "../include/map.hpp"


void update(Player *player, kb_key_t *key, const struct Map &map);
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
    kb_key_t key;


    // mainloop
    do {
      kb_Scan();
      key = kb_Data[7];
      update(&player, &key, map);
      render(&player, map);
    } while (kb_Data[1] != kb_Del);


    gfx_End();
    return 0;
}

void update(Player *player, kb_key_t *key, const struct Map &map) {
    player->update(key, map);
}


void render(Player *player, const struct Map &map) {
    // clear the screen
    gfx_ZeroScreen();


    // draw sky
    gfx_SetColor(5);  // light blue
    gfx_FillRectangle(
        0,
        0,
        map.WIDTH,
        map.HEIGHT/2
    );

    // draw floor
    gfx_SetColor(4);  // light grey
    gfx_FillRectangle(
        0,
        map.HEIGHT/2,
        map.WIDTH,
        map.HEIGHT/2
    );

    // the fun part is here
    render_rays(player, map);

    // update the screen
    // gfx_SwapDraw();
    gfx_BlitBuffer();
}
