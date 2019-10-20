#ifndef DIRECTIONALBEHAVIOR_HPP
# define DIRECTIONALBEHAVIOR_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"

class DirectionalBehavior : public Behavior
{
public:
	DirectionalBehavior();

	void update();

	void set(const int &p_yVelocity, const int &p_xVelocity, const bool &p_deleteAtExit);

	CANONICALFORM2(DirectionalBehavior)

	bool deleteAtExit;
	int yVelocity;
	int xVelocity;
};

#endif // DIRECTIONALBEHAVIOR_HPP
