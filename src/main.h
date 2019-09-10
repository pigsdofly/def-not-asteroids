#ifndef main_h
#define main_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cmath>
#define MAX_BULLETS 10

bool init();
void close();

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

enum keys {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif
