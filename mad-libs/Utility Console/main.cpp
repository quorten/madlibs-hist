//Entry point for utility program
//Parses command line to call proper function
//The first parameter is the function to call, the rest of the command line
//is passed to that function. The program name is not passed to the function, but the
//function name is.

#include <iostream>
#include <cstring>

#include "examples.h"
#include "misc.h"

typedef int(*SubProg)(int, char*[]);

struct functions_t
{
	char* funcName;
	SubProg funcAddr;
};

const int numFunctions = 5;
functions_t funcList[numFunctions] = {
									{"SyntaxCheck", (SubProg)SyntaxCheck},
									{"ArgumentCheck", (SubProg)ArgumentCheck},
									{"PointerCheck", (SubProg)PointerCheck},
									{"Temporal", (SubProg)Temporal},
									{"Reformatter", (SubProg)Reformatter}
									 };

int main(int argc, char* argv[])
{
	std::cout << "Welcome to the Mad Libs's Utility Console.\n" << std::endl;
	if (argc > 1)
	{
		for (int i = 0; i < numFunctions; i++)
		{
			if (std::strcmp(argv[1], funcList[i].funcName) == 0)
				return funcList[i].funcAddr(argc - 1, argv + 1);
		}
	}
	else
	{
		int numArgs = 1;
		char* args[20];
		args[0] = new char[50];
		std::cout << "Type the command line: ";
		std::cin >> args[0];

		for (; std::cin.rdbuf()->in_avail() > 1; numArgs++)
		{
			args[numArgs] = new char[50];
			std::cin >> args[numArgs];
		}

		//Parse the function name
		for (int i = 0; i < numFunctions; i++)
		{
			if (std::strcmp(args[0], funcList[i].funcName) == 0)
				return funcList[i].funcAddr(numArgs, args);
		}
		//Deallocate memory
		for (int i = 0; i < numArgs; i++)
			delete []args[i];
	}
	return 1;
}