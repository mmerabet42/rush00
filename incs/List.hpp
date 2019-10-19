#ifndef LIST_HPP
# define LIST_HPP

# include "LinkedList.hpp"

template <typename T>
class List
{
public:
	typedef LinkedList<T>* iterator;
	typedef const LinkedList<T>* const_iterator;

	List();
	~List();

	List(const List<T> &p_list);
	List<T> &operator=(const List<T> &p_list);

	const LinkedList<T> *begin() const;
	LinkedList<T> *begin();
	const LinkedList<T> *end() const;
	LinkedList<T> *end();
	const LinkedList<T> *last() const;
	LinkedList<T> *last();

	size_t size() const;

	void push(const T &p_value);
	void pop();

	void pushFront(const T &p_value);
	void popFront();

private:
	LinkedList<T> _end;
	LinkedList<T> *_begin;
	LinkedList<T> *_tail;
	size_t _size;
};

template <typename T>
List<T>::List()
	: _end((T())), _begin(&_end), _tail(nullptr), _size(0)
{}

template <typename T>
List<T>::~List()
{
	if (!this->_begin)
		return;

	LinkedList<T> *it;
	while (this->_begin != &this->_end)
	{
		it = this->_begin;
		this->_begin = this->_begin->next();
		delete it;
	}
}

template <typename T>
List<T>::List(const List<T> &p_list)
	: _end(T()), _begin(&_end), _tail(nullptr), _size(0)
{
	*this = p_list;
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &p_list)
{
	for (List<T>::const_iterator it = p_list.begin(); it != p_list.end(); it = it->next())
		push(it->value());
	return *this;
}

template <typename T>
const LinkedList<T> *List<T>::begin() const
{
	return this->_begin;
}

template <typename T>
LinkedList<T> *List<T>::begin()
{
	return this->_begin;
}

template <typename T>
const LinkedList<T> *List<T>::end() const
{
	return &this->_end;
}

template <typename T>
LinkedList<T> *List<T>::end()
{
	return &this->_end;
}

template <typename T>
const LinkedList<T> *List<T>::last() const
{
	return this->_tail;
}

template <typename T>
LinkedList<T> *List<T>::last()
{
	return this->_tail;
}

template <typename T>
size_t List<T>::size() const
{
	return this->_size;
}

template <typename T>
void List<T>::push(const T &p_value)
{
	LinkedList<T> *llist = new LinkedList<T>(p_value);
	if (!llist)
		return;

	llist->setPrev(this->_tail);
	if (this->_tail)
		this->_tail->setNext(llist);
	else
		this->_begin = llist;
	this->_tail = llist;
	llist->setNext(&this->_end);
	++this->_size;
}

template <typename T>
void List<T>::pop()
{
	if (!this->_tail)
		return;

	LinkedList<T> *tmp = this->_tail;
	this->_tail = this->_tail->prev();
	delete tmp;
	if (!this->_tail)
		this->_begin = &this->_end;
	else
		this->_tail->setNext(&this->_end);
	--this->_size;
}

template <typename T>
void List<T>::pushFront(const T &p_value)
{
	LinkedList<T> *llist = new LinkedList<T>(p_value);
	if (!llist)
		return;

	llist->setNext(this->_begin);
	this->_begin->setPrev(llist);
	this->_begin = llist;
	if (!this->_tail)
		this->_tail = this->_begin;
	++this->_size;
}

template <typename T>
void List<T>::popFront()
{
	if (!this->_tail)
		return;

	LinkedList<T> *tmp = this->_begin;
	this->_begin = this->_begin->next();
	this->_begin->setPrev(nullptr);
	delete tmp;
	if (this->_begin == &this->_end)
		this->_tail = nullptr;
	--this->_size;
}

#endif // LINKEDLIST_HPP
