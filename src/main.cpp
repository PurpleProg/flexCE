/*
flexCE is a wolfenstein3D-like raycasting "game"
writen in C++ with SDL, it aim to be ported to the TI83 Premium CE (not hapenning soon).
*/

#include <iostream>
#include <set>
#include <chrono>
#include <SDL.h>
#include "../include/player.hpp"


int sdl_init(SDL_Window **window, SDL_Renderer **main_renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void handle_events(bool *running, std::set<SDL_Keycode> *keys);
void update(Player *player, std::set<SDL_Keycode> *keys, SDL_Rect *boundaries);
void render(SDL_Renderer* main_renderer, Player *player, const struct Map &map);
void render_map(SDL_Renderer *main_renderer, const struct Map &map);
uint64_t get_current_time(void);



struct Map {
    static constexpr int TILE_SIZE = 32;
    static constexpr int MAP_ROWS = 20;
    static constexpr int MAP_COLUMNS = 16;
    static constexpr bool DATA[MAP_ROWS][MAP_COLUMNS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    };
};


int main(void) {

    // constant declaration
    const int FPS = 60;
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 640;
    const struct Map map;
    // debug var
    bool DEBUG_FPS = false;

    // init sdl
    SDL_Window *window = nullptr;
    SDL_Renderer *main_renderer = nullptr;
    if (sdl_init(&window, &main_renderer, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cout << "sdl init failed" << '\n';
        return 1;
    }

    // declare objects
    static Player player = Player(5.0, 5.0, (float)(map.TILE_SIZE/2));
    SDL_Rect boundaries = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
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
        render(main_renderer, &player, map);

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


void render(SDL_Renderer *main_renderer, Player *player, const struct Map &map) {
    // clear the screen
    SDL_SetRenderDrawColor(main_renderer, 80, 10, 100, 255);  // deep purple
    SDL_RenderClear(main_renderer);

    render_map(main_renderer, map);
    player->render(main_renderer);

    // update the screen
    SDL_RenderPresent(main_renderer);
}


void render_map(SDL_Renderer *main_renderer, const struct Map &map) {
    for (int row_index = 0; row_index < map.MAP_ROWS; row_index++) {
        for (int column_index = 0; column_index < map.MAP_COLUMNS; column_index++) {
            if (map.DATA[row_index][column_index]) {
                SDL_SetRenderDrawColor(main_renderer, 0, 0, 255, 255); // tile are blue
            } else {
                SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0); // transparent
            }
            SDL_Rect tile_rect = {
                column_index*map.TILE_SIZE,
                row_index*map.TILE_SIZE,
                map.TILE_SIZE, map.TILE_SIZE
            };
            SDL_RenderFillRect(main_renderer, &tile_rect);
        }
    }
}


int sdl_init(SDL_Window **window, SDL_Renderer **main_renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
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
    // declare the main_renderer (wtf is that :cry:)
    *main_renderer = SDL_CreateRenderer(
        *window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (*main_renderer == NULL) {
        std::cout << "main_renderer creation failed" << SDL_GetError() << '\n';
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