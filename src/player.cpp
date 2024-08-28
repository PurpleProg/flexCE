#include <math.h>
#include <keypadc.h>
#include "../include/map.hpp"
#include "../include/player.hpp"


Player::Player(int startx, int starty, int size) {
    rect = {startx, starty, size, size};
    BASE_SPEED = 1.5;

    speed = BASE_SPEED;
    angle_rotation_speed = 0.05;
    angle = 0.0;

    dir_x = 0.0;
    dir_y = 0.0;

    plane_x = 0;
    plane_y = 0.66;
}

void Player::update(const struct Map &map) {

    // check sprint
    if (kb_Data[1] & kb_2nd) {
        speed = 2*BASE_SPEED;
    } else {
        speed = BASE_SPEED;
    }

    // update angle and rotate plane
    if (kb_Data[7] & kb_Right) {
        angle += angle_rotation_speed;
        // update/rotate plane
        double old_plane_x = plane_x;
        plane_x = old_plane_x * cos(angle_rotation_speed) - plane_y * sin(angle_rotation_speed);
        plane_y = old_plane_x * sin(angle_rotation_speed) + plane_y * cos(angle_rotation_speed);
    } else if (kb_Data[7] & kb_Left) {
        angle -= angle_rotation_speed;
        // update/rotate plane
        double old_plane_x = plane_x;
        plane_x = old_plane_x * cos(-angle_rotation_speed) - plane_y * sin(-angle_rotation_speed);
        plane_y = old_plane_x * sin(-angle_rotation_speed) + plane_y * cos(-angle_rotation_speed);


    }
    angle = normalize_angle(angle);

    // move
    if (kb_Data[7] & kb_Up) {
        rect.x += speed * cos(angle);
        rect.y += speed * sin(angle);
    } else if (kb_Data[7] & kb_Down) {
        rect.x += speed * cos(angle - M_PI);
        rect.y += speed * sin(angle - M_PI);
    }
    if (kb_Data[4] & kb_LParen) {
        rect.x += speed * cos(angle + (M_PI / 2.0));
        rect.y += speed * sin(angle + (M_PI / 2.0));
    } else if (kb_Data[5] & kb_RParen) {
        rect.x += speed * cos(angle - (M_PI / 2.0));
        rect.y += speed * sin(angle - (M_PI / 2.0));
    }

    // update direction
    dir_x = cos(angle);
    dir_y = sin(angle);

    // collide
    collide_map(map);
}


void Player::collide_map(const struct Map &map) {
    for (int row_index = 0; row_index < map.ROWS; row_index++) {
        for (int column_index = 0; column_index < map.COLUMNS; column_index++) {
            if (
                map.DATA[row_index][column_index] &&
                rect.x + rect.w > column_index*map.TILE_SIZE &&
                rect.x < (column_index + 1)*map.TILE_SIZE &&
                rect.y + rect.h > row_index*map.TILE_SIZE &&
                rect.y < (row_index + 1)*map.TILE_SIZE
            ) {

                // get tile rect values
                float tile_left = column_index * map.TILE_SIZE;
                float tile_right = tile_left + map.TILE_SIZE;
                float tile_top = row_index * map.TILE_SIZE;
                float tile_bottom = tile_top + map.TILE_SIZE;

                // get overlaps for each direction
                float right_overlap = (rect.x + rect.w) - tile_left;
                float left_overlap = tile_right - rect.x;
                float top_overlap = tile_bottom - rect.y;
                float bottom_overlap = (rect.y + rect.h) - tile_top;

                // resove based on the smallest overlap
                if (fmin(right_overlap, left_overlap) < fmin(top_overlap, bottom_overlap)) {
                    if (fabs(right_overlap-left_overlap) < 2) {continue;}
                    else if (right_overlap < left_overlap) {
                        rect.x = tile_left - rect.w;
                    } else {
                        rect.x = tile_right;
                    }
                } else {
                    if (fabs(top_overlap-bottom_overlap) < 2) {continue;}
                    else if (top_overlap < bottom_overlap) {
                        rect.y = tile_bottom;
                    } else {
                        rect.y = tile_top - rect.h;
                    }
                }
            }
        // end of double for loop
        }
    }
}


double Player::normalize_angle(double angle) {
    // bound angle to -PI, PI
    while (angle > M_PI) {
        angle -= 2.0 * M_PI;
    }
    while (angle <= -M_PI) {
        angle += 2.0 * M_PI;
    }
    return angle;
}
