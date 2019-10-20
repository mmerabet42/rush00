#include "DirectionalBehavior.hpp"
#include "GameEntity.hpp"

void DirectionalBehavior::start()
{
	this->velocity = 0;
}

void DirectionalBehavior::update()
{
	entity()->setY(entity()->y() + this->velocity);
}
