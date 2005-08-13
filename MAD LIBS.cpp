//MAD LIBS word game. Ask questions to fill in word blanks for a story.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void playFlyingBummy();
void playGdayMate();
void playMonstersCame();

int main()
{
	//Pick a story at random
	srand(time(0));
	int randPick = rand() % 3;
	switch (randPick)
	{
	case 0:
		playFlyingBummy();
		break;
	case 1:
		playGdayMate();
		break;
	case 2:
		playMonstersCame();
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

void playMonstersCame()
{
	string noun1;
	string date2;
	string name3;
	string country4;
	string noun5;
	string adverb6;
	string adjetive7;
	string noun8;

	cout << "Type a plural noun: ";
	cin >> noun1;
	cout << "Type a date: ";
	cin >> date2;
	cout << "Type a name: ";
	cin >> name3;
	cout << "Type a country, state, contenent: ";
	cin >> country4;
	cout << "Type a noun: ";
	cin >> noun5;
	cout << "Type an adverb: ";
	cin >> adverb6;
	cout << "Type an adjetive: ";
	cin >> adjetive7;
	cout << "Type another noun: ";
	cin >> noun8;

	cout << "\nThe Day the " << noun1 << " came\n";
	cout << "\n";
	cout << "Have you ever seen " << noun1 << " from outerspace. This will be the first\n";
	cout << "time you discover such a wierd thing. At " << date2 << ", many " << noun1 << " came\n";
	cout << "from the plannet " << name3 << ". They Invaded earth and took over\n";
	cout << country4 << " before you knew it. A probe alien stoll " << noun5 << " and " << adverb6 << "\n";
	cout << "trough a " << adjetive7 << " ally. " << noun5 << " was the super important data to destroy\n";
	cout << "all the envading alliens! Now the alliens, developed a wepon to destroy the\n";
	cout << "sun and tear apart the galexy, exept for them! But nothing to fear, Super \n";
	cout << "" << noun8 << " could rescue " << noun5 << " so the alliens couldn't destroy the galexy and\n";
	cout << "get rid of all the invading alliens. So Super " << noun8 << " did that.\n";
}