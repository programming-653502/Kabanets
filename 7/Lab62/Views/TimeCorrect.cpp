#include "edittownview.h"

using namespace ui;

bool TimeCorrect::isCorrect(void* obj) {
	string* stringObj = reinterpret_cast<string*>(obj);
	if (stringObj != 0)
	{
		string input = *stringObj;

		if (input.length() < 4 || input.length() > 5)
			return false;

		int posOfDoubleP = input.find(':');
		if (posOfDoubleP == 1 || posOfDoubleP == 2) {

			for (char symbol : input) {
				if (symbol - '0' < 0 || symbol - '0' > 9) {
					if (symbol != ':')
						return false;
				}
			}
		}
		else {
			return false;
		}

	}
	else {
		return false;
	}

	return true;
}

string TimeCorrect::getDescription() {
	return "Неверный формат времени. Введите в формате hour:minute";
}