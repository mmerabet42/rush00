#ifndef GAMEENTITY_HPP
# define GAMEENTITY_HPP

# include "Pair.hpp"

typedef Pair<int, int> Point;

class GameEntity
{
private:
	GameEntity();
public:
	~GameEntity();

	GameEntity(const GameEntity &p_gameEntity);
	GameEntity &operator=(const GameEntity &p_gameEntity);

	GameEntity(const int &p_x, const int &p_y);

	int x() const;
	int y() const;

	void setPos(const int &p_x, const int &p_y);
	void setX(const int &p_x);
	void setY(const int &p_y);

	virtual Point *points() const = 0;
	virtual int points_size() const = 0;
protected:
	Point _pos;
};

#endif // GAMEENTITY_HPP
