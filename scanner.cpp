#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/** Functions
 * 
 */

bool Dig(char d) {
	 return (d >= '0' && d <= '9');
}
bool Letter(char l) {
	return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); 
}
bool Space(char s) {
	return (s == ' ' || s == '\t' || s == '\n'); 
}
bool Sympol(char c) {
	return (c == '+' || '-' || '*' || '/' || '['||']'|| '=' || '<' || '(' || ')' || ';'); 
}

enum STATES
{
	START,
	INCOMMENT,
	INNUM,
	INID,
	INASSIGN,
	DONE
};
STATES state = START;

string used_words[] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};

void getString(string l)
{
	string theToken;
	bool res_flag = 0;
	int i = 0;
	while (state != DONE)
	{
		switch (state)
		{
		case START:
			if (Space(l[i]))
			{
				i++;
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			else if (Dig(l[i]))
			{
				state = INNUM;
			}
			else if (Letter(l[i]))
			{
				state = INID;
			}
			else if (l[i] == ':')
			{
				state = INASSIGN;
			}
			else if (l[i] == '{')
			{
				i++;
				state = INCOMMENT;
			}
			else if (Sympol(l[i]))
			{
				switch (l[i])
				{
				case ';':
					cout << l[i] << endl;
					break;
				case '+':
					cout << "plus ";
					break;
				case '-':
					cout << "minus ";
					break;
				case '*':
					cout << "is multiplied by ";
					break;
				case '/':
					cout << "is divided by ";
					break;
				case '<':
					cout << "is less than ";
					break;
				case '>':
					cout << "is bigger than ";
					break;
				case '=':
					cout << "is equal ";
					break;
				case '(':
					cout << "right parentheses sign ";
					break;
				case ')':
					cout << "left parentheses sign ";
					break;
				case '[':
					cout << "left braket sign ";
					break;
				case ']':
					cout << "right braket sign ";
					break;
				default:
					cout << l[i] << " ";
					break;
				}
				i++;
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			else
				state = DONE;
			break;

		case INCOMMENT:
			if (state == INCOMMENT)
			{
				while (l[i] != '}')
				{
					i++;
				}
				i++;
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			break;

		case INNUM:
			while (Dig(l[i]))
			{
				theToken += l[i];
				i++;
			}
			cout << "number"
				 << " ";
			theToken = "";
			if (i == l.length())
				state = DONE;
			else
				state = START;
			break;

		case INID:
			while (Letter(l[i]))
			{
				theToken += l[i];
				i++;
			}
			for (int i = 0; i < 8; i++)
			{
				if (used_words[i] == theToken)
					res_flag = 1;
			}
			if (res_flag)
				cout << endl
					 << theToken << " ";
			else
				cout << "identifier"
					 << " ";
			theToken = "";
			res_flag = 0;
			if (i == l.length())
				state = DONE;
			else
				state = START;
			break;

		case INASSIGN:
			if (l[i] == ':')
			{
				i += 2;
				cout << ":="
					 << " ";
				state = START;
			}
			else
			{
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			break;
		case DONE:
			break;
		}
	}
}

int main(){
	ifstream file;
	string line, code;
	file.open("code.txt");
	while (!file.eof()){
		getline(file, line);
		code += line;
	}
	freopen("output.exe", "wt", stdout);
	getString(code);
	fclose(stdout);
	return 0;
}


