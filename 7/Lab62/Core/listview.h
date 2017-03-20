#ifndef H_LISTVIEW
#define H_LISTVIEW



#include "funcview.h"

using namespace core;

namespace core {
	class ListView;
}

class core::ListView : public FuncView {

public:

	ListView();
	ListView(vector<string>);
	ListView(vector<string>, string);

	void setTitle(string title) {
		mTitle = title;
	}

	string getTitle() {
		return mTitle;
	}

	string getItem(int);
	ListView* addNewItem(string);

	void onAttachView() override;
	vector<View*> onCreateView() override;
	void onDestroyView() override;
	ViewSize onResizeView(ViewSize) override;

private:

	vector<string> mItems;
	string mTitle;

};

#endif //!H_LISTVIEW