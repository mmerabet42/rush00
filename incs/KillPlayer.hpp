#ifndef KILLPLAYER_HPP
# define KILLPLAYER_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"
# include "RenderBehavior.hpp"

class KillPlayer : public Behavior
{
public:
	void start();
	void update();

	void set(const int &p_score);

	int score;

	CANONICALFORM(KillPlayer)
private:
	RenderBehavior *_renderBehavior;
	RenderBehavior *_playerBehavior;
};

#endif // KILLPLAYER_HPP
