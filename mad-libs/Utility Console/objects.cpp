//Demonstrates compiling C++ to C (if possible)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <cstring>

enum COLOR {RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, WHITE, BLACK};
enum TOOLTYPE {CROWBAR, WRENCH, POWERDRILL, LAZERPOINTER, GUN, PENCIL_PAPER, POWERSAW, BOMB_SHELL, PHOSPHER, PHOSPHOR_BOMB, CAULK, CON_BINE};
const char* const COLOR_NAMES[] = {"red", "orange", "yellow", "green", "blue", "violet", "white"};
const char* const TOOL_NAMES[] = {"crowbar",	"wrench",			"power drill",	"lazer pointer",
								"gun",		"pencil and paper",	"powersaw",		"bomb shell",
								"phospher",	"phospher bomb",	"caulk",		"con bine"};
const unsigned NUM_STRINGS = 3;
std::string stringTable[NUM_STRINGS];
enum STRINGTABLE_ID {HELP, END_GAME, START_GAME};
const char* IDNames[NUM_STRINGS]/* = {"Help", "EndGame", "StartGame"}*/;

class Marble
{
protected:
	COLOR color;
	unsigned int rareLevel;
public:
	Marble()
	{
		color = std::rand() % 7; //Black is only for black marbles
		rareLevel = (std::rand() % 10) + 1;
	}
	~Marble()
	{
	}
	COLOR GetColor() { return color; }
	unsigned int GetRareLevel() { return rareLevel; }
	void GrabMarble()
	{
		std::cout << "Grabbed a " << COLOR_NAMES[color] << " marble.\n";
	}
	void DepositMarble(unsigned int& score)
	{
		std::cout << "Deposited a " << COLOR_NAMES[color] << " marble in the exchange box.\n";
		score += 5 * rareLevel;
	}
};

class BlackMarble : public Marble
{
public:
	BlackMarble()
	{
		color = BLACK;
	}
	~BlackMarble()
	{
	}
	unsigned int GrabMarble(unsigned int& score, float& health)
	{
		//Choose a malicious action
		unsigned int actionNum = std::rand() % 10;
		switch (actionNum)
		{
		case 0:
			std::cout << "Grabbed a black marble.\n";
			break;
		case 1:
			std::cout << "The marble disappeared!\n";
			break;
		case 2:
			std::cout << "The marble suddenly became sharp and cut you.\nYou dropped the marble.\n";
			health -= 2;
			if (health > 0)
				std::cout << "You lost 2% health.\n";
			break;
		case 3:
			std::cout << "The marble burnt and exploded violently, injuring you.\n";
			health -= 10;
			if (health > 0)
				std::cout << "You lost 10% health.\n";
			break;
		case 4:
			if (score >= 200)
			{
				score -= 200;
				std::cout << "The marble sucked 200 points out of your score, grew to a boulder and ran you over.\n";
				health -= 15;
				if (health > 0)
					std::cout << "You lost 15% health.\n";
			}
			else
			{
				std::cout << "The marble sucked " << score << " point" << (score == 1 ? "" : "s") << " out of your score, grew to a boulder and ran you over.\n";
				score = 0;
				health -= 15;
				if (health > 0)
					std::cout << "You lost 15% health.\n";
			}
			break;
		case 5:
			std::cout << "The marble was actually a black hole in disguise, and it sucked you in.\n";
			health -= 100;
			break;
		case 6:
			std::cout << "This marble is a counterfit!\n";
			break;
		case 7:
			std::cout << "Grabbed a black marble.\n";
			break;
		case 8:
			std::cout << "Grabbed a black marble.\n";
			break;
		case 9:
			std::cout << "Grabbed a black marble.\n";
			break;
		}
		return actionNum;
	}
};

class Box
{
protected:
	unsigned int numMarbles;
	Marble* marbles;
public:
	Box(unsigned int maxSize)
	{
		numMarbles = (std::rand() % maxSize) + 1;
		marbles = new Marble[numMarbles];
	}
	~Box()
	{
		delete []marbles;
	}
	Marble& FetchMarble()
	{
		unsigned int marbleIndex = std::rand() % numMarbles;
		return marbles[marbleIndex];
	}

};

class BlackBox : public Box
{
	void FetchMarble()
	{
		std::cout << "You cannot open the blackbox.\n";
	}
};

class Tool
{
	friend ostream& operator<<(ostream& os, const Tool& obj);
protected:
	TOOLTYPE toolType;
public:
	Tool(TOOLTYPE tlType): toolType(tlType) {}
	~Tool()
	{
	}
	void UseTool(void* object)
	{
	}
	TOOLTYPE GetToolType() { return toolType; }
};

class ToolBox : public Box
{
protected:
	unsigned int numTools;
	Tool* tools;
public:
	ToolBox(): numTools(0) {}
	~ToolBox()
	{
		if (numTool > 0)
		{
			std::cout << "The toolbox exploded and the contents were lost into the world.\n";
			delete []tools;
		}
		else
		{
			std::cout << "The toolbox was destroyed.\n";
		}
	}
	void Look()
	{
		std::cout << "The toolbox contains:\n";
		for (int i = 0; i < numTools; i++)
			std::cout << tools[i] << "\n";
		std::cout << "\n";
	}
	Tool& FetchTool()
	{
		std::string tool2Fetch;
		std::cout << "Which tool do you want to fetch?\n";
		std::cin >> tool2Fetch;
		for (unsigned int i = 0; i < numTools; i++)
		{
			if (tool2Fetch == TOOL_NAMES[tools[i].GetToolType()])
				return tools[i];
		}
		std::cout << "That tool isn't in the toolbox.\n";
		return NULL;
	}
};

bool InitializeStrings();
void SafeShutdown();
std::string PrintString(std::string strName);
std::ostream& operator<<(std::ostream& os, const Tool& obj);

int main()
{
	unsigned int score = 0;
	float health = 100;
	std::srand(std::time(0));

	if (!InitializeStrings())
		return 1;

	std::cout << PrintString("StartGame");

	{
		char answer;
		std::cin >> answer;
		if (answer != 'y' && std::cin.rdbuf()->in_avail() > 1)
		{
			std::cout << "Chicken!\n";
			return 1;
		}
	}

	std::cout << PrintString("Help");

	bool returnedFromBox = true; //We want to see this message at the beginning
	while (health > 0 && score < 1000)
	{
		if (returnedFromBox == true)
		{
			std::cout << "\nBack to the marble room. " << health << "% health.\n";
			returnedFromBox = false;
		}
		std::string input;
		std::cin >> input;
		if (input == "exit")
			break;
		else if (input == "look")
		{
			if (std::cin.rdbuf()->in_avail() > 1)
			{
				std::string argument;
				std::cin >> argument;
				if (argument == "exchange")
				{
					std::cin >> argument;
					if (argument == "box")
					{
						std::cout << "It's a mailbox-like device, with a shaft behind that items slide down towards you and another shaft behind that lets your deposited items slide away from you.\n";
					}
				}
				else if (argument == "box")
					std::cout << "The box is filled with various colored marbles, some of which are black.\n";
				else if (argument == "table")
					std::cout << "It's an ordinary corkboard wooden textured table. Is there anything special about that?\n";
				else if (argument == "door")
					std::cout << "You'll never get out through that way unless you play the game!\n";
			}
			else
				std::cout << PrintString("RoomDesc");
		}
		else if (input == "deposit")
		{
		}
		else if (input == "withdraw")
		{
		}
		else if (input == "enter")
		{
		}
		else if (input == "exit")
		{
		}
		else if (input == "fetch")
		{
		}
		else if (input == "use")
		{
		}
		else if (input == "help")
		{
		}
		else// if (input == "")
		{
			std::cout << "You are not allowed to do that.\n";
		}
		//Cleanup the command line
		{
			std::string temp;
			while (std::cin.rdbuf()->in_avail() > 1)
				std::cin >> temp;
		}
	}
	if (health == 0)
		std::cout << "You are dead.\n";
	else if (score >= 1000)
	{
		std::cout << PrintString("EndGame");
	}
	SafeShutdown();
	return 0;
}

bool InitializeStrings()
{
	//Read the contents
	//Three ways to read the contents:
	//#1: Read the string ID in the file and store it for reference
	//CUT: #2: Read the numerical ID in the file and store it for reference
	//#3: Read the file without ID's and allocate ID's based on the order of addresses
	std::ifstream inFile("Object Strings.txt");
	if (inFile.fail())
		return false; //Error

	for (unsigned i = 0; i < NUM_STRINGS; i++)
	{
		std::string temp;
		std::getline(inFile, temp);
		temp.erase(0, 2);
		IDNames[i] = new char[temp.size()+1];
		strcpy(IDNames[i], temp.c_str());
		inFile.ignore(); //Ignore the quote
		while (true)
		{
			char input;
			inFile >> input;
			if (input == '"')
			{
				inFile >> input;
				/*if (input == '"')
					stringTable[i].push_back(input);
				else
					break;*/
				while (input == '"')
				{
					stringTable[i].push_back(input);
					inFile >> input;
				}
			}
			else
				stringTable[i].push_back(input);
		}
	}
	return true;
}

void SafeShutdown() //Deallocate memory used by IDNames[]
{
	for (unsigned i = 0; i < NUM_STRINGS; i++)
		delete []IDNames[i];
}

/* PrintString: Returns a string based off of the ID passed and does word wrapping.
   Word wrapping performed either automatically by the output device, dynamically
   by this function, or beforehand by an editor. */
std::string PrintString(std::string strID/*STRINGTABLE_ID strID*/)
{
	for (unsigned i = 0; i < NUM_STRINGS; i++)
	{
		if (strID == IDNames[i])
			return stringTable[i];
	}
	//return stringTable[strID];
}

std::ostream& operator<<(std::ostream& os, const Tool& obj)
{
	os << TOOL_NAMES[obj.toolType];
	return os;
}
