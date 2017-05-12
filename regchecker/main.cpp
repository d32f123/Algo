#include <iostream>

using namespace std;

#define STATENUM 8
#define CHARNUM 3

int main()
{
	int currstate = 0, endstate = 6;
	char ch;
	int states[STATENUM * CHARNUM];
	states[0] = 1; states[1] = 2; states[2] = 3;
	states[3] = 1; states[4] = 4; states[5] = 5;
	states[6] = 1; states[7] = 6; states[8] = 5;
	states[9] = 1; states[10] = 2; states[11] = 3;
	states[12] = 1; states[13] = 6; states[14] = 7;
	states[15] = 1; states[16] = 2; states[17] = 3;
	states[18] = 1; states[19] = 6; states[20] = 5;
	states[21] = 1; states[22] = 2; states[23] = 3;
	cout << "Input a string. Stop input with a dot (.)\n";
	while (true)
	{
		while (cin.get(ch))
		{
			if (ch == '.')
				break;
			if (ch != 'a' && ch != 'b' && ch != 'c')
				continue;
			ch = ch - 'a';
			currstate = states[currstate * CHARNUM + ch];
		}
		if (currstate == endstate)
			cout << "true\n";
		else
			cout << "false\n";
	}
	return 0;
}