#ifndef INPUTBEHAVIOR_HPP
# define INPUTBEHAVIOR_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"

class InputBehavior : public Behavior
{
public:
	InputBehavior();

	void update();

	void set(const int &p_up, const int &p_down, const int &p_left, const int &p_right, const int &p_fire);

	CANONICALFORM2(InputBehavior)

private:
	int _up;
	int _down;
	int _left;
	int _right;
	int _fire;
};

#endif // INPUTBEHAVIOR_HPP
