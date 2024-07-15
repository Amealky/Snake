#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "food.h"


struct Elt
{
    int posX;
    int posY;
    Elt* next;
};

extern Elt* snake;
extern int direction;
extern bool growSnake;

void createSnake();
void getOrder(SDL_Event& gEvent);
void moveSnake();
void checkCollision();
void drawSnake(SDL_Renderer* gRenderer);

#endif