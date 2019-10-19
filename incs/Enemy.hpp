#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "GameEntity.hpp"

class Enemy : public GameEntity
{
private:
	Enemy();
public:
	~Enemy();

	Enemy(const Enemy &p_gameEntity);
	Enemy &operator=(const Enemy &p_enemy);

	Enemy(const int &p_x, const int &p_y);
};

#endif // GAMEENTITY_HPP
