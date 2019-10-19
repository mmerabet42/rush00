#ifndef SCENE_HPP
# define SCENE_HPP

# include "List.hpp"
# include "GameEntity.hpp"

typedef List<List<GameEntity *>::iterator> DestroyQueue;

class Scene
{
public:
	Scene();
	~Scene();

	Scene(const Scene &p_scene);
	Scene &operator=(const Scene &p_scene);

	void addEntity(GameEntity *p_entity);
	void destroy(GameEntity *p_entity);

	void update();

	List<GameEntity *> entities() const;

private:
	List<GameEntity *> _entities;
	DestroyQueue _destroyQueue;
};

#endif // SCENE_HPP
