#include "Player.hpp"
#include "utils.hpp"

static const Point g_playerPoints[] = {
	Point(1, 1, '/'),	Point(0, 1, '-'),	Point(-1, 1, '\\'),
	Point(1, 0, '-'),	Point(0, 0, '-'),	Point(-1, 0, '-'),
	Point(0, 2, '>'), Point(0, -2, '3'), Point(0, -3, '~'),
	Point(1, -1, '\\'), Point(0, -1, '-'),	Point(-1, -1, '/'),
	Point(-2, 1, '/'), Point(-2, 2, '-'), Point(2, 1, '\\'),
	Point(2, 2, '-'),
};

Player::Player(const int &p_x, const int &p_y)
	: GameEntity(p_x, p_y)
{
	this->_inputBehavior = this->addBehavior<InputBehavior>();
	this->_renderBehavior = this->addBehavior<RenderBehavior>();
	this->_renderBehavior->set(g_playerPoints, TAB_SIZE(g_playerPoints), 6);
}
