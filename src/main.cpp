/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <iostream>
#include <SDL.h>
#include "../include/player.hpp"


void update(void);
void render(SDL_Renderer* renderer, Player *player);


int main(void) {

    // constant declaration
    const int TILE_SIZE = 32;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "sld init error : " << SDL_GetError() << '\n';
        return 1;
    }

    // declare the windows
    SDL_Window *window = SDL_CreateWindow(
        "Hi i guess ?",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        0
    );
    if (window == NULL) {
        std::cout << "windows creation failed" << SDL_GetError() << '\n';
        return 1;
    }

    // declare the renderer (wtf is that :cry:)
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (renderer == NULL) {
        std::cout << "renderer creation failed" << SDL_GetError() << '\n';
        return 1;
    }

    Player player = Player(0, 0, TILE_SIZE);

    bool running = true;

    // mainloop
    while (running) {
        update();
        render(renderer, &player);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


void update(void) {
    // no
}


void render(SDL_Renderer *renderer, Player *player) {
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player->render(renderer);

    // update the screen
    SDL_RenderPresent(renderer);
    SDL_Delay(16);   // almost 60 FPS

}
