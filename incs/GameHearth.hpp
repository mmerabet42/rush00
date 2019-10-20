#ifndef GAMEHEARTH_HPP
# define GAMEHEARTH_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"

class GameHearth : public Behavior
{
public:
	void update();

	int spawnRate;

	CANONICALFORM(GameHearth)
};

#endif // GAMEHEARTH_HPP
