//Dedicated to demonstrating things, of course!

#include <iostream>
#include <cstring>


int SyntaxCheck(int argc, char* argv[])
{
	std::cout << "No syntax checking example present!\n";
	return 0;
}

int ArgumentCheck(int argc, char* argv[])
{
	std::cout << argc << " arguments passed." << std::endl;
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;
	std::cout << "Press enter to continue . . ." << std::endl;
	std::cin.ignore(std::cin.rdbuf()->in_avail()+1);
	return 0;
}

int PointerCheck(int argc, char* argv[])
{
	std::cout << "Checking pointer incrementing system..." << std::endl;
	int intArray[4] = {1, 2, 3, 4};
	int* intPtr = &intArray[0];
	std::cout << *intPtr << std::endl;
	intPtr++;
	std::cout << *intPtr << std::endl;
	intPtr--;
	intPtr += 3;
	std::cout << *intPtr << std::endl;
	std::cout << "Press enter to continue . . ." << std::endl;
	std::cin.ignore(std::cin.rdbuf()->in_avail()+1);
	return 0;
}