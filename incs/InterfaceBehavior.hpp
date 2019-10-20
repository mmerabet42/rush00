#ifndef INTERFACEBEHAVIOR_HPP
# define INTERFACEBEHAVIOR_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"

class InterfaceBehavior : public Behavior
{
public:
	void start();
	void update();

	CANONICALFORM(InterfaceBehavior)

	int lives;
	int score;
};

#endif // INTERFACEBEHAVIOR_HPP
