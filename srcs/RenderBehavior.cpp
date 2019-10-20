#include "RenderBehavior.hpp"
#include <ncurses.h>
#include "GameEntity.hpp"

RenderBehavior::RenderBehavior()
	: _points(nullptr), _pointsSize(0)
{}

void RenderBehavior::update()
{
	for (int i = 0; i < this->_pointsSize; ++i)
	{
		mvaddch(entity()->x() + this->_points[i].x(),
				entity()->y() + this->_points[i].y(),
				this->_points[i].c());
	}
}

void RenderBehavior::set(const Point *p_points, const int &p_pointsSize)
{
	this->_points = p_points;
	this->_pointsSize = p_pointsSize;
}

bool RenderBehavior::collidesWith(const RenderBehavior *p_other) const
{
	if (!p_other)
		return false;
	for (int i = 0; i < this->_pointsSize; ++i)
		for (int j = 0; j < p_other->_pointsSize; ++j)
			if (entity()->x() + this->_points[i].x() == p_other->entity()->x() + p_other->_points[j].x()
					&& entity()->y() + this->_points[i].y() == p_other->entity()->y() + p_other->_points[j].y())
				return true;
	return false;
}
