#ifndef KILLENEMY_HPP
# define KILLENEMY_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"
# include "RenderBehavior.hpp"
# include "InterfaceBehavior.hpp"

class KillEnemy : public Behavior
{
public:
	void start();
	void update();

private:
	RenderBehavior *_renderBehavior;
	InterfaceBehavior *_interface;
};

#endif // KILLENEMY_HPP
