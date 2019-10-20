#include "Star.hpp"
#include <ncurses.h>

void Star::start()
{
	
}

void Star::update()
{
  mvaddch(hauteur, COLS - reset, '+');
  reset += speed;
  if (reset > COLS)
  {
    speed = (rand() % 3) + 1;
    reset = 0;
    hauteur = rand() % LINES;
  }
}

void Star::set(int p_hauteur, int p_speed)
{
    hauteur = p_hauteur;
    speed = p_speed;
}
