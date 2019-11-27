#pragma once
#include <list>


template<typename T>
class List
{
private:
	struct Node;

	Node* lbegin;
	Node* lend;

	int size;
public:
	struct ListItr;

	typename List<T>::ListItr begin();
	typename List<T>::ListItr end();
	const typename List<T>::ListItr cbegin();
	const typename List<T>::ListItr cend();

	List();
	~List();
	
	bool is_empty();
	int list_size();

	T& front();
	T& back();

	void push_back(T elem);
	void push_front(T elem);
	void pop_back();
	void pop_front();
	void insert(List<T>::ListItr pos, T elem);

	template<typename... Args>
	void emplace_back(Args&&... args);
	template<typename... Args>
	void emplace_front(Args&&... args);
	template<typename... Args>
	void emplace(List<T>::ListItr pos, Args&&... args);

	void clear();
};

template<typename T>
struct List<T>::Node
{
	T* value;
	Node* next_node;
	Node* prev_node;

	Node();
	~Node();
	Node(Node* _next_node, Node* _prev_node);
	Node(T _value, Node* _next_node, Node* _prev_node);
	template<typename... Args>
	Node(Args&&...args, Node* _next_node, Node* _prev_node);
};

template<typename T>
struct List<T>::ListItr
{
	List<T>::Node* this_node;

	List<T>::ListItr& operator++();
	List<T>::ListItr& operator++(int);

	List<T>::ListItr& operator--();
	List<T>::ListItr& operator--(int);

	List<T>::ListItr operator+(int num); //Тебя здесь быть не должно

	bool operator==(const List<T>::ListItr& itr);
	bool operator!=(const List<T>::ListItr& itr);

	T& operator*();

	ListItr() = default;
	ListItr(Node* new_node);
	~ListItr();
};

template<typename T>
typename List<T>::ListItr& List<T>::ListItr::operator++()
{
	this->this_node = this->this_node->next_node;
	return *this;
}

template<typename T>
typename List<T>::ListItr& List<T>::ListItr::operator++(int)
{
	this->this_node = this->this_node->next_node;
	return *this;
}

template<typename T>
typename List<T>::ListItr& List<T>::ListItr::operator--()
{
	this->this_node = this->this_node->prev_node;
	return *this;
}

template<typename T>
typename List<T>::ListItr& List<T>::ListItr::operator--(int)
{
	this->this_node = this->this_node->prev_node;
	return *this;
}

template<typename T>
typename List<T>::ListItr List<T>::ListItr::operator+(int num)
{
	List<T>::ListItr temp_itr = *this;
	for (int i = 0; i < num; i++)
	{
		if (temp_itr.this_node->next_node == nullptr) break;
		temp_itr++;
	}
	return temp_itr;
}

template<typename T>
bool List<T>::ListItr::operator==(const List<T>::ListItr& itr)
{
	return this->this_node == itr.this_node();
}

template<typename T>
bool List<T>::ListItr::operator!=(const List<T>::ListItr& itr)
{
	return this->this_node != itr.this_node;
}

template<typename T>
T& List<T>::ListItr::operator*()
{
	return *(this->this_node->value);
}

template<typename T>
List<T>::ListItr::ListItr(Node* new_node)
{
	this->this_node = new_node;
}

template<typename T>
List<T>::ListItr::~ListItr()
{

}

template<typename T>
typename List<T>::ListItr List<T>::begin()
{
	return List<T>::ListItr(this->lbegin);
}

template<typename T>
typename List<T>::ListItr List<T>::end()
{
	return List<T>::ListItr(this->lend);
}

template<typename T>
const typename List<T>::ListItr List<T>::cbegin()
{
	return List<T>::ListItr(this->lbegin);
}

template<typename T>
const typename List<T>::ListItr List<T>::cend()
{
	return List<T>::ListItr(this->lend);
}

template<typename T>
List<T>::Node::Node()
{
	value = nullptr;
	next_node = nullptr;
	prev_node = nullptr;
}

template<typename T>
List<T>::Node::~Node()
{
	delete this->value;
	delete this->next_node;
}

template<typename T>
List<T>::Node::Node(Node* _next_node, Node* _prev_node)
{
	value = nullptr;
	next_node = _next_node;
	prev_node = _prev_node;
}

template<typename T>
List<T>::Node::Node(T _value, Node* _next_node, Node* _prev_node)
{
	value = new T(_value);
	next_node = _next_node;
	prev_node = _prev_node;
}

template<typename T>
template<typename ...Args>
List<T>::Node::Node(Args && ...args, Node * _next_node, Node * _prev_node)
{
	value = new T(std::forward<Args>(args)...);
	next_node = _next_node;
	prev_node = _prev_node;
}

template<typename T>
List<T>::List()
{
	lend = new Node();
	lbegin = lend;
	size = 0;
}

template<typename T>
List<T>::~List()
{
	delete this->lbegin;
}

template<typename T>
bool List<T>::is_empty()
{
	return size == 0;
}

template<typename T>
int List<T>::list_size()
{
	return this->size;
}

template<typename T>
T& List<T>::front()
{
	return *(this->lbegin->value);
}

template<typename T>
T& List<T>::back()
{
	return *(this->lend->prev_node->value);
}

template<typename T>
void List<T>::push_back(T elem)
{
	if (size == 0)
	{
		this->lbegin = new Node(elem, this->lend, nullptr);
		this->lend->prev_node = this->lbegin;
		size++;
	}
	else
	{
		Node* temp_ptr = this->lend->prev_node;
		this->lend->prev_node = new Node(elem, this->lend, temp_ptr);
		temp_ptr->next_node = this->lend->prev_node;
		size++;
	}
}

template<typename T>
void List<T>::push_front(T elem)
{
	if (size == 0)
	{
		this->lbegin = new Node(elem, this->lend, nullptr);
		this->lend->prev_node = this->lbegin;
		size++;
	}
	else
	{
		Node* temp_ptr = this->lbegin;
		this->lbegin = new Node(elem, temp_ptr, nullptr);
		temp_ptr->prev_node = this->lbegin;
		size++;
	}
}

template<typename T>
void List<T>::pop_back()
{
	if (size != 0)
	{
		Node* temp_ptr = this->lend->prev_node;

		if (temp_ptr->prev_node)
			temp_ptr->prev_node->next_node = this->lend;
		else
			lbegin = lend;

		this->lend->prev_node = temp_ptr->prev_node;
		temp_ptr->next_node = nullptr;
		delete temp_ptr;
		--size;
	}
}

template<typename T>
void List<T>::pop_front()
{
	if (size != 0)
	{
		Node* temp_ptr = this->lbegin;
		this->lbegin = temp_ptr->next_node;
		temp_ptr->next_node = nullptr;
		delete temp_ptr;
		if (temp_ptr->next_node == lend)
			temp_ptr = lend;
		--size;
	}
}

template<typename T>
void List<T>::insert(List<T>::ListItr pos, T elem)
{
	List<T>::ListItr temp_itr = pos;
	temp_itr--;

	pos.this_node->prev_node = new Node(elem, pos.this_node, temp_itr.this_node);

	if (!(temp_itr.this_node == this->lend || temp_itr.this_node == nullptr))
		temp_itr.this_node->next_node = pos.this_node->prev_node;
	else
	{
		this->lbegin = pos.this_node->prev_node;
		this->lbegin->prev_node = nullptr;
	}
}

template<typename T>
void List<T>::clear()
{
	this->lend->prev_node->next_node = nullptr;
	delete this->lbegin;
	this->lbegin = this->lend;
	this->lend->prev_node = lbegin;
	this->size = 0;
}

template<typename T>
template<typename ...Args>
void List<T>::emplace_back(Args && ...args)
{
	if (size == 0)
	{
		this->lbegin = new Node(std::forward<Args>(args)..., this->lend, nullptr);
		this->lend->prev_node = this->lbegin;
		size++;
	}
	else
	{
		Node* temp_ptr = this->lend->prev_node;
		this->lend->prev_node = new Node(std::forward<Args>(args)..., this->lend, temp_ptr);
		temp_ptr->next_node = this->lend->prev_node;
		size++;
	}
}

template<typename T>
template<typename ...Args>
void List<T>::emplace_front(Args && ...args)
{
	if (size == 0)
	{
		this->lbegin = new Node(std::forward<Args>(args)..., this->lend, nullptr);
		this->lend->prev_node = this->lbegin;
		size++;
	}
	else
	{
		Node* temp_ptr = this->lbegin;
		this->lbegin = new Node(std::forward<Args>(args)..., temp_ptr, nullptr);
		temp_ptr->prev_node = this->lbegin;
		size++;
	}
}

template<typename T>
template<typename ...Args>
void List<T>::emplace(List<T>::ListItr pos, Args && ...args)
{
	List<T>::ListItr temp_itr = pos;
	temp_itr--;

	pos.this_node->prev_node = new Node(std::forward<Args>(args)..., pos.this_node, temp_itr.this_node);

	if (!(temp_itr.this_node == this->lend || temp_itr.this_node == nullptr))
		temp_itr.this_node->next_node = pos.this_node->prev_node;
	else
	{
		this->lbegin = pos.this_node->prev_node;
		this->lbegin->prev_node = nullptr;
	}
}
