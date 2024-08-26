#include "../include/player.hpp"
#include <iostream>


Player::Player(int startx, int starty, int size) {
    rect = {startx, starty, size, size};
    speed = 1;
}

void Player::update(std::set<SDL_Keycode> *keys, SDL_Rect *boundaries) {
    // move
    if (keys->count(SDLK_RIGHT)) {
        rect.x += speed;
    } else if (keys->count(SDLK_LEFT)) {
        rect.x -= speed;
    }
    if (keys->count(SDLK_DOWN)) {
        rect.y += speed;
    } else if (keys->count(SDLK_UP)) {
        rect.y -= speed;
    }
    // collide
    collide_boundaries(boundaries);
}


void Player::collide_boundaries(SDL_Rect *boundaries) {
    if ((rect.x + rect.w) > (boundaries->x + boundaries->w)) {rect.x = (boundaries->x + boundaries->w - rect.w);} // right
    if (rect.x < boundaries->x) {rect.x = boundaries->x;} // left
    if ((rect.y + rect.h) > (boundaries->y + boundaries->h)) {rect.y = (boundaries->y + boundaries->h - rect.h);} // bottom
    if (rect.y < boundaries->y) {rect.y = boundaries->y;}     // top
}


void Player::render(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

}