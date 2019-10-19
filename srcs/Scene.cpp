#include "Scene.hpp"

Scene::Scene()
{}

Scene::~Scene()
{
	for (List<GameEntity *>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		delete it->value();
}

Scene::Scene(const Scene &p_scene)
{
	*this = p_scene;
}

Scene &Scene::operator=(const Scene &p_scene)
{
	this->_entities = p_scene._entities;
	return *this;
}

void Scene::addEntity(GameEntity *p_entity)
{
	if (!p_entity)
		return;
	for (List<GameEntity *>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		if (it->value() == p_entity)
			return;
	this->_entities.push(p_entity);
	p_entity->setScene(this);
}

void Scene::destroy(GameEntity *p_entity)
{
	if (!p_entity)
		return;
	List<GameEntity *>::iterator it;
	for (it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		if (it->value() == p_entity)
			break;
	if (it == this->_entities.end())
		return;
	this->_destroyQueue.push(it);
}

void Scene::update()
{
	for (List<GameEntity *>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		it->value()->update();
	for (DestroyQueue::iterator it = this->_destroyQueue.begin(); it != this->_destroyQueue.end(); it = it->next())
	{
		delete it->value()->value();
		this->_entities.erase(it->value());
	}
	this->_destroyQueue.clear();
}

List<GameEntity *> Scene::entities() const
{
	return this->_entities;
}
