#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "baseObject.h"


using namespace std;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen= NULL;
static SDL_Event g_event;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_money_sound;

static Mix_Music *g_background_music;
// Screen

const int FRAME_PER_SECOND = 28; // fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

static SDL_Surface* g_img_menu = NULL;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4
#define STATE_FLAG 10
typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Renderer* screen, TTF_Font* font);
    SDL_Surface* LoadImage(std::string file_path);
    bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
    int ShowMenuOver(SDL_Renderer* screen, TTF_Font* font, TTF_Font* font_mark, int total_mark, int current_mark);
}

#endif
