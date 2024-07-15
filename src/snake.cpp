#include "snake.h"

Elt* snake = nullptr;
int direction = 1;
bool growSnake = false;

void createSnake()
{
    snake = new Elt;
    snake->posX = W / 2;
    snake->posY = H / 2;
    snake->next = nullptr;
}

void getOrder(SDL_Event& gEvent)
{
    if (SDL_PollEvent(&gEvent) != 0)
    {
        if (gEvent.type == SDL_QUIT || (gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_ESCAPE))
        {
            exit(0);
        }
        else if (gEvent.type == SDL_KEYDOWN)
        {
            switch (gEvent.key.keysym.sym)
            {
                case SDLK_UP:
                    if (direction != 2) direction = -2;
                    break;
                case SDLK_LEFT:
                    if (direction != 1) direction = -1;
                    break;
                case SDLK_RIGHT:
                    if (direction != -1) direction = 1;
                    break;
                case SDLK_DOWN:
                    if (direction != -2) direction = 2;
                    break;
                default:
                    break;
            }
        }
    }
}

void moveSnake()
{
    Elt* newHead = new Elt;
    newHead->posX = snake->posX + (direction == 1 ? 1 : (direction == -1 ? -1 : 0));
    newHead->posY = snake->posY + (direction == 2 ? 1 : (direction == -2 ? -1 : 0));
    newHead->next = snake;
    snake = newHead;

    if (!growSnake)
    {
        Elt* current = snake;
        Elt* prevTail = nullptr;
        while (current->next != nullptr)
        {
            prevTail = current;
            current = current->next;
        }
        if (prevTail != nullptr)
        {
            delete prevTail->next;
            prevTail->next = nullptr;
        }
    }
    else
    {
        growSnake = false;
    }
}

void checkCollision()
{
    Food* currentFood = foods;
    while (currentFood != nullptr)
    {
        if (currentFood->posX == snake->posX && currentFood->posY == snake->posY)
        {
            growSnake = true;
            removeFood(currentFood);
            return;
        }
        currentFood = currentFood->next;
    }

    Elt* currentSnakePart = snake->next;
    while (currentSnakePart != nullptr)
    {
        if (currentSnakePart->posX == snake->posX && currentSnakePart->posY == snake->posY)
        {
            exit(0);
        }
        currentSnakePart = currentSnakePart->next;
    }
}

void drawSnake(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
    Elt* currentSnakePart = snake;
    while (currentSnakePart != nullptr)
    {
        SDL_Rect rect = { currentSnakePart->posX * CELL_SIZE, currentSnakePart->posY * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderFillRect(gRenderer, &rect);
        currentSnakePart = currentSnakePart->next;
    }
}