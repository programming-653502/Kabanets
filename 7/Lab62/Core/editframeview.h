#ifndef H_EDITFRAMEVIEW
#define H_EDITFRAMEVIEW


#include "editview.h"

#include <functional>
#include <queue>

using namespace core;

namespace core {
	class EditFrameView;
}

class core::EditFrameView : public FuncView {

public:

	EditFrameView();
	EditFrameView(string);

	void setTitle(string title) {
		mTitle = title;
	}

	string getTitle() {
		return mTitle;
	}

	void setOnAnswerTypedCallback(AnswerTypedCallback callback) {
		onAnswerTypedCallback = callback;
	}

	void setCorrectChecking(Correct*);
	void setCorrectChecking(queue<Correct*>);

	void onAttachView() override;
	vector<View*> onCreateView() override;
	void onDestroyView() override;
	ViewSize onResizeView(ViewSize) override;

private:

	string mTitle;

	AnswerTypedCallback onAnswerTypedCallback;

	queue<Correct*> correctAnswerCallbacks;
};

#endif //!H_EDITFRAMEVIEW