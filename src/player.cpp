#include "../include/player.hpp"
#include <iostream>
#include <math.h>


Player::Player(float startx, float starty, float size) {
    rect = {startx, starty, size, size};
    BASE_SPEED = 0.1;
    speed = BASE_SPEED;
    angle = 0.0;
}

void Player::update(std::set<SDL_Keycode> *keys, SDL_Rect *boundaries) {
    // check sprint
    if (keys->count(SDLK_RSHIFT) || keys->count(SDLK_LSHIFT)) {
        speed = 4*BASE_SPEED;
    } else {
        speed = BASE_SPEED;
    }
    // update angle
    if (keys->count(SDLK_RIGHT)) {
        angle += speed / 100.0;
    } else if (keys->count(SDLK_LEFT)) {
        angle -= speed / 100.0;
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

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, &rect);

    // render a line for the angle dir
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // yellow
    float rect_center_x = rect.x + rect.w/2.0;
    float rect_center_y = rect.y + rect.h/2.0;
    float end_x = rect_center_x + (2*rect.w) * std::cos(angle);
    float end_y = rect_center_y + (2*rect.w) * std::sin(angle);
    SDL_RenderDrawLineF(
        renderer,
        rect_center_x, rect_center_y,
        end_x, end_y
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
