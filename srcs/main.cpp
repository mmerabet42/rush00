#include <ncurses.h>
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h>

#include "GameEntity.hpp"
#include "Behavior.hpp"
#include "Scene.hpp"
#include "Star.hpp"

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

void DrawHero (A a)
{
  for(int i = 0; i < a.getPointsSize() ; i++)
  {
    mvaddch(a.getPointX(i), a.getPointY(i), a.getPointSymb(i));
  }
}*/
// THIS ^ WOULD BECOME THIS v
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
	}
};

class InterfaceBehavior: public Behavior
{
public:
	void update()
	{
		mvprintw(entity()->y(), entity()->x(), "Score : %d", 150); // you use it like printf
		mvprintw(entity()->y() + 1, entity()->x(), "lives : %d", 3);
	}
};

/*
void EnemySpawn()
{

}


void Interface()
{
//  int score = 150;
//  int lives = 3;
  mvprintw( 2, 2, "Score : 150");          // NEED ITOA
  mvprintw( 3, 2, "lives : 3");
}
*/
void Update(Scene &scene)
{
  //clear();
/*************************/
//  DrawHero(a);
	scene.update();
  //EnemySpawn();                                 // RANDOM SPAWN Enemy
//  for(int i = 0; i < nbrEnemy; i++)               //iteration pour actualier les deplacement/tir de chaque ennemy
  //  UpdateEnemy(Enemy enemy[i], Hero perso );
//  DrawEnemy();
/**************************/
//  Interface();
  noecho();
}

void initBackground()
{

}


int main(void)
{
    initscr();
    curs_set(FALSE);
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

	initBackground();

    noecho();
    while(1)                  //need isAlive
    {
      clear();
      timeout(1);
      Update(scene);
      refresh();
      usleep(20000);
    }
    endwin();
    return 0;
}
