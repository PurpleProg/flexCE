#include <math.h>
#include "../include/map.hpp"
#include "../include/player.hpp"


Player::Player(float startx, float starty, float size) {
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

void Player::update(std::set<SDL_Keycode> *keys, SDL_Rect *boundaries, const struct Map &map) {

    // check sprint
    if (keys->count(SDLK_RSHIFT) || keys->count(SDLK_LSHIFT)) {
        speed = 2*BASE_SPEED;
    } else {
        speed = BASE_SPEED;
    }

    // update angle and rotate plane
    if (keys->count(SDLK_RIGHT)) {
        angle += angle_rotation_speed;
        // update/rotate plane
        double old_plane_x = plane_x;
        plane_x = old_plane_x * std::cos(angle_rotation_speed) - plane_y * std::sin(angle_rotation_speed);
        plane_y = old_plane_x * std::sin(angle_rotation_speed) + plane_y * std::cos(angle_rotation_speed);
    } else if (keys->count(SDLK_LEFT)) {
        angle -= angle_rotation_speed;
        // update/rotate plane
        double old_plane_x = plane_x;
        plane_x = old_plane_x * std::cos(-angle_rotation_speed) - plane_y * std::sin(-angle_rotation_speed);
        plane_y = old_plane_x * std::sin(-angle_rotation_speed) + plane_y * std::cos(-angle_rotation_speed);


    }
    angle = normalize_angle(angle);

    // move
    if (keys->count(SDLK_w)) {
        rect.x += speed * std::cos(angle);
        rect.y += speed * std::sin(angle);
    } else if (keys->count(SDLK_s)) {
        rect.x += speed * std::cos(angle - M_PI);
        rect.y += speed * std::sin(angle - M_PI);
    }
    if (keys->count(SDLK_d)) {
        rect.x += speed * std::cos(angle + (M_PI / 2.0));
        rect.y += speed * std::sin(angle + (M_PI / 2.0));
    } else if (keys->count(SDLK_a)) {
        rect.x += speed * std::cos(angle - (M_PI / 2.0));
        rect.y += speed * std::sin(angle - (M_PI / 2.0));
    }

    // update direction
    dir_x = std::cos(angle);
    dir_y = std::sin(angle);

    // collide
    collide_boundaries(boundaries);
    collide_map(map);
}


void Player::collide_boundaries(SDL_Rect *boundaries) {
    // replace the player inside the boundaries
    // usualy {0, 0, SCREED_WIDTH, SCREEN_HEIGHT} for 2D rendering
    if ((rect.x + rect.w) > (boundaries->x + boundaries->w)) {rect.x = (boundaries->x + boundaries->w - rect.w);} // right
    if (rect.x < boundaries->x) {rect.x = boundaries->x;} // left
    if ((rect.y + rect.h) > (boundaries->y + boundaries->h)) {rect.y = (boundaries->y + boundaries->h - rect.h);} // bottom
    if (rect.y < boundaries->y) {rect.y = boundaries->y;}     // top
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
                if (std::min(right_overlap, left_overlap) < std::min(top_overlap, bottom_overlap)) {
                    if (std::abs(right_overlap-left_overlap) < 2) {continue;}
                    else if (right_overlap < left_overlap) {
                        rect.x = tile_left - rect.w;
                    } else {
                        rect.x = tile_right;
                    }
                } else {
                    if (std::abs(top_overlap-bottom_overlap) < 2) {continue;}
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


void Player::render(SDL_Renderer *renderer) {

    // render player rect/hitbox
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderFillRectF(renderer, &rect);

    // render the direction vector (multiplyed so it's not 1 pixel long lol)
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // yellow
    float centerx = (rect.x + rect.w/2.0);
    float centery = (rect.y + rect.h/2.0);
    float dir_end_x = centerx + dir_x * 20;
    float dir_ent_y = centery + dir_y * 20;
    SDL_RenderDrawLineF(
        renderer,
        centerx,
        centery,
        dir_end_x,
        dir_ent_y
    );

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
