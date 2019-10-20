#include <ncurses.h>
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h>

#include "GameEntity.hpp"
#include "Behavior.hpp"
#include "Scene.hpp"
#include "CanonicalForm.hpp"
#include "Star.hpp"

/*******************************************************************************/

/*void DrawEnemy (Enemy enemy, Hero perso)
{
  for(int i = 0; i < enemy.tabPosSize() ; i++;)
  {
    mvaddch(enemy.getPosx(i), enemy.getPosy(i), enemy.getSymb(i));
    for(int j = 0; j < perso.tabPosSize() ; j++;)
    {
      if(enemy.getPosx(i) == perso.getPosx(j) && enemy.getPosy(i) == perso.getPosy(j))
      {
        perso.isDead();
      }
  }
}
}

void Update(Scene &scene)
{
  clear();
************************
//  DrawHero(a);
	scene.update();
  //EnemySpawn();                                 // RANDOM SPAWN Enemy
//  for(int i = 0; i < nbrEnemy; i++)               //iteration pour actualier les deplacement/tir de chaque ennemy
  //  UpdateEnemy(Enemy enemy[i], Hero perso );
//  DrawEnemy();
************************
//  Interface();
  noecho();
}
*/

// THE PLAYER SHAPE
static const Point g_playerPoints[] = {
	Point(1, 1, '/'),	Point(0, 1, '-'),	Point(-1, 1, '\\'),
	Point(1, 0, '-'),	Point(0, 0, '-'),	Point(-1, 0, '-'),
	Point(0, 2, '>'), Point(0, -2, '3'), Point(0, -3, '~'),
	Point(1, -1, '\\'), Point(0, -1, '-'),	Point(-1, -1, '/'),
	Point(-2, 1, '/'), Point(-2, 2, '-'), Point(2, 1, '\\'),
	Point(2, 2, '-'),
};
static const int g_playerPointsSize = 16;

static const Point g_points[] = {
	Point(0, 0, '*')
};
static const int g_pointsSize = 1;

class DirectionalBehavior : public Behavior
{
public:
	void start()
	{
		this->velocity = 0;
	}

	void update()
	{
		entity()->setY(entity()->y() + this->velocity);
	}

	int velocity;
};

class RenderBehavior: public Behavior
{
public:
	void update()
	{
		for (int i = 0; i < this->_pointsSize; ++i)
		{
			mvaddch(entity()->x() + this->_points[i].x(),
					entity()->y() + this->_points[i].y(),
					this->_points[i].c());
		}
	}

	void setPoints(const Point *p_points, const int &p_pointsSize)
	{
		this->_points = p_points;
		this->_pointsSize = p_pointsSize;
	}

	bool collidesWith(const RenderBehavior *p_other) const
	{
		for (int i = 0; i < this->_pointsSize; ++i)
			for (int j = 0; j < p_other->_pointsSize; ++j)
				if (entity()->x() + this->_points[i].x() == p_other->entity()->x() + p_other->_points[i].x()
						|| entity()->y() + this->_points[i].y() == p_other->entity()->y() + p_other->_points[i].y())
					return true;
		return false;
	}

	CANONICALFORM(RenderBehavior)

private:
	const Point *_points;
	int _pointsSize;
};

class InputBehavior: public Behavior
{
public:
	InputBehavior()
	{}

	void update()
	{
		char c = getch();
		if('a' == c)
			entity()->setY(entity()->y() - 2);
		if('d' == c)
			entity()->setY(entity()->y() + 2);
		if('w' == c)
			entity()->setX(entity()->x() - 2);
		if('s' == c)
			entity()->setX(entity()->x() + 2);

		if (c == 'h')
			entity()->scene()->setUnactive();

		if (c == 'o')
		{
			GameEntity *dot = new GameEntity(entity()->x(), entity()->y());
			dot->addBehavior<DirectionalBehavior>()->velocity = (rand() % 4) + 10;
			dot->addBehavior<RenderBehavior>()->setPoints(g_points, g_pointsSize);

			entity()->scene()->addEntity(dot);
		}
	}

	CANONICALFORM2(InputBehavior)
};

class InterfaceBehavior: public Behavior
{
public:
	void update()
	{
		mvprintw(entity()->y(), entity()->x(), "Score : %d", 150); // you use it like printf
		mvprintw(entity()->y() + 1, entity()->x(), "lives : %d", 3);
		mvprintw(entity()->y() + 2, entity()->x(), "entities : %d", entity()->scene()->entities().size());
	}
};

class BackgroundBehavior : public Behavior
{
	int i;
	int j;
	int h;

public:
	void start()
	{
		i = 0;
		j = 0;
		h = 0;
	}

	void update()
	{
		i++;
		if ( i > COLS )
			i = 0;
		j += 2;
		if ( j > COLS )           //Background
			j = 0;
		h += 3;
		if ( h > COLS )
			h = 0;

		mvaddch(10, COLS - i, '*');
		mvaddch(40, COLS - j, '*');                   //NEED RANDOM SPAWN
		mvaddch(20, COLS - h, '*');
	}

	CANONICALFORM(BackgroundBehavior)
};

int main(void)
{
// EXAMPLE:
	Scene scene;
	time_t ptr;
	std::srand(std::time(&ptr));

	GameEntity *a = new GameEntity(10, 10);
	a->addBehavior<InputBehavior>(); // ONLY THE PLAYER(S) WILL HAVE THIS BEHAVIOR
	a->addBehavior<RenderBehavior>()
		->setPoints(g_playerPoints, g_playerPointsSize); // EVERY ENTITY WILL HAVE THIS ONE

	GameEntity *interface = new GameEntity(2, 2);
	interface->addBehavior<InterfaceBehavior>();

	GameEntity *star1 = new GameEntity(0, 0);
	star1->addBehavior<Star>()->set(5, 1);
	GameEntity *star2 = new GameEntity(0, 0);
	star2->addBehavior<Star>()->set(10, 2);
	GameEntity *star3 = new GameEntity(0, 0);
	star3->addBehavior<Star>()->set(15, 3);
	GameEntity *star4 = new GameEntity(0, 0);
	star4->addBehavior<Star>()->set(25, 1);
	GameEntity *star5 = new GameEntity(0, 0);
	star5->addBehavior<Star>()->set(30, 4);

	scene.addEntity(star1);
	scene.addEntity(star2);
	scene.addEntity(star3);
	scene.addEntity(star4);
	scene.addEntity(star5);

	scene.addEntity(a);
	scene.addEntity(interface);

	scene.start();
	while(scene.isActive())
	{
		scene.update();
		usleep(20000);
	}
	return 0;
}
