#include "../include/player.hpp"
#include <iostream>
#include <math.h>


Player::Player(float startx, float starty, float size) {
    rect = {startx, starty, size, size};
    BASE_SPEED = 2.5;
    FOV = 60.0;

    speed = BASE_SPEED;
    angle_rotation_speed = 0.05;
    angle = 0.0;

    dir_x = 0.0;
    dir_y = 0.0;
}

void Player::update(std::set<SDL_Keycode> *keys, SDL_Rect *boundaries) {
    // check sprint
    if (keys->count(SDLK_RSHIFT) || keys->count(SDLK_LSHIFT)) {
        speed = 2*BASE_SPEED;
    } else {
        speed = BASE_SPEED;
    }

    // update angle
    if (keys->count(SDLK_RIGHT)) {
        angle += angle_rotation_speed;
    } else if (keys->count(SDLK_LEFT)) {
        angle -= angle_rotation_speed;
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

    //update direction
    // dir_x = (rect.x + rect.w/2.0) + std::cos(angle);
    // dir_y = (rect.y + rect.h/2.0) + std::sin(angle);
    dir_x = std::cos(angle);
    dir_y = std::sin(angle);

    // collide
    collide_boundaries(boundaries);
}


void Player::collide_boundaries(SDL_Rect *boundaries) {
    // replace the player inside the boundaries
    // usualy {0, 0, SCREED_WIDTH, SCREEN_HEIGHT} for 2D rendering
    if ((rect.x + rect.w) > (boundaries->x + boundaries->w)) {rect.x = (boundaries->x + boundaries->w - rect.w);} // right
    if (rect.x < boundaries->x) {rect.x = boundaries->x;} // left
    if ((rect.y + rect.h) > (boundaries->y + boundaries->h)) {rect.y = (boundaries->y + boundaries->h - rect.h);} // bottom
    if (rect.y < boundaries->y) {rect.y = boundaries->y;}     // top
}


void Player::render(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderFillRectF(renderer, &rect);

    // render the direction
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // yellow
    SDL_RenderDrawLineF(
        renderer,
        (rect.x + rect.w/2.0),
        (rect.y + rect.h/2.0),
        (rect.x + rect.w/2.0) + dir_x * 20,
        (rect.y + rect.h/2.0) + dir_y * 20
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
