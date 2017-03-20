#include "labelview.h"
#include "ConsoleHelper.h"

using namespace core;

LabelView::LabelView() {

}

void LabelView::onAttachView() {
	if (mTitle != "")
	{
		switch (mMode)
		{
		case TitleMode::ALONE:
			util::ConsoleHelper::WriteAloneMessage(mTitle);
			break;
		case TitleMode::BIND:
			util::ConsoleHelper::WriteBindMessage(mTitle);
			break;
		case TitleMode::NAME:
			util::ConsoleHelper::WriteNameOfView(mTitle);
			break;
		}
	}
}

vector<View*> LabelView::onCreateView() {
	long height = 0;
	switch (mMode)
	{
	case TitleMode::ALONE:
		height = util::ConsoleHelper::GetAloneHeight();
		break;
	case TitleMode::BIND:
		height = util::ConsoleHelper::GetBindHeight();
		break;
	case TitleMode::NAME:
		height = util::ConsoleHelper::GetNameHeight();
		break;
	}
	//ViewSize temp = ActualViewSize;
	//temp.Height = height;
	//SetViewSize(temp);

	return vector<View*>();
}

void LabelView::onDestroyView() {
	mTitle = "";
}

ViewSize LabelView::onResizeView(ViewSize size) {
	if (size.equals(ViewManager::UNSPECIFIED))
	{
		return mActualViewSize;
	}
	else
	{
		return size;
	}
}