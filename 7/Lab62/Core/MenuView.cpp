#include "menuview.h"
#include "listview.h"
#include "editframeview.h"
#include "consolehelper.h"

#include <string>
#include <functional>

using namespace core;

MenuView::MenuView() {

}

MenuView::MenuView(string title) {
	mTitle = title;
}

MenuView* MenuView::addItem(MenuItem item) {
	mItems.push_back(item);

	return this;
}

inline MenuItem MenuView::getItem(int index) {
	return mItems[index];
}

void MenuView::onAnswerTyped(string answer)
{
	long item = stol(answer);
	if (onItemSelectedCallback != 0)
		onItemSelectedCallback(item);
}

void MenuView::onAttachView() {
	
}

vector<View*> MenuView::onCreateView() {
	vector<View*> views;

	vector<string> strItems;
	for (MenuItem item : mItems)
	{
		string strItem = "(" + to_string(item.Number) + ")" + " " + item.NameOfItem;
		strItems.push_back(strItem);
	}

	ListView* list = new ListView(strItems);
	list->setTitle(mTitle);
	views.push_back(list);

	EditFrameView* edit = new EditFrameView();
	edit->setOnAnswerTypedCallback( std::bind(&MenuView::onAnswerTyped, this, std::placeholders::_1) );
	edit->setCorrectChecking(new MenuCorrect(mItems));
	views.push_back(edit);

	return views;
}

void MenuView::onDestroyView() {
	mItems.clear();
}

ViewSize MenuView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

MenuCorrect::MenuCorrect(vector<MenuItem> items) {
	mItems = items;
}

inline string MenuCorrect::getDescription() {
	return "Неверно введен номер пункта меню";
}


bool MenuCorrect::isCorrect(void* obj) {
	string* stringObj = reinterpret_cast<string*>(obj);
	if (stringObj != 0)
	{
		string input = *stringObj;

		for (MenuItem item : mItems)
		{
			if (input == std::to_string(item.Number))
			{
				return true;
			}
		}
	}

	return false;
}
