#include "EnemyBehavior.hpp"
#include <ctime>
#include "GameEntity.hpp"
#include "KillPlayer.hpp"
#include "RenderBehavior.hpp"
#include "utils.hpp"
#include "Scene.hpp"

static const Point g_points[] = {
	Point(0, 0, '<'), Point(0, 1, '='),
};

void EnemyBehavior::start()
{
	time(&this->_lastTime);
	this->_db = entity()->getBehavior<DirectionalBehavior>();
}

void EnemyBehavior::update()
{
	static int i = 0;
	time_t newTime;
	std::time(&newTime);

	if (newTime - this->_lastTime >= 2)
	{
		this->_lastTime = newTime;
		GameEntity *dot = new GameEntity(entity()->x(), entity()->y());
		dot->addBehavior<KillPlayer>();
		dot->addBehavior<DirectionalBehavior>()->set(this->_db->yVelocity + this->yVelocity, this->xVelocity, true);
		dot->addBehavior<RenderBehavior>()->set(g_points, TAB_SIZE(g_points),
												entity()->getBehavior<RenderBehavior>()->colorIndex());
		entity()->scene()->addEntity("enemyShoot" + toString(i++), dot);
	}
}

void EnemyBehavior::set(const int &p_yVelocity, const int &p_xVelocity)
{
	this->xVelocity = p_xVelocity;
	this->yVelocity = p_yVelocity;
}
