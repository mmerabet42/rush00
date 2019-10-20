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

static const Point g_points[] = {
	Point(0, 0, 'O')
};

// THE PLAYER SHAPE
int main(void)
{
// EXAMPLE:
	Scene scene;
	time_t ptr;
	std::srand(std::time(&ptr));

	Player *player = new Player(10, 10);

	GameEntity *interface = new GameEntity(2, 2);
	interface->addBehavior<InterfaceBehavior>();

	GameEntity *dot = new GameEntity(20, 60);
	dot->addBehavior<KillPlayer>();
	dot->addBehavior<RenderBehavior>()->set(g_points, 1);

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

	scene.addEntity("d", dot);
	scene.addEntity("s1", star1);
	scene.addEntity("s2", star2);
	scene.addEntity("s3", star3);
	scene.addEntity("s4", star4);
	scene.addEntity("s5", star5);

	scene.setPlayer(player);
//	scene.addEntity("Player", player);
	scene.addEntity("interface", interface);

	scene.start();
	while(scene.isActive())
	{
		scene.update();
		usleep(20000);
	}

	return 0;
}
