#include "food.h"

Food* foods = nullptr;
const int foodInterval = 10;
int foodCounter = 0;

void addFood()
{
    Food* newFood = new Food;
    newFood->posX = rand() % W;
    newFood->posY = rand() % H;
    newFood->next = foods;
    foods = newFood;
}

void removeFood(Food* food)
{
    if (foods == food)
    {
        foods = foods->next;
    }
    else
    {
        Food* current = foods;
        while (current->next != food)
        {
            current = current->next;
        }
        current->next = food->next;
    }
    delete food;
}

void drawFoods(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    Food* current = foods;
    while (current != nullptr)
    {
        SDL_Rect rect = { current->posX * CELL_SIZE, current->posY * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderFillRect(gRenderer, &rect);
        current = current->next;
    }
}