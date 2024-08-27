/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <iostream>
#include <set>
#include <SDL.h>
#include "../include/player.hpp"


void handle_events(bool *running, std::set<SDL_Keycode> *keys);
void update(Player *player, std::set<SDL_Keycode> *keys, SDL_Rect *boundaries);
void render(SDL_Renderer* main_renderer, Player *player);


int main(void) {

    // constant declaration
    const int TILE_SIZE = 32;
    const int FPS = 60;
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 640;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "sld init error : " << SDL_GetError() << '\n';
        return 1;
    }

    // declare the windows
    SDL_Window *window = SDL_CreateWindow(
        "Hi i guess ?",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0   // flag
    );
    if (window == NULL) {
        std::cout << "windows creation failed" << SDL_GetError() << '\n';
        return 1;
    }

    // declare the main_renderer (wtf is that :cry:)
    SDL_Renderer *main_renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (main_renderer == NULL) {
        std::cout << "main_renderer creation failed" << SDL_GetError() << '\n';
        return 1;
    }

    static Player player = Player(5.0, 5.0, (float)TILE_SIZE);
    std::set<SDL_Keycode> keys;
    bool running = true;

    SDL_Rect boundaries = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // mainloop
    while (running) {
        handle_events(&running, &keys);
        update(&player, &keys, &boundaries);
        render(main_renderer, &player);
    }

    // quit the game
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


void handle_events(bool *running, std::set<SDL_Keycode> *keys) {
    // gather keypress in a set (keys)
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        *running = false;
                        break;
                    case SDLK_RIGHT:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_LEFT:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_UP:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_DOWN:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_a:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_w:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_s:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_d:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_RSHIFT:
                        keys->insert(event.key.keysym.sym);
                        break;
                    case SDLK_LSHIFT:
                        keys->insert(event.key.keysym.sym);
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_LEFT:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_UP:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_DOWN:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_a:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_w:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_s:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_d:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_RSHIFT:
                        keys->erase(event.key.keysym.sym);
                        break;
                    case SDLK_LSHIFT:
                        keys->erase(event.key.keysym.sym);
                        break;
                }
                break;
        }
    }
}


void update(Player *player, std::set<SDL_Keycode> *keys, SDL_Rect *boundaries) {
    player->update(keys, boundaries);
}


void render(SDL_Renderer *main_renderer, Player *player) {
    // clear the screen
    SDL_SetRenderDrawColor(main_renderer, 80, 10, 100, 255);  // deep purple
    SDL_RenderClear(main_renderer);

    player->render(main_renderer);

    // update the screen
    SDL_RenderPresent(main_renderer);
}
