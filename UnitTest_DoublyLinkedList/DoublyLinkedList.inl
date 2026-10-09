#include "DoublyLinkedList.h"

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList() :_sentinel(), _size(0)
{
	_sentinel.prev = &_sentinel;
	_sentinel.next = &_sentinel;
}

template<typename T>
inline DoublyLinkedList<T>::~DoublyLinkedList()
{
	this->clear();
}

template<typename T>
inline const T& DoublyLinkedList<T>::ConstIterator::operator*() const
{
	assert(_list != nullptr);
	assert(_node != nullptr);
	assert(_node != &_list->_sentinel);
	return _node->data;
}

template<typename T>
inline typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--()
{
	assert(_list != nullptr);
	assert(_node != nullptr);
	assert(_node->prev != &_list->_sentinel);
	_node = _node->prev;
	return *this;
}

template<typename T>
inline typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator--(int)
{
	ConstIterator tmp = *this;
	--(*this);
	return tmp;
}

template<typename T>
inline typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++()
{
	assert(_list != nullptr);
	assert(_node != nullptr);
	assert(_node != &_list->_sentinel);
	_node = _node->next;// 次のノードへ
	return *this;
}

template<typename T>
inline typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator++(int)
{
	ConstIterator tmp = *this;
	++(*this);
	return tmp;
}

template<typename T>
inline typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator=(const typename DoublyLinkedList<T>::Iterator& other)
{
	_list = other._list;
	_node = other._node;
	return *this;
}

template<typename T>
inline typename bool DoublyLinkedList<T>::ConstIterator::operator==(const typename DoublyLinkedList<T>::ConstIterator& other) const
{
	return _list == other._list && _node == other._node;
}

template<typename T>
inline typename bool DoublyLinkedList<T>::ConstIterator::operator!=(const typename DoublyLinkedList<T>::ConstIterator& other) const
{
	return _list != other._list || _node != other._node;
}

template<typename T>
inline T& DoublyLinkedList<T>::Iterator::operator*() const
{
	assert(this->_list != nullptr);
	assert(this->_node != nullptr);
	assert(this->_node != &this->_list->_sentinel);
	return this->_node->data;
}

template<typename T>
inline typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--()
{
	assert(this->_list != nullptr);
	assert(this->_node != nullptr);
	assert(this->_node->prev != &this->_list->_sentinel);
	this->_node = this->_node->prev;
	return *this;
}

template<typename T>
inline typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--(int)
{
	Iterator tmp = *this;
	--(*this);
	return tmp;
}

template<typename T>
inline typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++()
{
	assert(this->_list != nullptr);
	assert(this->_node != nullptr);
	assert(this->_node != &this->_list->_sentinel);
	this->_node = this->_node->next;// 次のノードへ
	return *this;
}

template<typename T>
inline typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int)
{
	Iterator tmp = *this;
	++(*this);
	return tmp;
}

template<typename T>
inline bool DoublyLinkedList<T>::insert(const ConstIterator& pos, const T& data)
{

	if (pos._list != this)return false;

	Node* target = pos._node;
	Node* prev = target->prev;
	Node* n = new(std::nothrow) Node{ prev,target,data };

	if (n == nullptr)return false;

	prev->next = n;
	target->prev = n;
	++_size;

	return true;
}

template<typename T>
inline bool DoublyLinkedList<T>::erase(const ConstIterator& pos)
{

	if (pos._list != this)return false;
	Node* target = pos._node;

	if (target == &_sentinel)return false;

	Node* prev = target->prev;
	Node* next = target->next;

	prev->next = next;
	next->prev = prev;

	if (target) delete target;
	--_size;

	return true;
}

template<typename T>
inline bool DoublyLinkedList<T>::clear()
{
	Node* curr = _sentinel.next;
	if (!curr) return false;

	while (curr != &_sentinel)
	{
		Node* next = curr->next;
		delete curr;
		curr = next;
	}
	_sentinel.prev = &_sentinel;
	_sentinel.next = &_sentinel;
	_size = 0;

	return true;
}

template<typename T>
inline typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::cbegin() const
{
	return ConstIterator(this, _sentinel.next);
}

template<typename T>
inline typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::cend() const
{
	return ConstIterator(this, const_cast<Node*> (&_sentinel));
}

template<typename T>
inline typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin()
{
	return Iterator(this, _sentinel.next);
}

template<typename T>
inline typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end()
{
	return Iterator(this, &_sentinel);
}