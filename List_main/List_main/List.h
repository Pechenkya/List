#pragma once

template<typename T>
struct ListItr;

template<typename T>
class List
{
private:
	struct Node;

	Node* begin;
	Node* end;

	int size;
public:
	List();
	~List();
	void push_back(T elem);
	void push_front(T elem);
	void pop_back();
	void pop_front();
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
};

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
	delete this->prev_node;
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
List<T>::List()
{
	begin = nullptr;
	end = new Node();
	size = 0;
}

template<typename T>
List<T>::~List()
{
	delete this->begin;
}

template<typename T>
void List<T>::push_back(T elem)
{
	if (size == 0)
	{
		this->begin = new Node(elem, this->end, nullptr);
		this->end->prev_node = this->begin;
		size++;
	}
	else
	{
		Node* temp_ptr = this->end->prev_node;
		this->end->prev_node = new Node(elem, this->end, temp_ptr);
		temp_ptr->next_node = this->end->prev_node;
		size++;
	}
}

template<typename T>
void List<T>::push_front(T elem)
{
	if (size == 0)
	{
		this->begin = new Node(elem, this->end, nullptr);
		this->end->prev_node = this->begin;
		size++;
	}
	else
	{
		Node* temp_ptr = this->begin;
		this->begin = new Node(elem, temp_ptr, nullptr);
		temp_ptr->prev_node = this->begin;
		size++;
	}
}

template<typename T>
void List<T>::pop_back()
{
	if (size != 0)
	{
		Node* temp_ptr = this->end->prev_node;
		temp_ptr->prev_node->next_node = this->end;
		this->end->prev_node = temp_ptr->prev_node;
		temp_ptr->prev_node = nullptr;
		temp_ptr->next_node = nullptr;
		delete temp_ptr;
	}
}

template<typename T>
void List<T>::pop_front()
{
	if (size != 0)
	{
		Node* temp_ptr = this->begin;
		this->begin = temp_ptr->next_node;
		temp_ptr->next_node = nullptr;
		delete temp_ptr;
	}
}