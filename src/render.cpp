#include <iostream>
#include <SDL.h>
#include "../include/render.hpp"


void render_map(SDL_Renderer *renderer, const struct Map &map) {
    for (int row_index = 0; row_index < map.ROWS; row_index++) {
        for (int column_index = 0; column_index < map.COLUMNS; column_index++) {

            if (map.DATA[row_index][column_index]) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // tile are blue
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // transparent
            }
            SDL_Rect tile_rect = {
                column_index*map.TILE_SIZE,
                row_index*map.TILE_SIZE,
                map.TILE_SIZE, map.TILE_SIZE
            };
            SDL_RenderFillRect(renderer, &tile_rect);
        }
    }
}


void render_rays(SDL_Renderer *renderer, Player *player, const struct Map &map) {
    // cast a ray for each pixel on screen
    const int WIDTH = map.TILE_SIZE*map.COLUMNS;
    const double distance_to_prejection = WIDTH / player->FOV;
    for (int x = 1; x<WIDTH; x++) {
        double projected_x = distance_to_prejection/x;
        std::cout << projected_x << '\n';
    }
    // int a = 1/0;  // breakpoint
}
