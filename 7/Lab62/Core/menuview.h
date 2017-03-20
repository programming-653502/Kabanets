#ifndef H_MENUVIEW
#define H_MENUVIEW



#include "funcview.h"
#include "editview.h"

#include <functional>

using namespace core;

namespace core {
	class MenuView;
	struct MenuItem;

	typedef std::function<void(long)> ItemSelectedCallback;

	class MenuCorrect;
}

struct core::MenuItem
{

public:

	string NameOfItem;
	long Number;

	MenuItem(string nameOfItem, long number)
	{
		NameOfItem = nameOfItem;
		Number = number;
	}
};

class core::MenuView : public FuncView {

public:

	MenuView();
	MenuView(string);

	void setTitle(string title) {
		mTitle = title;
	}

	string getTitle() {
		return mTitle;
	}

	MenuView* addItem(MenuItem);
	MenuItem getItem(int);

	void setOnItemSelectedCallback(ItemSelectedCallback callback) {
		onItemSelectedCallback = callback;
	}

	void onAttachView() override;
	vector<View*> onCreateView() override;
	void onDestroyView() override;
	ViewSize onResizeView(ViewSize) override;

private:

	ItemSelectedCallback onItemSelectedCallback;

	string mTitle;
	vector<MenuItem> mItems;

	void onAnswerTyped(string);

};


class core::MenuCorrect : public core::Correct {

public:

	MenuCorrect(vector<MenuItem> items);

	string getDescription() override;

	bool isCorrect(void*) override;

private:

	vector<MenuItem> mItems;

};

#endif //!H_MENUVIEW