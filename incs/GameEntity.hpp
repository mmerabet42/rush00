#ifndef GAMEENTITY_HPP
# define GAMEENTITY_HPP

# include <string>
# include <typeinfo>
# include "Point.hpp"
# include "Pair.hpp"

//typedef Pair<std::type_info, Behavior *> BehaviorPair;

class GameEntity
{
protected:
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

	int getPointX(const int &p_i) const;
	int getPointY(const int &p_i) const;
	char getPointSymb(const int &p_i) const;

	bool collidesWith(const GameEntity &p_entity) const;
/*
	template <typename T_Behavior>
	T_Behavior *addBehavior();
*/
	virtual Point *getPoints() const = 0;
	virtual int getPointsSize() const = 0;

protected:
	int _x;
	int _y;

//	List<BehaviorInfo> _behaviors;
};
/*
template <typename T_Behavior>
T_Behavior *addBehavior()
{
	static std::type_info t = typeid(T_Behavior);

	List<BehaviorInfo>::iterator ` 
}
*/
#endif // GAMEENTITY_HPP
