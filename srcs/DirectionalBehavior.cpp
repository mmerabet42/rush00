#include "DirectionalBehavior.hpp"
#include "GameEntity.hpp"
#include <ncurses.h>
#include "Scene.hpp"

DirectionalBehavior::DirectionalBehavior()
	: deleteAtExit(false), yVelocity(0), xVelocity(0)
{}

void DirectionalBehavior::update()
{
	entity()->setPos(entity()->x() + this->xVelocity,
					 entity()->y() + this->yVelocity);

	if (this->deleteAtExit)
	{
		if (entity()->x() < -10 || entity()->x() > LINES + 10 || entity()->y() < -10 || entity()->y() > COLS + 10)
			entity()->scene()->destroy(entity());
	}
	else
	{
		if (entity()->x() < -2)
			this->xVelocity = -this->xVelocity;
		if (entity()->x() > LINES - 2)
			this->xVelocity = -this->xVelocity;

		if (entity()->y() < -10)
			entity()->scene()->destroy(entity());
	}
}

void DirectionalBehavior::set(const int &p_yVelocity, const int &p_xVelocity, const bool &p_deleteAtExit)
{
	this->xVelocity = p_xVelocity;
	this->yVelocity = p_yVelocity;
	this->deleteAtExit = p_deleteAtExit;
}
