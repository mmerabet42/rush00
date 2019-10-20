#include "KillPlayer.hpp"
#include "GameEntity.hpp"
#include "Scene.hpp"
#include <fstream>
#include <string>

void KillPlayer::start()
{
	this->_renderBehavior = entity()->getBehavior<RenderBehavior>();
	this->_playerBehavior = entity()->scene()->player()->getBehavior<RenderBehavior>();
}

void KillPlayer::update()
{
	if (this->_renderBehavior->collidesWith(this->_playerBehavior))
	{
		entity()->scene()->destroy(entity()->scene()->player());
		this->_playerBehavior = nullptr;
	}
}
