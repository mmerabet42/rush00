#include <iostream>
#include "incs/List.hpp"

int main()
{
	List<int> a;

	a.push(3);
	a.push(56);
	a.push(895);
	a.push(1);

	List<int>::iterator err = a.insert(7, -1);

	for (List<int>::iterator it = a.begin(); it != a.end(); it = it->next())
		std::cout << it->value() << std::endl;
	std::cout << std::endl << std::endl;
	a.erase(err);
	for (List<int>::iterator it = a.begin(); it != a.end(); it = it->next())
		std::cout << it->value() << std::endl;
	return 0;
}
