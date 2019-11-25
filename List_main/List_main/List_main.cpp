#include <iostream>
#include "List.h"

int main()
{
	List<int> list;
	list.push_back(5);
	list.push_back(23);
	list.push_back(32);
	list.push_back(723);

	list.push_front(42);


	list.pop_back();
	list.pop_front();

}
