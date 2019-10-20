#include "GameEntity.hpp"
#include <iostream>

GameEntity::GameEntity()
{}

GameEntity::~GameEntity()
{
	for (List<BehaviorPair>::iterator it = this->_behaviors.begin(); it != this->_behaviors.end(); it = it->next())
		delete it->value().b();
}

GameEntity::GameEntity(const GameEntity &p_gameEntity)
{
	*this = p_gameEntity;
}

GameEntity &GameEntity::operator=(const GameEntity &p_gameEntity)
{
	this->_x = p_gameEntity._x;
	this->_y = p_gameEntity._y;
	return *this;
}

GameEntity::GameEntity(const int &p_x, const int &p_y)
	: _x(p_x), _y(p_y)
{}

int GameEntity::x() const
{
	return this->_x;
}

int GameEntity::y() const
{
	return this->_y;
}

Scene *GameEntity::scene() const
{
	return this->_scene;
}

void GameEntity::setScene(Scene *p_scene)
{
	this->_scene = p_scene;
}

std::string GameEntity::name() const
{
	return this->_name;
}

void GameEntity::setName(const std::string &p_name)
{
	this->_name = p_name;
}

void GameEntity::setPos(const int &p_x, const int &p_y)
{
	this->_x = p_x;
	this->_y = p_y;
}

void GameEntity::setX(const int &p_x)
{
	this->_x = p_x;
}

void GameEntity::setY(const int &p_y)
{
	this->_y = p_y;
}

void GameEntity::start()
{
	for (List<BehaviorPair>::iterator it = this->_behaviors.begin(); it != this->_behaviors.end(); it = it->next())
		it->value().b()->start();
}

void GameEntity::update()
{
	for (List<BehaviorPair>::iterator it = this->_behaviors.begin(); it != this->_behaviors.end(); it = it->next())
		it->value().b()->update();
}
