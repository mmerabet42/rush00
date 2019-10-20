#include "KillPlayer.hpp"
#include "GameEntity.hpp"
#include "Scene.hpp"
#include <fstream>
#include <string>
#include <ncurses.h>

void KillPlayer::start()
{
	this->_renderBehavior = entity()->getBehavior<RenderBehavior>();
	this->_playerBehavior = nullptr;
	if (entity()->scene()->player())
		this->_playerBehavior = entity()->scene()->player()->getBehavior<RenderBehavior>();
}

void KillPlayer::update()
{
	if (this->_renderBehavior->collidesWith(this->_playerBehavior))
	{
		entity()->scene()->destroy(entity()->scene()->player());
		entity()->scene()->setUnactive();
		this->_playerBehavior = nullptr;
	}
}

void KillPlayer::set(const int &p_score)
{
	this->score = p_score;
}
