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


	while (!list.is_empty())
	{
		for (auto t : list)
			std::cout << t << " ";
		std::cout << std::endl;
		list.pop_front();
	}

	list.push_back(723);
	list.push_front(42);
	list.push_back(5);
	list.push_back(23);
	list.push_back(32);
	list.push_back(723);
	list.push_front(42);

	for (auto t : list)
		std::cout << t << " ";
	std::cout << std::endl;

	auto itr2 = list.begin() + 5;

	std::cout << *itr2 << std::endl;

	std::cout << list.front() << " " << list.back();

	list.clear();

	//list.emplace_front(5);

	list.insert(list.begin(), 3);

	list.emplace(list.begin(), 5);

}
