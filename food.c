#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include "food.h"
#include "snake.h"

void food_draw(Vector *food)
{
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    mvaddch(food->y, food->x, ACS_DIAMOND);
    attroff(COLOR_PAIR(2));
}

bool food_is_empty(Vector *food)
{
  return food->x == 0 && food->y == 0;
}

void food_create(Vector *food, int rows, int cols, Snake *snake)
{
  int x, y;

  x = rand() % ((cols - 1) - 1) + 1;
  y = rand() % ((rows - 1) - 1) + 1;

  for (int i = 0; i < snake->size; i++) {
    if (snake->cells[i].x == x && snake->cells[i].y == y) {
      return food_create(food, rows, cols, snake);
    }
  }

  food->x = x;
  food->y = y;
}

void food_destroy(Vector *food)
{
  food->x = 0;
  food->y = 0;
}
