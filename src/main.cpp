/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <iostream>
#include <set>
#include <SDL.h>
#include "../include/player.hpp"


void handle_events(bool *running, std::set<SDL_Keycode> *keys);
void update(std::set<SDL_Keycode> *keys, Player *player);
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

    static Player player = Player(0, 0, TILE_SIZE);
    std::set<SDL_Keycode> keys;
    bool running = true;

    // mainloop
    while (running) {
        handle_events(&running, &keys);
        update(&keys, &player);
        render(renderer, &player);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


void handle_events(bool *running, std::set<SDL_Keycode> *keys) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        *running = false;
                    case SDLK_RIGHT:
                        keys->insert(event.key.keysym.sym);
                    case SDLK_LEFT:
                        keys->insert(event.key.keysym.sym);
                    case SDLK_UP:
                        keys->insert(event.key.keysym.sym);
                    case SDLK_DOWN:
                        keys->insert(event.key.keysym.sym);
                }
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        keys->erase(event.key.keysym.sym);
                    case SDLK_LEFT:
                        keys->erase(event.key.keysym.sym);
                    case SDLK_UP:
                        keys->erase(event.key.keysym.sym);
                    case SDLK_DOWN:
                        keys->erase(event.key.keysym.sym);
                }
        }
    }
}


void update(std::set<SDL_Keycode> *keys, Player *player) {
    player->update(keys);
}


void render(SDL_Renderer *renderer, Player *player) {
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player->render(renderer);

    // update the screen
    SDL_RenderPresent(renderer);
}
