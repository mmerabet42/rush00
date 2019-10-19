#include "GameEntity.hpp"

GameEntity::GameEntity()
{}

GameEntity::~GameEntity()
{}

GameEntity::GameEntity(const GameEntity &p_gameEntity)
{
	*this = p_gameEntity;
}

GameEntity &GameEntity::operator=(const GameEntity &p_gameEntity)
{
	this->_pos = p_gameEntity._pos;
	return *this;
}

GameEntity::GameEntity(const int &p_x, const int &p_y)
	: _pos(p_x, p_y)
{}

int GameEntity::x() const
{
	return this->_pos.a();
}

int GameEntity::y() const
{
	return this->_pos.b();
}

void GameEntity::setPos(const int &p_x, const int &p_y)
{
	this->_pos.setPair(p_x, p_y);
}

void GameEntity::setX(const int &p_x)
{
	this->_pos.setA(p_x);
}

void GameEntity::setY(const int &p_y)
{
	this->_pos.setB(p_y);
}
