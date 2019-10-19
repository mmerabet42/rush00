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

	const List<T>::iterator begin() const;
	List<T>::iterator begin();
	const List<T>::iterator end() const;
	List<T>::iterator end();
	const List<T>::iterator last() const;
	List<T>::iterator last();

	size_t size() const;

	void push(const T &p_value);
	void pop();

	void pushFront(const T &p_value);
	void popFront();

	List<T>::iterator at(int p_index);
	List<T>::iterator at(const List<T>::iterator &p_it);

	List<T>::iterator insert(const T &p_value, const int &p_index);
	List<T>::iterator erase(const int &p_index);
	List<T>::iterator erase(List<T>::iterator &p_it);

	void clear();

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
	for (List<T>::const_iterator it = p_list.begin(); it != &p_list._end; it = it->next())
		push(it->value());
	return *this;
}

template <typename T>
const typename List<T>::iterator List<T>::begin() const
{
	return this->_begin;
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
	return this->_begin;
}

template <typename T>
const typename List<T>::iterator List<T>::end() const
{
	return &this->_end;
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
	return &this->_end;
}

template <typename T>
const typename List<T>::iterator List<T>::last() const
{
	return this->_tail;
}

template <typename T>
typename List<T>::iterator List<T>::last()
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

template <typename T>
typename List<T>::iterator List<T>::at(int p_index)
{
	while (p_index < 0)
		p_index += (int)this->_size;
	while (p_index >= (int)this->_size)
		p_index -= (int)this->_size;

	List<T>::iterator it = this->_begin;
	for (size_t i = 0; i < this->_size; ++i)
	{
		if (i == (size_t)p_index)
			return it;
		it = it->next();
	}
	return this->end();
}

template <typename T>
typename List<T>::iterator List<T>::at(const List<T>::iterator &p_it)
{
	List<T>::iterator it = this->_begin;
	for (size_t i = 0; i < this->_size; ++i)
	{
		if (p_it == it)
			return it;
		it = it->next();
	}
	return this->end();
}

template <typename T>
typename List<T>::iterator List<T>::insert(const T &p_value, const int &p_index)
{
	List<T>::iterator it = this->at(p_index);
	if (it == this->end())
		return this->end();

	LinkedList<T> *llist = new LinkedList<T>(p_value);
	if (!llist)
		return this->end();
	LinkedList<T> *tmp = it->next();
	it->setNext(llist);
	llist->setPrev(it);
	llist->setNext(tmp);
	tmp->setPrev(llist);
	++this->_size;
	return llist;
}

template <typename T>
typename List<T>::iterator List<T>::erase(const int &p_index)
{
	List<T>::iterator it = this->at(p_index);
	if (it == this->end())
		return this->end();

	LinkedList<T> *tmp = it->prev();
	if (!tmp)
		this->_begin = it->next();
	else
		tmp->setNext(it->next());
	it->next()->setPrev(tmp);
	tmp = it->next();
	delete it;
	--this->_size;
	return tmp;
}

template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator &p_it)
{
	List<T>::iterator it = this->at(p_it);
	if (it == this->end())
		return this->end();

	LinkedList<T> *tmp = it->prev();
	if (!tmp)
		this->_begin = it->next();
	else
		tmp->setNext(it->next());
	it->next()->setPrev(tmp);
	tmp = it->next();
	delete it;
	p_it = nullptr;
	--this->_size;
	return tmp;
}

template <typename T>
void List<T>::clear()
{
	LinkedList<T> *it = this->_begin;
	while (it != &this->_end)
	{
		LinkedList<T> *tmp = it->next();
		delete it;
		it = tmp;
	}
	this->_begin = &this->_end;
	this->_end.setPrev(nullptr);
	this->_tail = nullptr;
}

#endif // LINKEDLIST_HPP
