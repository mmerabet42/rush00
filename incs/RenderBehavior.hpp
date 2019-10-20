#ifndef RENDERBEHAVIOR_HPP
# define RENDERBEHAVIOR_HPP

# include "CanonicalForm.hpp"
# include "Behavior.hpp"
# include "Point.hpp"

class RenderBehavior : public Behavior
{
public:
	RenderBehavior();

	void update();

	void set(const Point *p_points, const int &p_pointsSize);

	bool collidesWith(const RenderBehavior *p_other) const;

	CANONICALFORM2(RenderBehavior)

private:
	const Point *_points;
	int _pointsSize;
};

#endif // RENDERBEHAVIOR_HPP
