/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <iostream>
#include <set>
#include <chrono>
#include <SDL.h>
#include "../include/player.hpp"
#include "../include/render.hpp"


int sdl_init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture_2d, SDL_Texture **texture_3d, int SCREEN_WIDTH, int SCREEN_HEIGHT, const struct Map &map);
uint64_t get_current_time(void);

void handle_events(bool *running, std::set<SDL_Keycode> *keys);
void update(Player *player, std::set<SDL_Keycode> *keys, SDL_Rect *boundaries);
void render(SDL_Renderer* renderer, SDL_Texture *texture_2d, SDL_Texture *texture_3d, Player *player, const struct Map &map);


int main(void) {

    // constant declaration
    const int FPS = 60;
    const int SCREEN_WIDTH = 1024 + 512;
    const int SCREEN_HEIGHT = 640;
    const struct Map map;
    // debug var
    bool DEBUG_FPS = false;

    // init sdl
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture_2d = nullptr;
    SDL_Texture *texture_3d = nullptr;
    if (sdl_init(&window, &renderer, &texture_2d, &texture_3d, SCREEN_WIDTH, SCREEN_HEIGHT, map)) {
        std::cout << "sdl init failed" << '\n';
        return 1;
    }

    // declare objects
    static Player player = Player(256.0, 256.0, (float)(map.TILE_SIZE/2));
    SDL_Rect boundaries = {0, 0, (map.TILE_SIZE*map.COLUMNS), (map.TILE_SIZE*map.ROWS)};
    std::set<SDL_Keycode> keys;

    // framerate limitation
    uint64_t start_time;
    uint64_t elapsed_time;
    const uint FRAME_TIME = 1000/FPS;  // in milliseconds (~16.6)

    // mainloop
    bool running = true;
    while (running) {
        start_time = get_current_time();

        handle_events(&running, &keys);
        update(&player, &keys, &boundaries);
        render(renderer, texture_2d, texture_3d, &player, map);

        // cap FPS to a max value (or a litter less FPS due to SDL_Delay aproximations)
        elapsed_time = get_current_time() - start_time;
        if (elapsed_time < FRAME_TIME) {
            SDL_Delay((uint32_t)(FRAME_TIME - elapsed_time));
        }
        // debug fps
        if (DEBUG_FPS) {
        elapsed_time = get_current_time() - start_time;
        float fps = 1000/elapsed_time;
        std::cout << fps << '\n';
        }

    }

    // quit the game
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture_2d);
    SDL_DestroyTexture(texture_3d);
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


void render(SDL_Renderer *renderer, SDL_Texture *texture_2d, SDL_Texture *texture_3d, Player *player, const struct Map &map) {
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 80, 10, 100, 255);  // deep purple
    SDL_RenderClear(renderer);

    // render in 3d
    SDL_SetRenderTarget(renderer, texture_3d);
    // yes
    SDL_SetRenderDrawColor(renderer, 100, 170, 250, 255);  // ligth blue
    SDL_RenderClear(renderer);
    render_rays(renderer, player, map);


    // render a 2D minimap
    SDL_SetRenderTarget(renderer, texture_2d);
    render_map(renderer, map);
    player->render(renderer);


    // Reset render target to the default (window)
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Rect dest_texture_2d = {
        0, 0,   // topleft
        map.TILE_SIZE*map.COLUMNS,
        map.TILE_SIZE*map.ROWS
    };
    SDL_RenderCopy(renderer, texture_2d, NULL, &dest_texture_2d);

    SDL_Rect dest_texture_3d = {
        map.TILE_SIZE*map.COLUMNS, 0,    // topleft
        map.TILE_SIZE*map.COLUMNS * 2,   // width
        map.TILE_SIZE*map.ROWS           // height
    };
    SDL_RenderCopy(renderer, texture_3d, NULL, &dest_texture_3d);


    // update the screen
    SDL_RenderPresent(renderer);
}


int sdl_init(
    SDL_Window **window,
    SDL_Renderer **renderer,
    SDL_Texture **texture_2d,
    SDL_Texture **texture_3d,
    int SCREEN_WIDTH,
    int SCREEN_HEIGHT,
    const struct Map &map
) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "sld init error : " << SDL_GetError() << '\n';
        return 1;
    }
    // declare the windows
    *window = SDL_CreateWindow(
        "Look it's 3D baby !",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0   // flag
    );
    if (*window == NULL) {
        std::cout << "windows creation failed" << SDL_GetError() << '\n';
        return 1;
    }
    // declare the renderer (wtf is that :cry:)
    *renderer = SDL_CreateRenderer(
        *window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (*renderer == NULL) {
        std::cout << "renderer creation failed" << SDL_GetError() << '\n';
        return 1;
    }
    // declare the textures (targets for the renderer)
    *texture_2d = SDL_CreateTexture(
        *renderer,
        SDL_PIXELFORMAT_RGBA4444,  // pixel format, 4 bits range from 0 to 255.
        SDL_TEXTUREACCESS_TARGET,  // texture acces, ot be a target for the renderer
        map.TILE_SIZE*map.COLUMNS,
        map.TILE_SIZE*map.ROWS
    );
    if (*texture_2d == NULL) {
        std::cout << "texture_2d creation failed" << SDL_GetError() << '\n';
        return 1;
    }
    *texture_3d = SDL_CreateTexture(
        *renderer,
        SDL_PIXELFORMAT_RGBA4444,  // pixel format, 4 bits range from 0 to 255.
        SDL_TEXTUREACCESS_TARGET,  // texture acces, ot be a target for the renderer
        map.TILE_SIZE*map.COLUMNS * 2,
        map.TILE_SIZE*map.ROWS
    );
    if (*texture_3d == NULL) {
        std::cout << "texture_3d creation failed" << SDL_GetError() << '\n';
        return 1;
    }

    return 0;
}


uint64_t get_current_time(void) {
    uint64_t time_now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    return time_now;
}