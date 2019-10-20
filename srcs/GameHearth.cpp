#include "GameHearth.hpp"
#include <ncurses.h>
#include "Point.hpp"
#include <cstdlib>
#include "GameEntity.hpp"
#include "KillPlayer.hpp"
#include "RenderBehavior.hpp"
#include "DirectionalBehavior.hpp"
#include "utils.hpp"
#include "Scene.hpp"
#include "EnemyBehavior.hpp"
#include <fstream>

// METEOR
static const Point g_meteorPoints[] = {
	Point(-2, -2, '/'),Point(-2, -1, '-'),	Point(2, 0, '-'),	Point(-2, 1, '-'),	Point(-2, 2, '\\'),
	Point(-1, -2, '|'),Point(-1, -1, ' '),	Point(1, 0, ' '),	Point(-1, 1, 'o'),	Point(-1, 2, '|'),
	Point(0, -2, '|'),Point(0, -1, ' '), Point(0, 0, ' '), Point(0, 1, ' '),	Point(-0, 2, '|'),
	Point(1, -2, '|'),Point(1, -1, ' '), Point(-1, 0, ' '),	Point(1, 1, ' '),	Point(1, 2, '|'),
	Point(2, -2, '\\'),Point(2, -1, '-'), Point(-2, 0, '-'), Point(2, 1, '-'),	Point(2, 2, '/'),
};

// SPACESHIP
static const Point g_spaceShipsPoints[] = {
	Point(-2, -1, ' '),	Point(-2, 0, '/'),	Point(-2, 1, ' '), Point(-2, 2, ' '),
	Point(-1, -1, '/'),	Point(-1, 0, '-'),	Point(-1, 1, '-'), Point(-1, 2, '/'),
	Point(0, -1, '\\'), Point(0, 0, '-'), Point(0, 1, '-'), Point(0, 2, '\\'),
	Point(1, -1, ' '), Point(1, 0, '\\'),	Point(1, 1, ' '), Point(1, 2, ' ')
};

// RUNNER
static const Point g_runnerPoints[] = {
	Point(-2, -1, '\\'),	Point(-2, 0, '\\'),	Point(-2, 1, ' '),
	Point(-1, -1, '/'),	Point(-1, 0, '\\'),	Point(-1, 1, '\\'),
	Point(0, -1, '<'), Point(0, 0, '-'), Point(0, 1, '-'), Point(0, 2, '-'),
	Point(1, -1, '\\'), Point(1, 0, 'o'),	Point(1, 1, '-'), Point(1, 2, 'o')
};

// BONUS
static const Point g_bonusPoints[] =
{
	Point(-1, -1, '/'),	Point(-1, 0, '-'),	Point(-1, 1, '\\'),
	Point(0, -1, '|'), Point(0, 0, '+'), Point(0, 1, '|'),
	Point(1, -1, '\\'), Point(1, 0, '-'),	Point(1, 1, '/'),
};


void GameHearth::update()
{
	static int i = 0;

	int randEnemy;
	if(1 == rand() % 60)
	{
		randEnemy = rand() % 4;
		GameEntity *enemy = new GameEntity(rand() % LINES, COLS + 10);
		KillPlayer *kp = enemy->addBehavior<KillPlayer>();
		kp->set(10);
		if (randEnemy == 0)
		{
			enemy->addBehavior<DirectionalBehavior>()->set(-3, 0, true);
			enemy->addBehavior<RenderBehavior>()->set(g_meteorPoints, TAB_SIZE(g_meteorPoints), 2);
		}
		else if (randEnemy == 1)
		{
			enemy->addBehavior<EnemyBehavior>()->set(-2, 0);
			enemy->addBehavior<DirectionalBehavior>()->set(-1, 0, true);
			enemy->addBehavior<RenderBehavior>()->set(g_spaceShipsPoints, TAB_SIZE(g_spaceShipsPoints), 1);
		}
		else if (randEnemy == 2)
		{
			enemy->setX(LINES - 2);
			enemy->addBehavior<EnemyBehavior>()->set(-2, -2);
			enemy->addBehavior<DirectionalBehavior>()->set(-1, 0, true);
			enemy->addBehavior<RenderBehavior>()->set(g_runnerPoints, TAB_SIZE(g_runnerPoints), 3);
		}
		else if (randEnemy == 3)
		{
			kp->set(20);
			enemy->addBehavior<EnemyBehavior>()->set(-2, 0);
			enemy->addBehavior<DirectionalBehavior>()->set(-1, -1, false);
			enemy->addBehavior<RenderBehavior>()->set(g_spaceShipsPoints, TAB_SIZE(g_spaceShipsPoints), 1);
		}
		entity()->scene()->addEntity("ent" + toString(i++), enemy);
	}
}
