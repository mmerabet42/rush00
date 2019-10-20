#ifndef DIRECTIONALBEHAVIOR_HPP
# define DIRECTIONALBEHAVIOR_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"

class DirectionalBehavior : public Behavior
{
public:
	void start();
	void update();

	int velocity;

	CANONICALFORM(DirectionalBehavior)
};

#endif // DIRECTIONALBEHAVIOR_HPP
