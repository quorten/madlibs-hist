//MAD LIBS word game. Ask questions to fill in word blanks for a story.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void playFlyingBummy();
void playGdayMate();

int main()
{
	//Pick a story at random
	srand(time(0));
	int randPick = rand() % 2;
	switch (randPick)
	{
	case 0:
		playFlyingBummy();
		break;
	case 1:
		playGdayMate();
		break;
	}
	cout << "Press the enter key to exit";
	cin.ignore(cin.rdbuf()->in_avail() + 1);
	return 0;
}

void playFlyingBummy()
{
	string name1;
	string noun1;
	string preposition1;
	string noun2;
	string adjetive1;
	string verb1;
	string date1;
	string verb2;
	string number1;
	string number2;
	string noun3;
	string verb3;
	string noun4;

	cout << "Type a name: ";
	cin >> name1;
	cout << "Type a noun: ";
	cin >> noun1;
	cout << "Type a preposition: ";
	cin >> preposition1;
	cout << "Type a plural noun: ";
	cin >> noun2;
	cout << "Type an adjetive: ";
	cin >> adjetive1;
	cout << "Type an action verb ending with s: ";
	cin >> verb1;
	cout << "Type a date: ";
	cin >> date1;
	cout << "Type a verb: ";
	cin >> verb2;
	cout << "Type a number: ";
	cin >> number1;
	cout << "Type another number: ";
	cin >> number2;
	cout << "Type a plural noun: ";
	cin >> noun3;
	cout << "Type a past tense verb: ";
	cin >> verb3;
	cout << "Type a noun: ";
	cin >> noun4;

	cout << "\nThe Flying Bummy\n";
	cout << "\n";
	cout << "The Flying Bummy lived in " << name1 << "'s " << noun1 << ". The Flying Bummy been\n";
	cout << preposition1 << " many " << noun2 << ". People think the Flying Bummy is too\n";
	cout << adjetive1 << " and " << verb1 << " too much. The Flying Bummy may be\n";
	cout << adjetive1 << ", but you'll never guess what he did on " << date1 << ". He " << verb2 << "\n";
	cout << number1 << " times on " << number2 << " " << noun3 << "! He also " << verb3 << " on " << name1 << "'s\n";
	cout << noun4 << "! Did he " << verb3 << " on your " << noun4 << "?\n";
}

void playGdayMate()
{
	string noun1;
	string noun2;
	string greeting1;
	string verb1;
	string noun3;
	string verb2;
	string clothing1;
	string verb3;
	string verb4;
	string place1;

	cout << "Type a noun: ";
	cin >> noun1;
	cout << "Type another noun: ";
	cin >> noun2;
	cout << "Type an -ed action verb: ";
	cin >> verb1;
	cout << "Type a greeting: ";
	cin >> greeting1;
	cout << "Type a noun: ";
	cin >> noun3;
	cout << "Type an action verb: ";
	cin >> verb2;
	cout << "Type a clothing item: ";
	cin >> clothing1;
	cout << "Type an action verb: ";
	cin >> verb3;
	cout << "Type another action verb: ";
	cin >> verb4;
	cout << "Type a place: ";
	cin >> place1;

	cout << "\nG'day Mate!\n";
	cout << "\n";
	cout << "Now that " << noun1 << " was gone, Mai was happy. She was so happy that she\n";
	cout << "gave Valen a " << noun2 << " for a present. Then, Mai " << verb1 << "\n";
	cout << "on the beach. Much to her surprise, she found Yugi, Joey, and Kaibad\n";
	cout << "on the beach too. Soon after, Valen showed up and said \"" << greeting1 << "\n";
	cout << "mate!\"  Joey took it as an insult and started a " << noun3 << " fight. Joey\n";
	cout << "won, but Valen still tried to " << verb2 << " that he was better.\n";
	cout << "Yami was so bored of the fight that he took off his " << clothing1 << ".\n";
	cout << "This made Fea scream and " << verb3 << ". The moral of the story is\n";
	cout << "don't " << verb4 << " in the " << place1 << ".\n";
}