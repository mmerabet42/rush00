#include "InterfaceBehavior.hpp"
#include <ncurses.h>
#include "Scene.hpp"
#include "GameEntity.hpp"

void InterfaceBehavior::start()
{
	lives = 0;
	scores = 0;
}

void InterfaceBehavior::update()
{
	mvprintw(entity()->y(), entity()->x(), "Score : %d", this->scores);
	mvprintw(entity()->y() + 1, entity()->x(), "lives : %d", this->lives);
	mvprintw(entity()->y() + 2, entity()->x(), "entities : %d", entity()->scene()->entities().size());
	mvprintw(entity()->y() + 3, entity()->x(), "last : %s", entity()->scene()->entities().last()->value().b()->name().c_str());
}
