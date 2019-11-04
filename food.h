#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "vector.h"
#include "snake.h"

void food_draw(Vector *food);
bool food_is_empty(Vector *food);
void food_create(Vector *food, int rows, int cols, Snake *snake);
void food_destroy(Vector *food);

#endif
