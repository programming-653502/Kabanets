#include "editframeview.h"
#include "ConsoleHelper.h"

EditView::EditView() {

}

void EditView::setCorrectChecking(Correct* checking) {
	correctAnswerCallbacks.push(checking);
}

void EditView::setCorrectChecking(queue<Correct*> checkingList) {
	for (queue<Correct*>::size_type i = 0; i < checkingList.size(); i++) {
		correctAnswerCallbacks.push(checkingList.front());
	}
}


void EditView::onAttachView() {
	string answer = util::ConsoleHelper::GetAnswerString();

	if (correctAnswerCallbacks.size() > 0)
	{

		vector<Correct*> correctList;

		for (queue<Correct*>::size_type i = 0; i < correctAnswerCallbacks.size(); i++) {
			correctList.push_back(correctAnswerCallbacks.front());
		}

		for (queue<Correct*>::size_type i = 0; i < correctList.size(); i++)
		{
			if (!correctList[i]->isCorrect(&answer))
			{
				string description = correctList[i]->getDescription();
				util::ConsoleHelper::WriteAloneMessage(description);

				answer = util::ConsoleHelper::GetAnswerString();
				i = -1;
			}
		}
	}

	if (onAnswerTypedCallback != 0)
		onAnswerTypedCallback(answer);
}

vector<View*> EditView::onCreateView() {
	vector<View*> views;
	return views;
}

void EditView::onDestroyView() {
}

ViewSize EditView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}



IntCorrect::IntCorrect() {

}

string IntCorrect::getDescription() {
	return "Можно вводить только цифры. Только положительные";
}

bool IntCorrect::isCorrect(void* obj) {
	string* stringObj = reinterpret_cast<string*>(obj);
	if (stringObj != 0)
	{
		string input = *stringObj;

		if (input == "")
			return false;

		for (char c : input)
		{
			if (!(0 <= c - '0' && c - '0' <= 9))
			{
				return false;
			}
		}
	}

	return true;
}




string DoubleCorrect::getDescription() {
	return "Можно вводить только цифры. Дробные либо целые. Только положительные";
}

bool DoubleCorrect::isCorrect(void* obj) {
	string* stringObj = reinterpret_cast<string*>(obj);
	if (stringObj != 0)
	{
		string input = *stringObj;


		if (input == "")
			return false;

		for (char c : input)
		{
			if (c != '.' && c != ',') {
				if (!(0 <= c - '0' && c - '0' <= 9))
				{
					return false;
				}
			}
		}
	}

	return true;
}





string StringEmptyCorrect::getDescription() {
	return "Введите строку";
}

bool StringEmptyCorrect::isCorrect(void* obj) {
	string* stringObj = reinterpret_cast<string*>(obj);
	if (stringObj != 0)
	{
		string input = *stringObj;

		if (!input.empty())
			return true;
	}

	return false;
}