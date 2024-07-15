#include <iostream>
#include <time.h>
#include <SDL2/SDL.h>
#include "snake.h"
#include "food.h"

#define W 40
#define H 25
#define CELL_SIZE 20

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Event gEvent;

void initSDL();
void quitSDL();
void clearScreen();

int main(int argc, char* args[])
{
    srand(static_cast<unsigned int>(time(NULL)));

    initSDL();
    createSnake();

    bool running = true;
    while (running)
    {
        getOrder(gEvent);
        moveSnake();
        checkCollision();

        clearScreen();
        drawFoods(gRenderer);
        drawSnake(gRenderer);
        SDL_RenderPresent(gRenderer);

        SDL_Delay(100);

        if (snake->posX < 0 || snake->posX >= W || snake->posY < 0 || snake->posY >= H)
        {
            running = false;
        }

        foodCounter++;
        if (foodCounter >= foodInterval)
        {
            foodCounter = 0;
            addFood();
        }
    }

    quitSDL();
    return 0;
}

void initSDL()
{
    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              W * CELL_SIZE, H * CELL_SIZE, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void quitSDL()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


void clearScreen()
{
    SDL_SetRenderDrawColor(gRenderer, 25, 25, 25, 25); // White
    SDL_RenderClear(gRenderer);
}