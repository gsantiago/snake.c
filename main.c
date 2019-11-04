#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ncursesw/ncurses.h>
#include "vector.h"
#include "snake.h"
#include "food.h"

void draw_window_border();
void delay(int milliseconds);

int main()
{
  int cols;
  int rows;
  int ch;
  Vector food = { 0, 0 };
  Snake snake;

  srand(time(NULL));

  initscr();
  getmaxyx(stdscr, rows, cols);
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  start_color();

  snake_create(&snake, rows, cols);
  draw_window_border();

  while ((ch = getch()) != KEY_F(1)) {
    switch (ch) {
      case KEY_UP: snake_set_direction(&snake, UP); break;
      case KEY_DOWN: snake_set_direction(&snake, DOWN); break;
      case KEY_LEFT: snake_set_direction(&snake, LEFT); break;
      case KEY_RIGHT: snake_set_direction(&snake, RIGHT); break;
    }

    if (food_is_empty(&food)) {
      food_create(&food, rows, cols, &snake);
    }

    snake_move(&snake);
    snake_draw(&snake);
    food_draw(&food);

    if (snake_collides(&snake, &food)) {
      food_destroy(&food);
      snake_increase(&snake);
    }

    if (snake_collides_to_borders(&snake, rows, cols) || snake_collides_to_itself(&snake)) {
      erase();
      snake_reset(&snake, rows, cols);
      food_destroy(&food);
      draw_window_border();
    }

    delay(40);
  }

  refresh();

  endwin();

  return 0;
}

void draw_window_border()
{
  wborder(
    stdscr,
    ACS_VLINE, // left
    ACS_VLINE, // right
    ACS_HLINE, // top
    ACS_HLINE, // bottom side
    ACS_ULCORNER, // top left
    ACS_URCORNER, // top right
    ACS_LLCORNER, // bottom left
    ACS_LRCORNER // bottom right
  );
}

void delay(int milliseconds)
{
  struct timespec t = { 0, 1000000 * milliseconds };
  nanosleep(&t, NULL);
}
