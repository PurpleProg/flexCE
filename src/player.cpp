#include "../include/player.hpp"
#include <iostream>


Player::Player(int startx, int starty, int size) {
    rect = {startx, starty, size, size};
    speed = 5;
}

void Player::update(std::set<SDL_Keycode> *keys) {
    // debug the keys
    if (keys->count(SDLK_RIGHT)) {
        std::cout << "moving left" << '\n';
        rect.x += speed;
    }
}

void Player::render(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

}