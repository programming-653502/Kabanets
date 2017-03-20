#ifndef H_LABELVIEW
#define H_LABELVIEW


#include "funcview.h"

using namespace core;

namespace core {
	class LabelView;
}

class core::LabelView : public FuncView {

public:
	
	LabelView();

	enum TitleMode { ALONE, BIND, NAME };

	void setTitle(string title) {
		mTitle = title;
	}

	string getTitle() {
		return mTitle;
	}

	void setMode(TitleMode mode) {
		mMode = mode;
	}

	TitleMode getMode() {
		return mMode;
	}

	void onAttachView() override;
	vector<View*> onCreateView() override;
	void onDestroyView() override;
	ViewSize onResizeView(ViewSize) override;

private:
	string mTitle;
	TitleMode mMode = TitleMode::BIND;
};

#endif //!H_LABELVIEW