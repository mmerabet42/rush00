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
#include "utils.hpp"

void boucle(Scene *scene);
void Gameover();

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

/*
static const Point g_playerPoints[] = {
	Point(-2, -1, '/'),	Point(-2, 0, '-'),	Point(-2, 1, '\\'),
	Point(-1, -1, '|'),	Point(-1, 0, ' '),	Point(-1, 1, '|'),
	Point(0, -1, '|'), Point(0, 0, ' '), Point(0, 1, '|'),
	Point(1, -1, '|'), Point(1, 0, ' '),	Point(1, 1, '|'),
	Point(2, -1, '\\'), Point(2, 0, '-'), Point(2, 1, '/'),
}; //cube
*///static const int g_playerPointsSize = 16;
/*static const Point g_playerPoints[] = {
	Point(-2, -2, '/'),Point(-2, -1, '-'),	Point(2, 0, '-'),	Point(-2, 1, '-'),	Point(-2, 2, '\\'),
	Point(-1, -2, '|'),Point(-1, -1, ' '),	Point(1, 0, ' '),	Point(-1, 1, 'o'),	Point(-1, 2, '|'),
	Point(0, -2, '|'),Point(0, -1, ' '), Point(0, 0, ' '), Point(0, 1, ' '),	Point(-0, 2, '|'),
	Point(1, -2, '|'),Point(1, -1, ' '), Point(-1, 0, ' '),	Point(1, 1, ' '),	Point(1, 2, '|'),
	Point(2, -2, '\\'),Point(2, -1, '-'), Point(-2, 0, '-'), Point(2, 1, '-'),	Point(2, 2, '/'),
}; //asteroide
*/
/*
static const Point g_playerPoints[] = {
	Point(-2, -1, ' '),	Point(-2, 0, '/'),	Point(-2, 1, ' '), Point(-2, 2, ' '),
	Point(-1, -1, '/'),	Point(-1, 0, '-'),	Point(-1, 1, '-'), Point(-1, 2, '/'),
	Point(0, -1, '\\'), Point(0, 0, '-'), Point(0, 1, '-'), Point(0, 2, '\\'),
	Point(1, -1, ' '), Point(1, 0, '\\'),	Point(1, 1, ' '), Point(1, 2, ' ')
};*/
/*
static const Point g_playerPoints[] = {
	Point(-2, -1, '\\'),	Point(-2, 0, '\\'),	Point(-2, 1, ' '),
	Point(-1, -1, '/'),	Point(-1, 0, '\\'),	Point(-1, 1, '\\'),
	Point(0, -1, '<'), Point(0, 0, '-'), Point(0, 1, '-'), Point(0, 2, '-'),
	Point(1, -1, '\\'), Point(1, 0, 'o'),	Point(1, 1, '-'), Point(1, 2, 'o')
};
*/
/*
static const Point g_playerPoints[] =
{
	Point(-1, -1, '/'),	Point(-1, 0, '-'),	Point(-1, 1, '\\'),
	Point(0, -1, '|'), Point(0, 0, '+'), Point(0, 1, '|'),
	Point(1, -1, '\\'), Point(1, 0, '-'),	Point(1, 1, '/'),
};
*/

static const Point g_points[] = {
	Point(0, 0, '*')
};
//static const int g_pointsSize = 1;

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
		start_color();
		init_pair(1, 4, 0);
		attron(COLOR_PAIR(1));
		for (int i = 0; i < this->_pointsSize; ++i)
		{
			mvaddch(entity()->x() + this->_points[i].x(),
					entity()->y() + this->_points[i].y(),
					this->_points[i].c());
		}
		attroff(COLOR_PAIR(1));
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

	void start()
	{}

	void update()
	{
		static int i = 0;
		char c;
		c = getch();

			if('a' == c)
			{
				entity()->setY(entity()->y() - 2);
			}
			if('d' == c)
				entity()->setY(entity()->y() + 2);
			if('w' == c)
				entity()->setX(entity()->x() - 2);
			if('s' == c)
				entity()->setX(entity()->x() + 2);
			if (c == 'h')
				entity()->scene()->setUnactive();

			if (c == 'o' && entity()->scene()->getEntity("Player") == entity())
			{
				GameEntity *dot = new GameEntity(entity()->x(), entity()->y());
				dot->addBehavior<DirectionalBehavior>()->velocity = (rand() % 4) + 10;
				dot->addBehavior<RenderBehavior>()->setPoints(g_points, TAB_SIZE(g_points));

				entity()->scene()->addEntity("dot" + toString(i++), dot);
			}
	}

	CANONICALFORM2(InputBehavior)
};

class InterfaceBehavior: public Behavior
{
public:
	int i;
	int lives;
	int score;

	void update()
	{
		mvprintw(entity()->y(), entity()->x(), "Score : %d", score);
		mvprintw(entity()->y() + 1, entity()->x(), "lives : %d", lives);
		mvprintw(entity()->y() + 2, entity()->x(), "entities : %d", entity()->scene()->entities().size());
		mvprintw(entity()->y() + 3, entity()->x(), "last : %s", entity()->scene()->entities().last()->value().b()->name().c_str());
	}
};


void initboucle()
{
	Scene scene;

	GameEntity *a = new GameEntity(10, 10);
	a->addBehavior<InputBehavior>(); // ONLY THE PLAYER(S) WILL HAVE THIS BEHAVIOR
	a->addBehavior<RenderBehavior>()
		->setPoints(g_playerPoints, TAB_SIZE(g_playerPoints)); // EVERY ENTITY WILL HAVE THIS ONE

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

	scene.addEntity("s1", star1);
	scene.addEntity("s2", star2);
	scene.addEntity("s3", star3);
	scene.addEntity("s4", star4);
	scene.addEntity("s5", star5);

	scene.addEntity("Player", a);
	scene.addEntity("interface", interface);

	scene.start();
	boucle(&scene);
	Gameover();
}

void boucle(Scene *scene)
{
	while(scene->isActive())
	{
		scene->update();
		usleep(20000);
	}
}

	void Gameover()
	{
		while (1)
		{
			mvprintw(LINES/2 - 1, COLS/2, "%s\n", "------------------------");
			mvprintw(LINES/2, COLS/2, "%s\n", "GAME OVER");
			mvprintw(LINES/2 + 1, COLS/2, "%s\n", "Press 'R' to replay");
			mvprintw(LINES/2 + 2 , COLS/2, "%s\n", "Press 'Q' to exit");
			mvprintw(LINES/2 + 3, COLS/2, "%s\n", "------------------------");
			char c = getch();
			if(c == 'r')
			{
				initboucle();
			}
			if(c == 'q')
			{
					endwin();
					break;
			}
			refresh();
		}
	}



int main(void)
{
	time_t ptr;
	std::srand(std::time(&ptr));
	initboucle();
	return 0;
}
