#pragma once
#include "view.h"

#include <iostream>
#include <string>
#include <conio.h>

using namespace std;
using namespace core;

#define SPACE ""
#define SEPARATOR "///////////////////////////////////////////////////////////////////"
#define SMALL_SEPARATOR "....................................."

namespace core{
	namespace util {
		class ConsoleHelper;
	}
}

class util::ConsoleHelper {

public:

	static void WriteAloneMessage(string message);

	static long GetAloneHeight();

	static void WriteNameOfView(string message);

	static long GetNameHeight();

	static void WriteBindMessage(string message);

	static long GetBindHeight();

	static char GetFastAnswer();

	static string GetAnswerString();

	static void Separate();

	static void SmalSeparate();

	static void WritePadding(long length);
	
};