#ifndef PAIR_HPP
# define PAIR_HPP

template <typename A, typename B>
class Pair
{
public:
	Pair();
	~Pair();

	Pair(const Pair<A, B> &p_pair);
	Pair<A, B> &operator=(const Pair<A, B> &p_pair);

	Pair(const A &p_a, const B &p_b);

	const A &a() const;
	A a();

	const B &b() const;
	B b();

	void setPair(const A &p_a, const B &p_b);
	void setA(const A &p_a);
	void setB(const B &p_b);

private:
	A _a;
	B _b;
};

template <typename A, typename B>
Pair<A, B>::Pair()
{}

template <typename A, typename B>
Pair<A, B>::~Pair()
{}

template <typename A, typename B>
Pair<A, B>::Pair(const Pair<A, B> &p_pair)
{
	*this = p_pair;
}

template <typename A, typename B>
Pair<A, B> &Pair<A, B>::operator=(const Pair<A, B> &p_pair)
{
	this->_a = p_pair._a;
	this->_b = p_pair._b;
	return *this;
}

template <typename A, typename B>
Pair<A, B>::Pair(const A &p_a, const B &p_b)
	: _a(p_a), _b(p_b)
{}

template <typename A, typename B>
const A &Pair<A, B>::a() const
{
	return this->_a;
}

template <typename A, typename B>
A Pair<A, B>::a()
{
	return this->_a;
}

template <typename A, typename B>
const B &Pair<A, B>::b() const
{
	return this->_b;
}

template <typename A, typename B>
B Pair<A, B>::b()
{
	return this->_b;
}

template <typename A, typename B>
void Pair<A, B>::setPair(const A &p_a, const B &p_b)
{
	this->_a = p_a;
	this->_b = p_b;
}

template <typename A, typename B>
void Pair<A, B>::setA(const A &p_a)
{
	this->_a = p_a;
}

template <typename A, typename B>
void Pair<A, B>::setB(const B &p_b)
{
	this->_a = p_b;
}

#endif // PAIR_HPP
