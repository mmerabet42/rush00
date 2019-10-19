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

int GameEntity::getPointX(const int &p_i) const
{
	return this->_x + this->getPoints()[p_i].x();
}

int GameEntity::getPointY(const int &p_i) const
{
	return this->_y + this->getPoints()[p_i].y();
}

char GameEntity::getPointSymb(const int &p_i) const
{
	return this->getPoints()[p_i].c();
}

bool GameEntity::collidesWith(const GameEntity &p_entity) const
{
	for (int i = 0; i < this->getPointsSize(); ++i)
		for (int j = 0; j < p_entity.getPointsSize(); ++j)
			if (this->getPointX(i) == p_entity.getPointY(j) && this->getPointY(i) == p_entity.getPointY(j))
				return true;
	return false;
}

void GameEntity::update()
{
	for (List<BehaviorPair>::iterator it = this->_behaviors.begin(); it != this->_behaviors.end(); it = it->next())
		it->value().b()->update();
}
