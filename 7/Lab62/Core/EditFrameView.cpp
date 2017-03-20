#include "editframeview.h"
#include "labelview.h"
#include "editview.h"

#include "ConsoleHelper.h"

EditFrameView::EditFrameView() {

}

EditFrameView::EditFrameView(string title) {
	mTitle = title;
}

void EditFrameView::setCorrectChecking(Correct* checking) {
	correctAnswerCallbacks.push(checking);
}

void EditFrameView::setCorrectChecking(queue<Correct*> checkingList) {
	for (int i = 0; i < checkingList.size(); i++) {
		correctAnswerCallbacks.push(checkingList.front());
	}
}



void EditFrameView::onAttachView() {
}

vector<View*> EditFrameView::onCreateView() {
	vector<View*> views;

	LabelView* titleLabel = new LabelView();
	titleLabel->setTitle(mTitle);
	titleLabel->setMode(LabelView::TitleMode::ALONE);
	views.push_back(titleLabel);

	LabelView* separateLabel = new LabelView();
	separateLabel->setTitle(SMALL_SEPARATOR);
	separateLabel->setMode(LabelView::TitleMode::BIND);
	views.push_back(separateLabel);

	LabelView* waitingLabel = new LabelView();
	waitingLabel->setTitle("ќжидание ответа...");
	waitingLabel->setMode(LabelView::TitleMode::BIND);
	views.push_back(waitingLabel);

	EditView* edit = new EditView();
	edit->setCorrectChecking(correctAnswerCallbacks);
	edit->setOnAnswerTypedCallback(onAnswerTypedCallback);
	views.push_back(edit);

	separateLabel = new LabelView();
	separateLabel->setTitle(SMALL_SEPARATOR);
	separateLabel->setMode(LabelView::TitleMode::BIND);
	views.push_back(separateLabel);

	return views;
}

void EditFrameView::onDestroyView() {
	mTitle = "";
}

ViewSize EditFrameView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}