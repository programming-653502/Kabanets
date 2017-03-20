#include "funcview.h"
#include "viewexceptions.h"

FuncView::FuncView() {

}


long findInFuncVector(vector<View*> viewVector, View* view) {

	bool find = false;
	long pos = 0;
	for (View* internalView : viewVector) {
		if (internalView->equals(view)) {
			return pos;
		}

		pos++;
	}

	return -1;
}

bool removeFromFuncVector(vector<View*> viewVector, View* view) {

	long pos = 0;
	if ((pos = findInFuncVector(viewVector, view)) != -1) {
		viewVector.erase(viewVector.begin() + pos);
	}
	else {
		return false;
	}

	return true;
}


FuncViewManager::FuncViewManager(FuncView* view) : ViewManager(view) {

}

bool FuncViewManager::removeView(View* view) {
	if (!isExist(view))
		throw new ViewExistException();

	bool success = false;

	success = removeFromFuncVector(viewChildren, view);

	if (!success)
	{
		success = removeFromFuncVector(additionChildList, view);

		if (!success) return false;
	}

	view->onDestroyView();

	return true;
}

View* FuncViewManager::getView(long id) const {
	for (View* savedChild : viewChildren)
	{
		if (id == savedChild->getId())
		{
			return savedChild;
		}
	}

	for (View* savedAdditionChild : additionChildList)
	{
		if (id != savedAdditionChild->getId())
		{
			return savedAdditionChild;
		}
	}

	return 0;
}
