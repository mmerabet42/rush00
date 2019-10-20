#ifndef BEHAVIOR_HPP
# define BEHAVIOR_HPP

class GameEntity;

class Behavior
{
private:

	Behavior(const Behavior &p_bhvr);
	Behavior &operator=(const Behavior &p_bhvr);

public:
	Behavior();
	virtual ~Behavior();

	GameEntity *entity() const;
	void setEntity(GameEntity *p_entity);

	virtual void start();
	virtual void update();

private:
	GameEntity *_entity;
};

#endif // BEHAVIOR_HPP
