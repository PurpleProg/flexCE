#include "../include/player.hpp"


Player::Player(int startx, int starty, int size) {
    rect = {startx, starty, size, size};
}

void Player::update(void) {
    // haaaaaaaaaaaaaaaaaaaaaaaaaaaa
}

void Player::render(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

}