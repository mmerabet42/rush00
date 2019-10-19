#ifndef POINT_HPP
# define POINT_HPP

class Point
{
private:
	Point();
public:
	~Point();

	Point(const Point &p_point);
	Point &operator=(const Point &p_point);

	Point(const int &p_x, const int &p_y, const char &p_char);

	int x() const;
	int y() const;
	char c() const;

	void setX(const int &p_x);
	void setY(const int &p_y);
	void setPos(const int &p_x, const int &p_y);

	void setChar(const char &p_char);


private:
	int _x;
	int _y;
	char _char;
};

#endif // POINT_HPP
