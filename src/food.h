#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <SDL2/SDL.h>

#define W 40
#define H 25
#define CELL_SIZE 20


struct Food
{
    int posX;
    int posY;
    Food* next;
};

extern Food* foods;
extern const int foodInterval;
extern int foodCounter;

void addFood();
void removeFood(Food* food);
void drawFoods(SDL_Renderer* gRenderer);

#endif