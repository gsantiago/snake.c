#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "vector.h"

typedef struct {
  int size;
  Vector speed;
  Vector *cells;
  Vector last;
} Snake;

typedef enum {
  UP,
  LEFT,
  RIGHT,
  DOWN
} Direction;

void snake_create(Snake *snake, int rows, int cols);
void snake_draw(Snake *snake);
void snake_move(Snake *snake);
bool snake_collides(Snake *snake, Vector *point);
void snake_increase(Snake *snake);
void snake_set_direction(Snake *snake, Direction direction);
bool snake_collides_to_borders(Snake *snake, int rows, int cols);
bool snake_collides_to_itself(Snake *snake);
void snake_reset(Snake *snake, int rows, int cols);
bool snake_is_vertical(Snake *snake);
bool snake_is_horizontal(Snake *snake);

#endif
