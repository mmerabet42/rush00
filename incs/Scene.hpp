#ifndef SCENE_HPP
# define SCENE_HPP

# include "List.hpp"
# include "GameEntity.hpp"

class Scene
{
public:
	Scene();
	~Scene();

	Scene(const Scene &p_scene);
	Scene &operator=(const Scene &p_scene);



private:
	List<GameEntity *> _entities;
};

#endif // SCENE_HPP
