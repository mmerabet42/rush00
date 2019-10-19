#include <iostream>
#include "GameEntity.hpp"

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

int main()
{
	A a(-2, -3);
	A b(0, 0);

	std::cout << a.collidesWith(b) << std::endl;

	return 0;
}
