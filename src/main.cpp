/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <iostream>
#include <SDL.h>


void update(void);
void render(void);


int main(void) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "sld init error : " << SDL_GetError() << '\n';
        return 1;
    }

    // declare the windows
    SDL_Window* window = SDL_CreateWindow(
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

    // declare the renderer (wtf is this :cry:)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "renderer creation failed" << SDL_GetError() << '\n';
        return 1;
    }



    // copy past im just testing
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000); // Wait for 2 seconds

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    // end copied

    bool running = false;

    // mainloop
    while (running) {
        update();
        render();
    }

    return 0;
}


void update(void) {
    // no
}


void render(void) {
    // pass
}
