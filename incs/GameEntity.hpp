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

	std::string name() const;
	void setName(const std::string &p_name);

	void setPos(const int &p_x, const int &p_y);
	void setX(const int &p_x);
	void setY(const int &p_y);

	template <typename T_Behavior>
	T_Behavior *addBehavior();

	template <typename T_Behavior>
	T_Behavior *getBehavior();

	void start();
	void update();

private:
	template <typename T>
	const std::type_info *getTypeInfo() const;

protected:
	int _x;
	int _y;

	List<BehaviorPair> _behaviors;

	Scene *_scene;
	std::string _name;
};

template <typename T_Behavior>
T_Behavior *GameEntity::addBehavior()
{
	static const std::type_info *t = this->getTypeInfo<T_Behavior>();

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


template <typename T_Behavior>
T_Behavior *GameEntity::getBehavior()
{
	static const std::type_info *t = this->getTypeInfo<T_Behavior>();

	for (List<BehaviorPair>::const_iterator it = this->_behaviors.begin(); it != this->_behaviors.end(); it = it->next())
		if (it->value().a() == t)
			return dynamic_cast<T_Behavior *>(it->value().b());
	return nullptr;
}

template <typename T_Behavior>
const std::type_info *GameEntity::getTypeInfo() const
{
	static const std::type_info *t = &typeid(T_Behavior);
	return t;
}

#endif // GAMEENTITY_HPP
