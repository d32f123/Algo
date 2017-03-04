#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using std::vector;
using std::string;
using std::cin;
using std::cout;

bool askCont(const string & str = std::string("Continue? Y/N:\t"));

#define PANIC \
{\
	std::cerr << "Usage: " << argv[0] << " [-t [-n]] [-i | -k num]\n"\
		<< "-t: Print only terminal sentences\n-n: Print iteration number\n-i: interactive\n-k num: try for num cycles max\n";\
	return 1;\
}

int readS(vector<string> & sRules, std::istream & fin)
{
	string temp;
	fin >> temp;
	std::smatch sMatch;
	std::regex sRegex("([^,]+),(.*)");
	if (std::regex_match(temp, sMatch, sRegex))
	{
		do {
			sRules.push_back(sMatch[1].str());
			int matchPos = sMatch.position(2);
			temp = temp.substr(matchPos);
		} while (std::regex_match(temp, sMatch, sRegex));
		sRules.push_back(temp);
	}
	else
	{
		sRules.push_back(temp);
	}
	return 0;
}

int readP(vector<string> & leftSide, vector<string> & rightSide, std::istream & fin)
{
	string temp;
	std::regex e("(.*)==>(.*)");
	
	while ((fin >> temp) && temp[0] != '.')
	{
		std::smatch sm;
		if (std::regex_match(temp, sm, e) && !sm.empty())
		{
			string leftString = sm[1].str();
			string rightString = sm[2].str();
			std::smatch sMatch;
			std::regex sRegex("([^,]+),(.*)");
			if (std::regex_match(rightString, sMatch, sRegex))
			{
				do {
					leftSide.push_back(leftString);
					rightSide.push_back(sMatch[1].str());
					int matchPos = sMatch.position(2);
					rightString = rightString.substr(matchPos);
				} while (std::regex_match(rightString, sMatch, sRegex));
				leftSide.push_back(leftString);
				rightSide.push_back(sMatch[1].str());
			}
			else
			{
				leftSide.push_back(leftString);
				rightSide.push_back(rightString);
			}
		}
		else
		{
			std::cerr << "Wrong format!";
			return -1;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	vector<char> notTerm;
	vector<char> term;
	vector<string> leftSide;
	vector<string> rightSide;
	vector<string> sRules;

	std::ifstream file;

	bool printOnlyTerm = false;
	bool printM = false;
	bool interactive = false;
	bool useKParameter = false;
	bool justLoop = false;
	bool nonTerminalFromArg = false;
	bool terminalFromArg = false;
	bool rulesFromArg = false;
	bool startFromArg = false;
	int K = 10000;
	//Обработаем аргументы
	if (argc == 1)
	{
		std::cout << "Usage: " << argv[0] << " [-t [-n]] [-i | -k num] [-nt \"nt symbols\"] [-ts \"t symbols\"] [-r filename] [-s filename]\n"
			<< "-t: Print only terminal sentences\n-n: Print iteration number\n-i: interactive\n-k num: try for num cycles max\n";
	}
	for (int i = 1; i < argc; ++i)
	{
		switch (argv[i][1]) // symbol after -
		{
		case 's':
			++i; startFromArg = true;

			file.open(argv[i]);
			if (!file.is_open())
			{
				std::cerr << "File was not found\n";
				return 2;
			}
			readS(sRules, file);
			file.close();
			break;
		case 'r':
			++i; rulesFromArg = true;
			
			file.open(argv[i]);
			if (!file.is_open())
			{
				std::cerr << "File was not found\n";
				return 2;
			}
			readP(leftSide, rightSide, file);
			file.close();
			break;
		case 't':
			if (argv[i][2] == '\0')
			{
				printOnlyTerm = true;
				break;
			}
			else
			{
				++i; terminalFromArg = true;
				int j = 0;
				while (argv[i][j] != '\0')
					if (argv[i][j++] != ',')
						term.push_back(argv[i][j - 1]);
				break;
			}
		case 'n':
			if (argv[i][2] == '\0')
			{
				printM = true;
				break;
			}
			else
			{
				++i;	nonTerminalFromArg = true;
				int j = 0;
				while (argv[i][j] != '\0')
					if (argv[i][j++] != ',') 
						notTerm.push_back(argv[i][j - 1]);
				break;
			}
		case 'i':
			interactive = true;
			break;
		case 'k':
			useKParameter = true;
			if (i + 1 > argc)
			{ 
				PANIC;
			}
			string maxNum(argv[i + 1]);
			try {
				K = std::stoi(argv[++i]);
				if (K < 0)
				{
					std::cerr << "k parameter less than 0\n";
					PANIC;
				}
			}
			catch (std::invalid_argument e)
			{
				std::cerr << "Int expected after -k\n";
				PANIC;
			}
			catch (std::out_of_range e)
			{
				std::cerr << "The k parameter was too large\n";
				PANIC;
			}
		}
	}
	if (!interactive && printOnlyTerm && !useKParameter)
		justLoop = true;
	else if (!interactive && !useKParameter)
		interactive = true;


	setlocale(LC_ALL, "Russian");


	if (!terminalFromArg)
	{
		cout << "Enter the alphabet of terminal symbols\nEx:abcd...\n";
		char c;
		while (cin.get(c) && c != '\n')
		{
			if (c != ',')
				term.push_back(c);
		}
	}

	if (!nonTerminalFromArg)
	{
		cout << "Enter the alphabet of non-terminal symbols\n";
		char c;
		while (cin.get(c) && c != '\n')
		{
			if (c != ',')
				notTerm.push_back(c);
		}
	}

	if (!rulesFromArg)
	{
		cout << "Enter the set of rules in the following format: <A>==><B>,<C>,...\nEx:A==>a,b,CB,bC,...\nEnter . to stop the input\n"
			<< "Ex: AB==>aab\n";
		int ret = readP(leftSide, rightSide, std::cin);
		if (ret)
			return 1;
	}

	if (!startFromArg)
	{
		cout << "Enter the rules for S in the following format: aA,bb,...\n";
		readS(sRules, std::cin);
	}

	

	int M = 0;

	vector<string> Sentences[2];
	bool currVector = true;
	Sentences[0].push_back("S");
	do {
		for (size_t i = 0; i < Sentences[!currVector].size(); ++i)
		{
			bool matchedOnce = false;
			for (size_t j = 0; j < leftSide.size(); ++j)
			{
				std::smatch sm;
				if (std::regex_match((Sentences[!currVector])[i], sm, std::regex("(?:.*)(" + leftSide[j] + ")(?:.*)")))
				{
					string newSent = std::regex_replace(Sentences[!currVector][i], std::regex(leftSide[j]), rightSide[j]);
					Sentences[currVector].push_back(newSent);
					if (!printOnlyTerm)
						cout << i + 1 << ":\t\t" << newSent << std::endl;
					matchedOnce = true;
				}
			}
			if (!matchedOnce)
			{
				if (Sentences[!currVector][i].find('S') != string::npos)
				{
					matchedOnce = true;
					for (size_t j = 0; j < sRules.size(); ++j)
					{
						string newSent = std::regex_replace(Sentences[!currVector][i], std::regex("S"), sRules[j]);
						Sentences[currVector].push_back(newSent);
						if (!printOnlyTerm)
							cout << i + 1 << ":\t\t" << newSent << std::endl;
					}
				}
			}
			if (printOnlyTerm && !matchedOnce)
			{
				if (printM)
					cout << M + 1 << ":\t";
				cout << Sentences[!currVector][i] << std::endl;
			}
		}
		Sentences[!currVector].clear();
		currVector = !currVector;
		if (Sentences[!currVector].empty())
			break;
		++M;
		if (!interactive) 
			std::cerr << M;
	} while (justLoop ? true : false || interactive ? askCont() : false || useKParameter ? M < K : false);
	return 0;
}

bool askCont(const string & str)
{
	cout << str;
	char ch;
	cin.clear();
	while (cin.get(ch) && ch != 'Y' && ch != 'N');
	if (ch == 'Y')
		return true;
	return false;
}