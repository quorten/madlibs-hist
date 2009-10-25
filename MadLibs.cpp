//A simple Mad Libs game which loads a random story from a file.
//Later a configuration pannel may be added.

#ifdef MSVC
#include <io.h> //The file finding code uses WINDOWS APIs
#else
#include <dirent.h> //POSIX compliant code
#endif

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct MadLibsStory
{
	string titleForPrev; //When allowed to pick a story
	vector<string> storyFragments;
	vector<string> customWords;
	vector<unsigned> wordRefs;
};

inline bool FindFiles(vector<string>& files);
void AskQuestion(string qBegin, string& wordDesc);
void FormatCustomWord(string& wordDesc);

int main()
{
	//First find all the story files in the directory
	vector<string> files;

	if (!FindFiles(files))
	{
		cout << "ERROR: Could not find any story files.\n";
		return 1;
	}

	//Pick a random story file
	srand(time(NULL));
	unsigned story = rand() % files.size();

	//Read the whole file into memory
	//We have to parse the file to find out how many stories it has since it does not
	//have a table of contents.
	FILE* fp = fopen(files[story].c_str(), "rb");
	fseek(fp, 0, SEEK_END);
	unsigned fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buffer = new char[fileSize];
	fread(buffer, fileSize, 1, fp);
	fclose(fp);

	//Since we read the whole file this way, we will have to properly format newlines.
	string fileContents;
	for (unsigned i = 0; i < fileSize; i++)
	{
		if (buffer[i] != '\r')
			fileContents.push_back(buffer[i]);
		else
		{
			if (buffer[i+1] == '\n') //CR+LF
				i++;
			fileContents.push_back('\n');
		}
	}
	delete []buffer;

	//Parse the file
	//We have to format three arrays: story fragments, custom words, and word references
	//Story fragments and word references are interleaved to create the story
	vector<MadLibsStory> stories;

	unsigned curWordRef = 0;
	bool inTitle = true; //The first line should be a title
	{ //Allocate memory for the first story
		MadLibsStory temp;
		temp.storyFragments.push_back(string(""));
		stories.push_back(temp);
	}
	for (unsigned i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i] != '(')
		{
			for (; i < fileContents.size() && fileContents[i] != '('; i++)
			{
				//Check for end tag
				const string endTag("\n\nEND STORY");
				bool foundEndTag = true;
				for (unsigned j = i, k = 0; j < i + endTag.size(); j++, k++)
				{
					if (j == fileContents.size())
					{
						//The end of file came early
						foundEndTag = false;
						break;
					}
					if (fileContents[j] != endTag[k])
					{
						foundEndTag = false;
						break;
					}
				}
				if (foundEndTag == true)
				{
					i += 11;
					if (i == fileContents.size())
						goto storyEnd;
					else if (fileContents[i] != '\n')
						break;
					//if (fileContents[i] != '\n')
					i++; //Skip double newline
					{ //Allocate memory for the next story
						MadLibsStory temp;
						temp.storyFragments.push_back(string(""));
						stories.push_back(temp);
					}
					//Reset proper variables
					curWordRef = 0;
					inTitle = true;
					goto storyEnd;
				}

				//Do the normal story fragment copy
				stories.back().storyFragments.back().push_back(fileContents[i]);

				if (inTitle == true)
				{
					if (fileContents[i] != '\n')
						stories.back().titleForPrev.push_back(fileContents[i]);
					else
					{
						inTitle = false;
						//if (fileContents[i+1] != '\n')
							//Then we should tell the user about this
							//We might temporarily fix it too
					}
				}
			}
			i--;
			storyEnd: ;
		}
		else
		{
			i++;
			if (fileContents[i] == '(')
			{
				//These parentheses are meant for the story content
				for (; i < fileContents.size() && fileContents[i] == '('; i++)
					stories.back().storyFragments.back().push_back(fileContents[i]);
				i--;
			}
			else
			{
				//We found a custom word
				stories.back().customWords.push_back(string(""));
				//Save the custom word temporarily
				for (; i < fileContents.size() && fileContents[i] != ')'; i++)
					stories.back().customWords.back().push_back(fileContents[i]);
				//Search for a match with this custom word and previous custom words
				bool foundReuse = false;
				for (unsigned i = 0; i < stories.back().customWords.size() - 1; i++)
				{
					if (stories.back().customWords.back() == stories.back().customWords[i])
					{
						//We have a match. Fill in the proper word reference
						stories.back().wordRefs.push_back(i);
						//Delete reused word
						stories.back().customWords.pop_back();
						foundReuse = true;
						break;
					}
				}
				if (foundReuse == false)
				{
					//No match found. Store reference and keep stored word
					stories.back().wordRefs.push_back(curWordRef);
					curWordRef++;
				}
				stories.back().storyFragments.push_back(string(""));
			}
			if (inTitle == true)
			{
				stories.back().titleForPrev.push_back('?');
			}
		}
	}
	if (inTitle == true)
	{
		//We have a newline at the end of the file, but of course no story
		stories.pop_back();
	}

	//Pick a random story from the file
	story = rand() % stories.size();

	//Ask the words
	FormatCustomWord(stories[story].customWords.front());
	bool sayAnotherNext = false;
	for (unsigned i = 0; i < stories[story].customWords.size(); i++)
	{
		if (sayAnotherNext == true) //This flag is set at the end of the loop
		{
			sayAnotherNext = false;
			//If the next type of word is the same type, then set the
			//flag so next time we say "Type another ..."
			if (i < stories[story].customWords.size() - 1)
				FormatCustomWord(stories[story].customWords[i+1]);
			if (i < stories[story].customWords.size() - 1 && stories[story].customWords[i] == stories[story].customWords[i+1])
				sayAnotherNext = true;
			//Now we can change the word when we ask the question
			AskQuestion(string("Type another "), stories[story].customWords[i]);
		}
		else
		{
			//If the next type of word is the same type, then set the
			//flag so next time we say "Type another ..."
			if (i < stories[story].customWords.size() - 1)
				FormatCustomWord(stories[story].customWords[i+1]);
			if (i < stories[story].customWords.size() - 1 && stories[story].customWords[i] == stories[story].customWords[i+1])
				sayAnotherNext = true;
			//If the first letter of the word is a vowel (a, e, i, o, u, not
			//including y), then say "Type an ..."
			const string accptdVowls("aeiou");
			bool useAn = false;
			for (unsigned j = 0; j < 5; j++)
			{
				if (stories[story].customWords[i][0] == accptdVowls[j])
				{
					useAn = true;
					break;
				}
			}
			if (useAn == true)
				AskQuestion(string("Type an "), stories[story].customWords[i]);
			//Otherwise, just say "Type a ..."
			else
				AskQuestion(string("Type a "), stories[story].customWords[i]);
				//cout << "Type a " << stories[story].customWords[i] << ":\n";
		}
	}

	//Display the story
	cout << endl;
	for (unsigned i = 0; i < stories[story].storyFragments.size() - 1; i++)
		cout << stories[story].storyFragments[i] <<
			stories[story].customWords[stories[story].wordRefs[i]];
	cout << stories[story].storyFragments.back() << endl;
	return 0;
}

inline bool FindFiles(vector<string>& files)
{
#ifdef MSVC

	finddata_t findData;
	intptr_t findHandle;

	findHandle = findfirst("*.mlb", &findData);
	if (findHandle == -1)
		return false;

	files.push_back(string(findData.name));
	while (findnext(findHandle, &findData) == 0)
	{
		files.push_back(string(findData.name));
	}
	findclose(findHandle);
	return true;

#else

	DIR *d = opendir(".");
	if (d == NULL)
		return false;

	struct dirent *de;
	while (de = readdir(d))
	{
		files.push_back(string(de->d_name));
		if (files.back().find(".mlb") != files.back().size() - 4)
			files.pop_back();
	}
	closedir(d);
	if (files.size() > 0)
		return true;
	else
		return false;

#endif
}

void AskQuestion(string qBegin, string& wordDesc)
{
	string answer;
	cout << qBegin << wordDesc << ": ";
	getline(cin, answer, '\n');
	wordDesc = answer;
}

//Erases the numeric ID from the custom word description
void FormatCustomWord(string& wordDesc)
{
	//NOTE: Here we consider it pointless to have only a
	//number for the word description.
	unsigned numBegin;
	bool inNumber = true;
	for (numBegin = wordDesc.size() - 1; numBegin > 0 && inNumber == true; numBegin--)
	{
		const string numbers("0123456789");
		inNumber = false;
		for (unsigned j = 0; j < 10; j++)
		{
			if (numbers[j] == wordDesc[numBegin])
				inNumber = true;
		}
	}
	numBegin += 2;	//Undo the extra numBegin-- and...
					//Don't erase the last letter of the description
	wordDesc.erase(numBegin);
}
