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
    const int HEIGHT = map.TILE_SIZE*map.ROWS;
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

        // ray lenght. this is the euclidian distance, not a side. Or is it ?
        double ray_len_x = 0;
        double ray_len_y = 0;

        // get player pos in map coordinates
        double player_x_pos = (player->rect.x + (player->rect.w/2.0)) / map.TILE_SIZE;
        double player_y_pos = (player->rect.y + (player->rect.h/2.0)) / map.TILE_SIZE;

        // get map position
        int map_pos_x = int(player_x_pos);
        int map_pos_y = int(player_y_pos);

        // if the ray hit with direction it is
        bool ray_hit = false;
        bool ray_hit_on_x_axis;


        // calculate initial ray position
        if (ray_dir_x > 0) {  // right
            step_x = 1;
            ray_len_x = (map_pos_x + 1 - player_x_pos) * unit_distance_x;
        } else {    // left
            step_x = -1;
            ray_len_x = (player_x_pos - map_pos_x) * unit_distance_x;
        }
        if (ray_dir_y > 0) {   // down
            step_y = 1;
            ray_len_y = (map_pos_y + 1 - player_y_pos) * unit_distance_y;
        } else {   // up
            step_y = -1;
            ray_len_y = (player_y_pos - map_pos_y) * unit_distance_y;
        }

        // perform the DDA
        while (!ray_hit) {
            if (ray_len_x < ray_len_y) {
                ray_len_x += unit_distance_x;
                map_pos_x += step_x;
                ray_hit_on_x_axis = true;
            } else {
                ray_len_y += unit_distance_y;
                map_pos_y += step_y;
                ray_hit_on_x_axis = false;
            }
            // check map
            if (map.DATA[map_pos_y][map_pos_x]) {
                ray_hit = true;
            }
            // prevent ray OoB
            if (map_pos_x >= map.COLUMNS || map_pos_x < 0 || map_pos_y >= map.ROWS || map_pos_y < 0) {
                ray_hit = true;
            }
        }

        // render the lines
        double perpendicular_wall_distance;
        if (ray_hit_on_x_axis) {
            perpendicular_wall_distance = ray_len_x - unit_distance_x;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else {
            perpendicular_wall_distance = ray_len_y - unit_distance_y;
            SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        }

        double line_height = (int)HEIGHT/perpendicular_wall_distance;
        int start_y = HEIGHT/2 - line_height/2;
        int end_y = start_y + line_height;

        SDL_RenderDrawLineF(
            renderer,
            x,
            start_y,
            x,
            end_y
        );
    }
}
