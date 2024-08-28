#include "../include/render.hpp"
#include <graphx.h>
#include <math.h>


void render_rays(Player *player, const struct Map &map) {
    // cast a ray for each pixel on screen
    for (int x = 0; x<map.WIDTH; x++) {
        double camera_x = (x/(double)map.WIDTH * 2) -1;   // project world x in camera space (range -1 to 1)
        double ray_dir_x = player->dir_x + player->plane_x * camera_x;
        double ray_dir_y = player->dir_y + player->plane_y * camera_x;

        // tell which direction the ray goes
        int8_t step_x;
        int8_t step_y;

        // calculate unit of distance
        double unit_distance_x = fabs(1/ray_dir_x);
        double unit_distance_y = fabs(1/ray_dir_y);

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
            gfx_SetColor(3); // blue
        } else {
            perpendicular_wall_distance = ray_len_y - unit_distance_y;
            gfx_SetColor(2);  // red
        }

        double line_height = (int)map.HEIGHT/perpendicular_wall_distance;
        int start_y = map.HEIGHT/2 - line_height/2;

        gfx_VertLine(
            x, start_y, line_height
        );
    }
}
