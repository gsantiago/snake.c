#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncursesw/ncurses.h>
#include "snake.h"

void snake_create(Snake *snake, int rows, int cols)
{
  snake->size = 10;
  snake->speed.x = 0;
  snake->speed.y = 1;
  snake->cells = malloc(sizeof(Vector) * snake->size);

  for (int i = 0; i < snake->size; i++) {
    snake->cells[i] = (Vector){ cols / 2, rows / 2 - i };
  }
}

void snake_draw(Snake *snake)
{
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(1));

  for (int i = 0; i < snake->size; i++) {
    mvaddch(snake->cells[i].y, snake->cells[i].x, ACS_CKBOARD);
  }

  mvprintw(snake->last.y, snake->last.x, " ");

  attroff(COLOR_PAIR(1));
}

void snake_move(Snake *snake)
{
  snake->last.x = snake->cells[snake->size - 1].x;
  snake->last.y = snake->cells[snake->size - 1].y;

  for (int i = snake->size - 1; i > 0; i--) {
    snake->cells[i].x = snake->cells[i - 1].x;
    snake->cells[i].y = snake->cells[i - 1].y;
  }

  snake->cells[0].x += snake->speed.x;
  snake->cells[0].y += snake->speed.y;
}

bool snake_collides(Snake *snake, Vector *point)
{
  return snake->cells[0].x == point->x && snake->cells[0].y == point->y;
}

void snake_increase(Snake *snake)
{
  snake->cells = realloc(snake->cells, sizeof(Vector) * ++snake->size);
  snake->cells[snake->size - 1].x = snake->last.x;
  snake->cells[snake->size - 1].y = snake->last.y;
}

void snake_set_direction(Snake *snake, Direction direction)
{
  switch (direction) {
    case UP:
      if (snake_is_horizontal(snake)) {
        snake->speed.x = 0;
        snake->speed.y = -1;
      }
      break;
    case DOWN:
      if (snake_is_horizontal(snake)) {
        snake->speed.x = 0;
        snake->speed.y = 1;
      }
      break;
    case LEFT:
      if (snake_is_vertical(snake)) {
        snake->speed.x = -1;
        snake->speed.y = 0;
      }
      break;
    case RIGHT:
      if (snake_is_vertical(snake)) {
        snake->speed.x = 1;
        snake->speed.y = 0;
      }
      break;
    default:
      printf("Invalid given direction");
      exit(1);
  }
}

bool snake_collides_to_borders(Snake *snake, int rows, int cols)
{
  int x = snake->cells[0].x;
  int y = snake->cells[0].y;

  return y < 1 || y >= rows - 1 || x < 1 || x >= cols;
}

bool snake_collides_to_itself(Snake *snake)
{
  for (int i = 1; i < snake->size; i++) {
    if (snake_collides(snake, &snake->cells[i])) {
      return true;
    }
  }

  return false;
}

void snake_reset(Snake *snake, int rows, int cols) {
  free(snake->cells);
  snake_create(snake, rows, cols);
}

bool snake_is_vertical(Snake *snake)
{
  return snake->speed.y != 0;
}

bool snake_is_horizontal(Snake *snake)
{
  return snake->speed.x != 0;
}
