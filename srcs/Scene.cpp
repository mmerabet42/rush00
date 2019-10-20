#include "Scene.hpp"
#include <ncurses.h>
#include "RenderBehavior.hpp"

Scene::Scene()
	: _isActive(false)
{}

Scene::~Scene()
{
	for (List<EntityPair>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		delete it->value().b();
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

void Scene::addEntity(const std::string &p_name, GameEntity *p_entity)
{
	if (!p_entity)
		return;
	for (List<EntityPair>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		if (it->value().a() == p_name || it->value().b() == p_entity)
			return;
	this->_entities.push(EntityPair(p_name, p_entity));
	p_entity->setScene(this);
	p_entity->setName(p_name);
}

void Scene::destroy(GameEntity *p_entity)
{
	if (!p_entity)
		return;
	List<EntityPair>::iterator it;
	for (it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		if (it->value().b() == p_entity)
			break;
	if (it == this->_entities.end())
		return;
	if (p_entity == this->_player)
		this->_player = nullptr;
	this->_destroyQueue.push(it);
}

void Scene::start()
{
	initscr();
	curs_set(FALSE);
	noecho();

	this->_isActive = true;

	for (List<EntityPair>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		it->value().b()->start();
}

void Scene::update()
{
	clear();
	timeout(1);

	for (List<EntityPair>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		it->value().b()->update();
	for (DestroyQueue::iterator it = this->_destroyQueue.begin(); it != this->_destroyQueue.end(); it = it->next())
	{
		delete it->value()->value().b();
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

const List<EntityPair> &Scene::entities() const
{
	return this->_entities;
}

GameEntity *Scene::getEntity(const std::string &p_name)
{
	for (List<EntityPair>::iterator it = this->_entities.begin(); it != this->_entities.end(); it = it->next())
		if (it->value().a() == p_name)
			return it->value().b();
	return nullptr;
}

void Scene::setPlayer(Player *p_player)
{
	this->_player = p_player;
	this->addEntity("Player", p_player);
}

Player *Scene::player() const
{
	return this->_player;
}
