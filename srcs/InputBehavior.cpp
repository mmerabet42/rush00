#include "InputBehavior.hpp"
#include <ncurses.h>
#include "GameEntity.hpp"
#include "Scene.hpp"
#include "DirectionalBehavior.hpp"
#include "RenderBehavior.hpp"
#include "utils.hpp"

InputBehavior::InputBehavior()
{
	this->set('w', 's', 'a', 'd', ' ');
}

static const Point g_points[] = {
	Point(0, 0, '*')
};

void InputBehavior::update()
{
	static int i = 0;

	char c = getch();
	if(c == this->_left)
		entity()->setY(entity()->y() - 2);
	if(c == this->_right)
		entity()->setY(entity()->y() + 2);
	if(c == this->_up)
		entity()->setX(entity()->x() - 2);
	if(c == this->_down)
		entity()->setX(entity()->x() + 2);

	if (c == 'h')
		entity()->scene()->setUnactive();

	if (c == 'o' && entity()->scene()->getEntity("Player") == entity())
	{
		GameEntity *dot = new GameEntity(entity()->x(), entity()->y());
		dot->addBehavior<DirectionalBehavior>()->velocity = (rand() % 4) + 10;
		dot->addBehavior<RenderBehavior>()->set(g_points, TAB_SIZE(g_points));

		entity()->scene()->addEntity("dot" + toString(i++), dot);
	}
}

void InputBehavior::set(const int &p_up, const int &p_down, const int &p_left, const int &p_right, const int &p_fire)
{
	this->_up = p_up;
	this->_down = p_down;
	this->_left = p_left;
	this->_right = p_right;
	this->_fire = p_fire;
}
