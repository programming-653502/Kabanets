#include "ConsoleHelper.h"

using namespace util;

void ConsoleHelper::WriteAloneMessage(string message)
{
	cout << SPACE << endl;
	cout << message << endl;
	cout << SPACE << endl;
}

long ConsoleHelper::GetAloneHeight()
{
	return 3;
}

void ConsoleHelper::WriteNameOfView(string message)
{
	Separate();
	cout << "                  " + message << endl;
	Separate();

	//Console.WriteLine(SPACE);
}

long ConsoleHelper::GetNameHeight()
{
	return 2 * GetAloneHeight() + 1;
}

void ConsoleHelper::WriteBindMessage(string message)
{
	cout << message << endl;
}

long ConsoleHelper::GetBindHeight()
{
	return 1;
}

char ConsoleHelper::GetFastAnswer()
{
	return _getch();
}

string ConsoleHelper::GetAnswerString()
{
	string buffer;
	getline(cin, buffer);
	return buffer;
}

void ConsoleHelper::Separate()
{
	WriteAloneMessage(SEPARATOR);
}

void ConsoleHelper::SmalSeparate()
{
	cout << SMALL_SEPARATOR << endl;
}

void ConsoleHelper::WritePadding(long length)
{
	for (long i = length - 1; i >= 0; i--)
	{
		WriteBindMessage("");
	}
}