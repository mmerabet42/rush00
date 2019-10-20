#include <ncurses.h>
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>

#include "GameEntity.hpp"
#include "Behavior.hpp"
#include "Scene.hpp"
#include "CanonicalForm.hpp"
#include "Star.hpp"
#include "utils.hpp"
#include "InputBehavior.hpp"
#include "RenderBehavior.hpp"
#include "DirectionalBehavior.hpp"
#include "InterfaceBehavior.hpp"
#include "KillPlayer.hpp"
#include "Player.hpp"
#include "GameHearth.hpp"

static const Point g_points[] = {
	Point(0, 0, 'O')
};

void boucle(Scene *scene);
void Gameover();

void initboucle()
{
	Scene scene;

	Player *player = new Player(10, 10);

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

	GameEntity *gameHearth = new GameEntity(0, 0);
	gameHearth->addBehavior<GameHearth>();

	scene.setPlayer(player);
	scene.addEntity("s1", star1);
	scene.addEntity("s2", star2);
	scene.addEntity("s3", star3);
	scene.addEntity("s4", star4);
	scene.addEntity("s5", star5);

	scene.addEntity("interface", interface);
	scene.addEntity("gameHearth", gameHearth);

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
	initboucle();
	return 0;
}
