#include "InterfaceBehavior.hpp"
#include <ncurses.h>
#include "Scene.hpp"
#include "GameEntity.hpp"

void InterfaceBehavior::start()
{
	lives = 0;
	score = 0;
}

void InterfaceBehavior::update()
{
	mvprintw(entity()->y(), entity()->x(), "Score : %d", this->score);
	mvprintw(entity()->y() + 1, entity()->x(), "lives : %d", this->lives);
	mvprintw(entity()->y() + 2, entity()->x(), "elapsed : %d sec", entity()->scene()->elapsedTime());
}
