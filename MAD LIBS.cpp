//MAD LIBS word game. Ask questions to fill in word blanks for a story.

#include <iostream>
#include <string>

using namespace std;

void playFlyingBummy();

int main()
{
	playFlyingBummy();

	cout << "Press the enter key to exit";
	cin.ignore(cin.rdbuf()->in_avail() + 1);
	return 0;
}

void playFlyingBummy()
{
	string name1;
	string noun1;
	string adjetive1;
	string verb1;
	string date1;
	string verb2;
	string number1;
	string number2;
	string verb3;
	string noun2;

	cout << "Type a name: ";
	cin >> name1;
	cout << "Type a plural noun: ";
	cin >> noun1;
	cout << "Type an adjetive: ";
	cin >> adjetive1;
	cout << "Type an action verb: ";
	cin >> verb1;
	cout << "Type a date: ";
	cin >> date1;
	cout << "Type a verb: ";
	cin >> verb2;
	cout << "Type a number: ";
	cin >> number1;
	cout << "Type another number: ";
	cin >> number2;
	cout << "Type a verb: ";
	cin >> verb3;
	cout << "Type a noun: ";
	cin >> noun2;

	cout << "The Flying Bummy\n";
	cout << "The Flying Bummy lived in someone's " << name1 << ". The Flying Bummy been ";
	cout << "through many " << noun1 << ". People think the Flying Bummy is too ";
	cout << adjetive1 << " and " << verb1 << " too much. The Flying Bummy may be ";
	cout << adjetive1 << ", but you'll never guess what he did on " << date1 << ". He " << verb2 << " ";
	cout << number1 << " times on " << number2 << " buildings! He also " << verb3 << " on " << name1 << "'s ";
	cout << noun2 << "! Did he " << verb3 << " on your " << noun2 << "?\n";
}