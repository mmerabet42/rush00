#ifndef GAMEENTITY_HPP
# define GAMEENTITY_HPP

# include <string>
# include <typeinfo>
# include "Point.hpp"
# include "Pair.hpp"
# include "Behavior.hpp"
# include "List.hpp"

typedef Pair<const std::type_info *, Behavior *> BehaviorPair;

class Scene;

class GameEntity
{
protected:
	GameEntity();
public:
	virtual ~GameEntity();

	GameEntity(const GameEntity &p_gameEntity);
	GameEntity &operator=(const GameEntity &p_gameEntity);

	GameEntity(const int &p_x, const int &p_y);

	int x() const;
	int y() const;

	Scene *scene() const;
	void setScene(Scene *p_scene); 

	void setPos(const int &p_x, const int &p_y);
	void setX(const int &p_x);
	void setY(const int &p_y);

	int getPointX(const int &p_i) const;
	int getPointY(const int &p_i) const;
	char getPointSymb(const int &p_i) const;

	bool collidesWith(const GameEntity &p_entity) const;

	template <typename T_Behavior>
	T_Behavior *addBehavior();
	
	void update();

	virtual Point *getPoints() const = 0;
	virtual int getPointsSize() const = 0;

protected:
	int _x;
	int _y;

	List<BehaviorPair> _behaviors;

	Scene *_scene;
};

template <typename T_Behavior>
T_Behavior *GameEntity::addBehavior()
{
	static const std::type_info *t = &typeid(T_Behavior);

	for (List<BehaviorPair>::iterator it = this->_behaviors.begin(); it != this->_behaviors.end(); it = it->next())
		if (it->value().a() == t)
			return nullptr;
	T_Behavior *bv = new T_Behavior();
	if (!bv)
		return nullptr;
	bv->setEntity(this);
	this->_behaviors.push(BehaviorPair(t, bv));
	return bv;
}

#endif // GAMEENTITY_HPP
