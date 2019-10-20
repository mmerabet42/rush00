#include "Scene.hpp"
#include <ncurses.h>

Scene::Scene()
	: _isActive(false)
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

void Scene::start()
{
	initscr();
	curs_set(FALSE);
	noecho();

	this->_isActive = true;
}

void Scene::update()
{
	clear();
	timeout(1);

	for (List<GameEntity *>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		it->value()->update();
	for (DestroyQueue::iterator it = this->_destroyQueue.begin(); it != this->_destroyQueue.end(); it = it->next())
	{
		delete it->value()->value();
		this->_entities.erase(it->value());
	}
	this->_destroyQueue.clear();

	refresh();

	if (!this->_isActive)
		endwin();
}

bool Scene::isActive() const
{
	return this->_isActive;
}

void Scene::setUnactive()
{
	this->_isActive = false;
}

List<GameEntity *> Scene::entities() const
{
	return this->_entities;
}
