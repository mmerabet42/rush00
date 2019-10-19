#include "Point.hpp"

Point::Point()
{}

Point::~Point()
{}

Point::Point(const Point &p_point)
{
	*this = p_point;
}

Point &Point::operator=(const Point &p_point)
{
	this->_x = p_point._x;
	this->_y = p_point._y;
	this->_char = p_point._char;
	return *this;
}

Point::Point(const int &p_x, const int &p_y, const char &p_char)
	: _x(p_x), _y(p_y), _char(p_char)
{}

int Point::x() const
{
	return this->_x;
}

int Point::y() const
{
	return this->_y;
}

char Point::c() const
{
	return this->_char;
}

void Point::setX(const int &p_x)
{
	this->_x = p_x;
}

void Point::setY(const int &p_y)
{
	this->_y = p_y;
}

void Point::setPos(const int &p_x, const int &p_y)
{
	this->_x = p_x;
	this->_y = p_y;
}

void Point::setChar(const char &p_char)
{
	this->_char = p_char;
}
