#ifndef SCENE_HPP
# define SCENE_HPP

# include "List.hpp"
# include "GameEntity.hpp"
# include "Player.hpp"

typedef Pair<std::string, GameEntity *> EntityPair;
typedef List<List<EntityPair>::iterator> DestroyQueue;

class Scene
{
public:
	Scene();
	~Scene();

	Scene(const Scene &p_scene);
	Scene &operator=(const Scene &p_scene);

	void addEntity(const std::string &p_name, GameEntity *p_entity);
	void destroy(GameEntity *p_entity);

	void start();
	void update();

	bool isActive() const;
	void setUnactive();

	const List<EntityPair> &entities() const;
	GameEntity *getEntity(const std::string &p_name);

	void setPlayer(Player *p_player);
	Player *player() const;

private:
	List<EntityPair> _entities;
	DestroyQueue _destroyQueue;

	Player *_player;

	bool _isActive;
};

#endif // SCENE_HPP
