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
    const int WIDTH = map.TILE_SIZE*map.COLUMNS * 2;
    for (int x = 0; x<WIDTH; x++) {
        double camera_x = (x/(double)WIDTH * 2) -1;   // project world x in camera space (range -1 to 1)
        double ray_dir_x = player->dir_x + player->plane_x * camera_x;
        double ray_dir_y = player->dir_y + player->plane_y * camera_x;

        // tell which direction the ray goes
        int8_t step_x;
        int8_t step_y;

        // calculate unit of distance
        double unit_distance_x = std::abs(1/ray_dir_x);
        double unit_distance_y = std::abs(1/ray_dir_y);

        // ray lenght. this is the euclidian distance, not a side.
        double ray_len_x = 0;
        double ray_len_y = 0;

        // get map position
        int map_pos_x = int(player->rect.x + (player->rect.w/2.0));
        int map_pos_y = int(player->rect.y + (player->rect.h/2.0));

        // if the ray hit with direction it is
        bool ray_hit = false;
        bool ray_hit_on_x_axis;


        /////////////////////////////////////////////////////////
        // calculate initial ray position
        if (ray_dir_x > 0) {  // right
            step_x = 1;
            ray_len_x = (map_pos_x + 1 - (player->rect.x + (player->rect.w/2.0))) * unit_distance_x;
        } else {
            step_x = -1;
            ray_len_x = ((player->rect.x + (player->rect.w/2)) - map_pos_x) * unit_distance_x;
        }
        if (ray_dir_y > 0) {
            step_y = 1;
            ray_len_y = (map_pos_y + 1 - (player->rect.y - (player->rect.h/2.0))) * unit_distance_y;
        } else {
            step_y = -1;
            ray_len_y = ((player->rect.y - (player->rect.h/2.0)) - map_pos_y) * unit_distance_y;
        }
    }
}
