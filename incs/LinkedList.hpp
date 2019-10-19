#ifndef LINKEDLIST_HPP
# define LINKEDLIST_HPP

# include <cstddef>

template <typename T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	LinkedList(const LinkedList<T> &p_linkedList);
	LinkedList<T> &operator=(const LinkedList<T> &p_linkedList);

	LinkedList(const T &p_value);

	const T &value() const;

	T &value();
	void setValue(const T &p_value);

	const LinkedList<T> *next() const;
	LinkedList<T> *next();
	void setNext(LinkedList<T> *p_next);

	const LinkedList<T> *prev() const;
	LinkedList<T> *prev();
	void setPrev(LinkedList<T> *p_prev);

private:
	T _value;
	LinkedList<T> *_next;
	LinkedList<T> *_prev;
};

template <typename T>
LinkedList<T>::LinkedList()
	: LinkedList(T())
{}

template <typename T>
LinkedList<T>::~LinkedList()
{}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &p_linkedList)
{
	*this = p_linkedList;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &p_linkedList)
{
	this->_value = p_linkedList._value;
	this->_next = p_linkedList._next;
	this->_prev = p_linkedList._prev;
}

template <typename T>
LinkedList<T>::LinkedList(const T &p_value)
	: _value(p_value), _next(nullptr), _prev(nullptr)
{}

template <typename T>
const T &LinkedList<T>::value() const
{
	return this->_value;
}

template <typename T>
T &LinkedList<T>::value()
{
	return this->_value;
}

template <typename T>
void LinkedList<T>::setValue(const T &p_value)
{
	this->_value = p_value;
}

template <typename T>
const LinkedList<T> *LinkedList<T>::next() const
{
	return this->_next;
}

template <typename T>
LinkedList<T> *LinkedList<T>::next()
{
	return this->_next;
}

template <typename T>
void LinkedList<T>::setNext(LinkedList<T> *p_next)
{
	this->_next = p_next;
}

template <typename T>
const LinkedList<T> *LinkedList<T>::prev() const
{
	return this->_prev;
}

template <typename T>
LinkedList<T> *LinkedList<T>::prev()
{
	return this->_prev;
}

template <typename T>
void LinkedList<T>::setPrev(LinkedList<T> *p_prev)
{
	this->_prev = p_prev;
}

#endif  // LINKEDLIST_HPP
