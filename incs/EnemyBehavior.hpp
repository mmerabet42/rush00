#ifndef ENEMYBEHAVIOR_HPP
# define ENEMYBEHAVIOR_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"
# include "DirectionalBehavior.hpp"
# include <ctime>

class EnemyBehavior : public Behavior
{
public:
	void start();
	void update();

	void set(const int &p_yVelocity, const int &p_xVelocity);

	CANONICALFORM(EnemyBehavior)

	int xVelocity;
	int yVelocity;
	int fireRate;

private:
	DirectionalBehavior *_db;
	time_t _lastTime;
};

#endif // ENEMYBEHAVIOR_HPP
