#pragma once

#include "bignum.h"
#include <iostream>

/*
* BigList is structure like a deque (double-ended-queue) but without chunks
* 
* 
*/

// Node of container
template <typename T>
struct _Node
{
	_Node() {}
	_Node(T dt) : data(dt) {}
	~_Node() {}

	T data;
	_Node* prev = nullptr;
	_Node* next = nullptr;

};

// otherside functions
template <typename T>
_Node<T>* createNode(T data)
{
	_Node<T> *newNode = new _Node<T>(data);

	if (!newNode)
		return nullptr;

	newNode->data = data;
	newNode->prev = newNode->next = nullptr;

	return newNode;
}



template <class T>
class BigList;

// Specilization
template<class T>
std::ostream& operator<<(std::ostream& out, const BigList<T>& num)
{
	_Node<T>* it;
	it = num.front;

	out << "BigList(";
	while (it)
	{
		out << it->data;
		if (it->next)
			out << ", ";
		it = it->next;
	}
	out << ")";

	return out;
}

// Container
template <class T>
class BigList
{
	BigNum _size;
	_Node<T> *front	= nullptr;
	_Node<T> *back	= nullptr;

public:
	BigList() : _size(0)    { };
	~BigList() { clear(); };

	//void resize(BigNum &size);
	BigNum size() { return _size;  };
	
	// front
	void push_front(T data);
	void pop_front();

	// back
	void push_back(T data);
	void pop_back();

	void clear();
	friend std::ostream& operator<< <T>(std::ostream& out, const BigList& num);

	T& operator[](BigNum index) 
	{
		if (_size < index + 1)
			throw std::invalid_argument("Index out of the range.");
		return moveAt(index)->data; 
	}

	bool isEmpty() { return !front; }

	void insert(T data, BigNum index);
	void erase(BigNum index);

private:
	_Node<T>* moveAt(BigNum& index);
};


// Realization
template<class T>
void BigList<T>::push_front(T data)
{
	_Node<T>* newNode = createNode(data);

	if (!newNode)
		throw "Memory is overflow.";

	if (!front)
	{
		front = back = newNode;
	}
	else
	{
		newNode->next = front;
		front->prev = newNode;
		front = newNode;
	}

	++_size;
}

template<class T>
void BigList<T>::pop_front()
{
	if (isEmpty())
		return;

	_Node<T> *oldNode = front;
	front = front->next;
	front->prev = nullptr;

	if (!front)
		back = nullptr;
	--_size;

	delete oldNode;
}

template<class T>
void BigList<T>::push_back(T data)
{
	_Node<T>* newNode = createNode(data);

	if (!newNode)
		throw "Memory is overflow.";

	if (!back)
	{
		front = back = newNode;
	}
	else
	{
		newNode->prev = back;
		back->next = newNode;
		back = newNode;
	}

	++_size;
}

template<class T>
void BigList<T>::pop_back()
{
	if (isEmpty())
		return;


	_Node<T>* oldNode = back;
	
	back = back->prev;
	if (back)
		back->next = nullptr;

	if (!back)
		front = nullptr;
	--_size;

	delete oldNode;
}

template<class T>
void BigList<T>::clear()
{
	_Node<T>* currentNode = front;

	while (currentNode)
	{
		_Node<T>* nextNode = currentNode->next;

		delete currentNode;
		currentNode = nextNode;
	}

	front = back = nullptr;
	_size = 0;
}


// Metod insert item after item with index = "BigNum index"
template<class T>
void BigList<T>::insert(T data, BigNum index)
{
	if (!front && !back) // size = 0;
	{
		push_back(data);
		return;
	}

	if (_size < (index + 1))
	{
		throw std::invalid_argument("Index out of the range");
	}

	_Node<T> *newNode = createNode(data);
	_Node<T> *indexNode = moveAt(index);

	_Node<T>* afterNode = indexNode->next;

	indexNode->next = newNode;
	newNode->prev = indexNode;
	newNode->next = afterNode;

	if (afterNode)
		afterNode->prev = newNode;

	++_size;
}

template<class T>
void BigList<T>::erase(BigNum index)
{
	if (_size < (index + 1))
		throw "Index out of the range";

	_Node<T>* indexNode = moveAt(index);
	
	if (!indexNode->next)
	{
		pop_back();
		return;
	}
	if (!indexNode->prev)
	{
		pop_front();
		return;
	}
	
	_Node<T>* afterNode = indexNode->next;
	_Node<T>* beforeNode = indexNode->prev;

	afterNode->prev = beforeNode;
	beforeNode->next = afterNode;
	
	delete indexNode;
	--_size;
}

template<class T>
_Node<T>* BigList<T>::moveAt(BigNum& index)
{
	_Node<T>* pointer = front;
	while ((index))
	{
		pointer = pointer->next;
		--index;
	}

	return pointer;
}
