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
	p_entity->setScene(this);
	p_entity->setName(p_name);
	if (!this->_isActive)
		this->_entities.pushFront(EntityPair(p_name, p_entity));
	else
		this->_addQueue.pushFront(EntityPair(p_name, p_entity));
}

void Scene::destroy(GameEntity *p_entity)
{
	if (!p_entity)
		return;
	List<EntityPair>::iterator it = this->_entities.begin();
	for (; it != this->_entities.end(); it = it->next())
		if (it->value().b() == p_entity)
			break;
	if (it == this->_entities.end())
		return;
	DestroyQueue::iterator it2 = this->_destroyQueue.begin();
	for (; it2 != this->_destroyQueue.end(); it2 = it2->next())
		if (it2->value() == it)
			return;
	this->_destroyQueue.pushFront(it);
}

void Scene::start()
{
	std::srand(time(&this->_startTimer));
	initscr();
	curs_set(FALSE);
	noecho();
	start_color();
	init_pair(0, 0, 0);
	init_pair(1, 1, 0);
	init_pair(2, 2, 0);
	init_pair(3, 3, 0);
	init_pair(4, 4, 0);
	init_pair(5, 5, 0);
	init_pair(6, 6, 0);
	init_pair(7, 7, 0);

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
		if (!it || !it->value())
			continue;
		if (it->value()->value().b() == this->_player)
			this->_player = nullptr;
		delete it->value()->value().b();
		this->_entities.erase(it->value());
	}
	this->_destroyQueue.clear();

	for (AddQueue::iterator it = this->_addQueue.begin(); it != this->_addQueue.end(); it = it->next())
	{
		this->_entities.pushFront(it->value());
		it->value().b()->start();
	}
	this->_addQueue.clear();

	refresh();
}

bool Scene::isActive() const
{
	return this->_isActive;
}

void Scene::setUnactive()
{
	this->_isActive = false;
}

List<EntityPair> &Scene::entities()
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

time_t Scene::elapsedTime() const
{
	time_t currentTime;
	time(&currentTime);

	return currentTime - this->_startTimer;
}
