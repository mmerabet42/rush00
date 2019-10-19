#include "Enemy.hpp"

Enemy::Enemy()
	: GameEntity()
{}

Enemy::~Enemy()
{}

Enemy::Enemy(const Enemy &p_enemy)
	: GameEntity(p_enemy)
{}

Enemy &Enemy::operator=(const Enemy &p_enemy)
{
	GameEngine::operator=(p_enemy);
	return *this;
}

Enemy::Enemy(const int &p_x, const int &p_y)
	: GameEntity(p_x, p_y)
{}
