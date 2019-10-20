#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "CanonicalForm.hpp"
# include "GameEntity.hpp"
# include "InputBehavior.hpp"
# include "RenderBehavior.hpp"

class Player : public GameEntity
{
public:
	Player(const int &p_x, const int &p_y);

	CANONICALFORM2(Player)
private:
	InputBehavior *_inputBehavior;
	RenderBehavior *_renderBehavior;
};

#endif // PLAYER_HPP
