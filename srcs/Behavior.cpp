#include "Behavior.hpp"
#include <cstddef>

Behavior::Behavior()
	: _entity(nullptr)
{}

Behavior::~Behavior()
{}

Behavior::Behavior(const Behavior &p_bhvr)
{
	*this = p_bhvr;
}

Behavior &Behavior::operator=(const Behavior &p_bhvr)
{
	this->_entity = p_bhvr._entity;
	return *this;
}

GameEntity *Behavior::entity() const
{
	return this->_entity;
}

void Behavior::setEntity(GameEntity *p_entity)
{
	this->_entity = p_entity;
}

void Behavior::start()
{}

void Behavior::update()
{}
