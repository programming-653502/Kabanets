#include "listview.h"
#include "labelview.h"

using namespace core;

ListView::ListView() {

}

ListView::ListView(vector<string> items) {
	mItems = items;
}

ListView::ListView(vector<string> items, string title) {
	mItems = items;
	mTitle = title;
}

string ListView::getItem(int index) {
	return mItems[index];
}

ListView* ListView::addNewItem(string item) {
	mItems.push_back(item);

	return this;
}

void ListView::onAttachView() {
	//Console.WriteLine(Title);
}

vector<View*> ListView::onCreateView() {
	
	vector<View*> views;

	LabelView* TitleLabel = new LabelView();
	TitleLabel->setTitle(mTitle);
	TitleLabel->setMode(LabelView::TitleMode::ALONE);
	views.push_back(TitleLabel);

	int height = 1;
	for (string title : mItems)
	{
		LabelView* item = new LabelView();
		item->setTitle(title);
		item->setMode(LabelView::TitleMode::BIND);
		views.push_back(item);

		height++;
	}

	return views;
}

void ListView::onDestroyView() {
	mItems.clear();
	mTitle = "";
}

ViewSize ListView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}