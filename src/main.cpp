#include <iostream>

#include "my_vector.h"

int main()
{
	my_vector<int> vector(10, 5);


	std::cout << "Data Structures working" << std::endl;
	std::cout << "Vector 7th element: " << vector[6] << std::endl;

	return 0;
}