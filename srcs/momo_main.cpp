#include <iostream>
#include "GameEntity.hpp"
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
			Point(1, 1, 'a'),	Point(0, 1, 'b'),	Point(-1, 1, 'c'),
			Point(1, 0, 'd'),	Point(0, 0, 'e'),	Point(-1, 0, 'f'),
			Point(1, -1, 'g'),	Point(0, -1, 'h'),	Point(-1, -1, 'i'),
													Point(-1, -2, 'j')
		};
		return ps;
	}
	int getPointsSize() const
	{
		return 10;
	}
};

class Move: public Behavior
{
public:
	void update()
	{
		this->entity()->scene()->destroy(this->entity());
	}
};

int main()
{
	Scene scene;

	A *a = new A(-2, -3);
	a->addBehavior<Move>();
	A *b = new A(0, 0);

	scene.addEntity(a);
	scene.addEntity(b);

	std::cout << scene.entities().size() << std::endl;
	scene.update();
	std::cout << scene.entities().size() << std::endl;

	return 0;
}
