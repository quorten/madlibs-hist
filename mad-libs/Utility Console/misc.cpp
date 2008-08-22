//Main file for miscilanious tiny utilities

#include <fstream>
#include <string>
#include <iostream>
#include <cctype> //Reformatter
#include <cstdlib> //Reformatter
#include <queue> //Reformatter

using namespace std;

/* Extract tiny strings from source file into string file,
	generating an automatic name for each string. Can also
	do the reverse, taking strings from string file and
	putting them back in the source file.
   Command Line: Temporal <sourcefile> <stringfile> direction=[EXTRACT | INTRACT] */
int Temporal(int argc, char* argv[])
{
	//enum PARSE_DIRECTION {EXTRACT, INTRACT};
	string sourceFile;
	string stringFile;
	string direction = argv[3];

	//Read first file
	{
		ifstream inFile(argv[1]);
		if (inFile.fail())
			return 1;

		while (inFile.eof() == false)
		{
			string temp;
			getline(inFile, temp);
			sourceFile.append(temp);
			sourceFile.push_back('\n');
		}
		//Remove one extra newline added
		sourceFile.erase(sourceFile.end() - 1);
	}
	//Read second file
	{
		ifstream inFile(argv[2]);
		if (inFile.fail())
			return 1;

		while (inFile.eof() == false)
		{
			string temp;
			getline(inFile, temp);
			stringFile.append(temp);
			stringFile.push_back('\n');
		}
		//Don't remove one extra newline added
		//data.erase(stringFile.end() - 1);
	}

	//Do the work
	if (direction == "EXTRACT")
	{
		for (unsigned i = 0, count = 1; i < sourceFile.size(); count++)
		{
			i = (unsigned)sourceFile.find("std::cout << \"", i);
			if (i == string::npos)
				break;
			unsigned begin = i; //Used later for replacing the string
			i += 14;
			//Give an automatic name
			string autoName = "misc";
			{//Don't keep tmpBuff on the stack
				char tmpBuff[10];
				_itoa_s(count, tmpBuff, 10, 10);
				autoName.append(tmpBuff);
			}
			stringFile.append("//"); stringFile.append(autoName); stringFile.append("\n\"");
			//Copy the string to string file
			while (sourceFile[i] != '"')
			{
				if (sourceFile[i] == '\\')
				{
					i++;
					switch (sourceFile[i])
					{
					case 'n':
						stringFile.push_back('\n');
						break;
					case '"':
						stringFile.append("\"\"");
						break;
					}
				}
				else
					stringFile.push_back(sourceFile[i]);
				i++;
			}
			stringFile.append("\"\n\n");
			i += 2;
			//Replace text in source file
			{
				string temp = "PrintString(\"";
				temp.append(autoName); temp.append("\");");
				sourceFile.replace(begin, i - begin, temp);
			}
		}
		//Remove one extra newline added
		sourceFile.erase(sourceFile.end() - 1);
	}
	if (direction == "INTRACT")
	{
		for (unsigned i = 0, k = 0; i < sourceFile.size(); )
		{
			//Find the place to replace
			i = (unsigned)sourceFile.find("PrintString(\"", i);
			if (i == string::npos)
				break;
			//Find the indention
			unsigned numTabs = 0;
			for (int t = i - 1; sourceFile[t] != '\n'; t--)
				numTabs++;
			k = i;
			i += 13;
			string stringID;
			string replacmtString;
			//Copy the string ID
			while (sourceFile[i] != '"')
			{
				if (sourceFile[i] == '\\')
				{
					i++;
					switch (sourceFile[i])
					{
					case 'n':
						stringID.push_back('\n');
						break;
					case '"':
						stringID.push_back('"');
						break;
					}
				}
				else
					stringID.push_back(sourceFile[i]);
				i++;
			}
			i += 3;
			//Find the proper string in string file, and format the string
			unsigned j = (unsigned)stringFile.find(stringID);
			if (j == string::npos)
				return 1;
			j += (unsigned)stringID.size() + 2; //Skip newline and quote
			replacmtString.append("std::cout << \"");
			bool deleteExtra; //Delete extra formatting
			while (stringFile[j] != '"')
			{
				/*if (stringFile[j + 1] == '"')
				{
					if (stringFile[j + 2] == '"')
						j += 2;
				}*/
				if (stringFile[j] == '\n')
				{
					replacmtString.append("\\n\";\n");
					replacmtString.append(numTabs, '\t');
					replacmtString.append("std::cout << \"");
					j++;
					deleteExtra = true;
				}
				else
				{
					replacmtString.push_back(stringFile[j]);
					j++;
					deleteExtra = false;
				}
			}
			if (deleteExtra == true)
				replacmtString.erase(replacmtString.size() - 14 - numTabs - 1);
			else
				replacmtString.append("\";");

			//Replace the string
			sourceFile.replace(k, i - k, replacmtString);
		}
	}
	
	//Save first file
	{
		ofstream outFile(argv[1], ios_base::out | ios_base::trunc);
		outFile << sourceFile;
	}
	//Save second file
	{
		ofstream outFile(argv[2], ios_base::out | ios_base::trunc);
		outFile << stringFile;
	}

	return 0;
}

/* Reformatter: Overly Simple code reformatter.
   Does not perform correct syntax parsing.
   Command Line: Reformatter <SubFunc> <inFile> <outFile>
   SubFunc #1: Finds 'PrintString("' and does formatting to
       change string ID's to enumerant style ID's. Also creates the enumerant
	   and an array of strings for the enumerant.
   SubFunc #2: Replaces string ID's with a legitiment numeric ID
   SubFunc #3: Changes string ID's to enumerant style string ID's */
int Reformatter(int argc, char* argv[])
{
	string data;
	//Read the contents
	{
		ifstream inFile(argv[2]);
		if (inFile.fail())
			return 1;

		while (inFile.eof() == false)
		{
			string temp;
			getline(inFile, temp);
			data.append(temp);
			data.push_back('\n');
		}
		//Remove one extra newline added
		data.erase(data.end() - 1);
	}

	//Do the work
	switch (atoi(argv[1]))
	{
	case 1:
		{
			queue<string> enumNames;
			queue<string> arrayNames; //For the string array
			for (unsigned i = 0; i < data.size(); )
			{
				i = (unsigned)data.find("PrintString(\"", i);
				if (i == string::npos)
					break;
				i += 12;
				data.erase(i, 1);
				enumNames.push(string(""));
				arrayNames.push(string(""));
				for (bool firstIteration = true; data[i] != '"'; firstIteration = false)
				{
					arrayNames.back().push_back(data[i]);
					if (isupper(data[i]) && firstIteration == false)
					{
						data.insert(i, "_");
						enumNames.back().push_back('_');
						i++;
					}
					data[i] = toupper(data[i]);
					enumNames.back().push_back(toupper(data[i]));
					i++;
				}
				data.erase(i, 1);
			}
			data.push_back('\n');
			data.append("enum STRINGTABLE_ID {");
			while (!enumNames.empty())
			{
				data.append(enumNames.front());
				enumNames.pop();
				data.append(", ");
			}
			data.erase(data.end() - 2, data.end());
			data.append("};\nconst char* IDNames[] = {");
			while (!arrayNames.empty())
			{
				data.push_back('"');
				data.append(arrayNames.front());
				arrayNames.pop();
				data.append("\", ");
			}
			data.erase(data.end() - 2, data.end());
			data.append("};");
		}
		break;
	case 2:
		{
			const int NUM_FINDS = 3;
			const char* findList[NUM_FINDS] = {"END_GAME", "HELP", "START_GAME"};
			const int findStrLengths[NUM_FINDS] = {8, 4, 10};
			const char* replaceList[NUM_FINDS] = {"3", "2", "1"};
			for (unsigned j = 0; j < NUM_FINDS; j++)
			{
				unsigned i = (unsigned)data.find(findList[j]);
				if (i != string::npos)
				{
					data.replace(i, findStrLengths[j], replaceList[j]);
					i += findStrLengths[j];
				}
			}
		}
		break;
	case 3:
		for (unsigned i = 0; i < data.size(); )
		{
			i = (unsigned)data.find("//", i);
			if (i == string::npos)
				break;
			//if (data[i - 1] == '\n')
			//{
				i += 2;
				for (bool firstIteration = true; data[i] != '\n'; firstIteration = false)
				{
					if (isupper(data[i]) && firstIteration == false)
					{
						data.insert(i, "_");
						i++;
					}
					data[i] = toupper(data[i]);
					i++;
				}
			//}
		}
		break;
	}

	//Save the work
	{
		ofstream outFile(argv[3], ios_base::out | ios_base::trunc);
		outFile << data;
	}

	return 0;
}