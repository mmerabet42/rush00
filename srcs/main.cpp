#include <ncurses.h>
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h>

#include "GameEntity.hpp"
#include "Behavior.hpp"
#include "Scene.hpp"

class A : public GameEntity
{
public:
	A(const int &p_x, const int &p_y)
		: GameEntity(p_x, p_y)
	{}

	Point *getPoints() const
	{
		static Point ps[] = {
			Point(1, 1, '/'),	Point(0, 1, '-'),	Point(-1, 1, '\\'),
			Point(1, 0, '-'),	Point(0, 0, '-'),	Point(-1, 0, '-'),
      Point(0, 2, '>'), Point(0, -2, '3'), Point(0, -3, '~'),
			Point(1, -1, '\\'), Point(0, -1, '-'),	Point(-1, -1, '/'),
		  Point(-2, 1, '/'), Point(-2, 2, '-'), Point(2, 1, '\\'),
      Point(2, 2, '-'),
		};
		return ps;
	}
	int getPointsSize() const
	{
		return 16;
	}
};

class EmptyGameEntity : public GameEntity
{
public:
	EmptyGameEntity(const int &p_x, const int &p_y)
		: GameEntity(p_x, p_y)
	{}

	Point *getPoints() const
	{
		return nullptr;
	}

	int getPointsSize() const
	{
		return 0;
	}
};

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
*/
void DrawHero (A a)
{
  for(int i = 0; i < a.getPointsSize() ; i++)
  {
    mvaddch(a.getPointX(i), a.getPointY(i), a.getPointSymb(i));
  }
}
// THIS ^ WOULD BECOME THIS v
class RenderBehavior: public Behavior
{
public:
	void update()
	{
		for (int i = 0; i < entity()->getPointsSize(); ++i)
			mvaddch(entity()->getPointX(i), entity()->getPointY(i), entity()->getPointSymb(i));
	}
};

class InputBehavior: public Behavior
{
public:
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
		mvprintw(entity()->y(), entity()->x(), "Score : %d", 150);          // you use it like printf
		mvprintw(entity()->y() + 1, entity()->x(), "lives : %d", 3);
	}
};

/*
void EnemySpawn()
{

}

*/
void Interface()
{
//  int score = 150;
//  int lives = 3;
  mvprintw( 2, 2, "Score : 150");          // NEED ITOA
  mvprintw( 3, 2, "lives : 3");
}

void Update(Scene &scene)
{
  clear();
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

void Background(int i, int j, int h)
{
  mvaddch(10, COLS - i, '*');
  mvaddch(40, COLS - j, '*');                   //NEED RANDOM SPAWN
  mvaddch(20, COLS - h, '*');
}


int main(void)
{
    initscr();
    curs_set(FALSE);
    int i = 0;
    int j = 0;
    int h = 0;

// EXAMPLE:
	Scene scene;

	A *a = new A(10, 10);
	a->addBehavior<InputBehavior>(); // ONLY THE PLAYER(S) WILL HAVE THIS BEHAVIOR
	a->addBehavior<RenderBehavior>(); // EVERY ENTITY WILL HAVE THIS ONE

	EmptyGameEntity *interface = new EmptyGameEntity(2, 2);
	interface->addBehavior<InterfaceBehavior>();

	scene.addEntity(a);
	scene.addEntity(interface);

    noecho();
    while(1)                  //need isAlive
    {
      clear();
      /***************/
      i++;
      if ( i > COLS )
        i = 0;
      j += 2;
      if ( j > COLS )           //Background
        j = 0;
      h += 3;
      if ( h > COLS )
        h = 0;
      /*****************/
      timeout(1);
      Update(scene);
      Background(i,j,h);
      refresh();
      usleep(20000);
    }
    endwin();
    return 0;
}
