#include "view.h"
#include "logicview.h"
#include "logicstorage.h"
#include "consolequeue.h"
#include "consolehelper.h"

#include "viewexceptions.h"

#include "dbmenu.h"

using namespace core;

View::View() {
	mId = ViewManager::generateId();
}

View::~View() {
	delete mManager;
}

inline ViewManager* View::getManager() {
	if (mManager == 0)
		mManager = new ViewManager(this);

	return mManager;
}




void View::changeSize(long width, long height) {
	ViewSize bridge = mActualViewSize;
	bridge.width = width;
	bridge.height = height;
	mActualViewSize = bridge;
}

void View::addPaddings(long paddingLeft, long paddingTop, long paddingRight, long paddingBottom) {
	ViewSize bridge = mActualViewSize;
	bridge.paddingLeft = paddingLeft;
	bridge.paddingTop = paddingTop;
	bridge.paddingRight = paddingRight;
	bridge.paddingBottom = paddingBottom;
	mActualViewSize = bridge;
}

inline bool View::equals(View* view) {
	if (view->getId() == mId) {
		return true;
	}

	return false;
}





long findInVector(vector<View*> viewVector, View* view) {
	
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

bool removeFromVector(vector<View*> viewVector, View* view) {

	long pos = 0;
	if ((pos = findInVector(viewVector, view)) != -1) {
		viewVector.erase(viewVector.begin() + pos);
	} else {
		return false;
	}

	return true;
}


long ViewManager::idCreator = 0;

const ViewSize ViewManager::UNSPECIFIED = ViewSize();

ViewManager::ViewManager(View* view) {
	bindedView = view;
}

ViewManager::~ViewManager() {
	//delete bindedView;

	if (typeid(bindedView) == typeid(ui::DatabaseMenu)) {
		util::ConsoleHelper::WriteNameOfView("ВОТ ТУТ ХУЙНЯ");
	}

	for (View* v : viewChildren) {
		delete v;
	}
	viewChildren.clear();

	for (View* v : additionChildList) {
		delete v;
	}
	additionChildList.clear();

	for (View* v : ignoreChildList) {
		delete v;
	}
	ignoreChildList.clear();

	isAttached = false;
	isInAttaching = false;
}

inline long ViewManager::generateId() {
	return idCreator++;
}

bool ViewManager::isExist(long id) const {

	for (View* savedChild : viewChildren)
	{
		if (id != savedChild->getId())
		{
			return true;
		}
	}

	for (View* savedAdditionChild : additionChildList)
	{
		if (id != savedAdditionChild->getId())
		{
			return true;
		}
	}

	return false;
}

bool ViewManager::isExist(View* child) const {
	for (View* savedChild : viewChildren)
	{
		if (savedChild == child)
		{
			return true;
		}
	}

	for (View* savedAdditionChild : additionChildList)
	{
		if (savedAdditionChild == child)
		{
			return true;
		}
	}

	return false;
}

bool ViewManager::consoleStartPrivius() {
	GlobalLogicStorage* storage = GlobalLogicStorage::getInstance();
	LogicView* view = storage->getView((int)storage->getViewCount() - 1);
	view->getManager()->start();

	return true;
}

bool ViewManager::addNewChild(View* child) {
	if (isExist(child))
	{
		throw new ViewExistException();
	}

	if (isInAttaching)
	{
		ignoreChildList.push_back(child); // Console. игнорируем потому что view подтянется далее по ходу отображения
	}


	child->getManager()->cascadeStart(this);

	resolveSize(UNSPECIFIED);

	//ConfirmChanges(); // NOT IN CONSOLE
	//}

	return true;
}

ViewManager::DestroyType ViewManager::destroy() {

	if (isAttached || !isInAttaching)
	{
		bool notToDestroyNow = false;
		for (int childPos = 0; childPos < viewChildren.size(); childPos++)
		{
			View* child = viewChildren[childPos];

			DestroyType childDestroyType;
			LogicView* logicChild = dynamic_cast<LogicView*>(child);
			if (logicChild != 0)
			{
				childDestroyType = logicChild->getManager()->destroy();
			}
			else
			{
				childDestroyType = child->getManager()->destroy();
			}

			if (childDestroyType == DestroyType::DESTROYED) {
				delete child;
				viewChildren.erase(viewChildren.begin());
				childPos--;
			}

			if (childDestroyType == DestroyType::WAIT) {
				notToDestroyNow = true;
			}
		}

		if (notToDestroyNow) {
			waitForDestroying = true;

			return DestroyType::WAIT;
		} else {
			waitForDestroying = false;

			bindedView->onDestroyView();

			isAttached = false;
			isInAttaching = false;

			return DestroyType::DESTROYED;
		}

	} else if (isInAttaching) {

		waitForDestroying = true;
		return DestroyType::WAIT;

	} else {

		return DestroyType::DESTROYED;

	}

}

void ViewManager::reattach() {
	destroy();
	confirmChanges();
}

bool ViewManager::removeView(View* view) {
	return false;
}

View* ViewManager::getView(long Id) const {
	return 0;
}

void ViewManager::consoleReturnPrevius() {

}

bool ViewManager::confirmChanges() {
	util::ConsoleHelper::WritePadding(bindedView->getActualViewSize().paddingTop);
	
	bindedView->onAttachView();

	for (vector<View*>::size_type i = 0; i < viewChildren.size(); i++)
	{
		View* child = viewChildren[i];

		if (findInVector(ignoreChildList, child) == -1)
		{
			child->getManager()->confirmChanges();
		}
		else
		{
			removeFromVector(ignoreChildList, child);
		}
	}

	if (!waitForDestroying) {
		util::ConsoleHelper::WritePadding(bindedView->getActualViewSize().paddingBottom);
	}

	isInAttaching = false;

	if (waitForDestroying)
		isAttached = false;
	else
		isAttached = true;

	return true;
}

ViewSize ViewManager::resolveSize(ViewSize size) {
	parentSize = bindedView->onResizeView(size);

	long parentWidth = size.width, parentHeight = size.height;

	long childCommonWidth = 0, childCommonHeight = 0;
	vector<ViewSize> childrenSize;

	for (View* child : viewChildren)
	{
		ViewSize childSize = child->getManager()->resolveSize(UNSPECIFIED);
		childSize.paddingBottom = child->getActualViewSize().paddingBottom;
		childSize.paddingRight = child->getActualViewSize().paddingRight;
		childSize.paddingLeft = child->getActualViewSize().paddingLeft;
		childSize.paddingTop = child->getActualViewSize().paddingTop;

		childCommonWidth += childSize.width;
		childCommonHeight += childSize.height;
		childCommonHeight += childSize.paddingBottom;
		childCommonHeight += childSize.paddingTop;

		childrenSize.push_back(childSize);
	}

	if (!size.equals(UNSPECIFIED))
	{

		if (childCommonWidth > parentWidth || childCommonHeight > parentHeight)
		{
			if (mResizeType == ResizeTypes::SCALE)
			{
				float scaledWidth = ((float)parentWidth) / childCommonWidth;
				float scaledHeight = ((float)parentHeight) / childCommonHeight;

				ViewSize newChildSize;
				long childCommonEndWidth = 0, childCommonEndHeight = 0;
				for (vector<View*>::size_type i = 0; i < viewChildren.size(); i++)
				{
					View* child = viewChildren[i];
					newChildSize.width = (long)(((float)childrenSize[i].width) * scaledWidth);
					newChildSize.height = (long)(((float)childrenSize[i].height) * scaledHeight);

					ViewSize endSize = child->getManager()->resolveSize(newChildSize);

					endSize.paddingBottom = child->getActualViewSize().paddingBottom;
					endSize.paddingRight = child->getActualViewSize().paddingRight;
					endSize.paddingLeft = child->getActualViewSize().paddingLeft;
					endSize.paddingTop = child->getActualViewSize().paddingTop;
					child->getActualViewSize() = endSize;

					childCommonEndWidth += endSize.width;
					childCommonEndHeight += endSize.height;
					childCommonEndHeight += endSize.paddingBottom;
					childCommonEndHeight += endSize.paddingTop;
				}


				if (childCommonEndWidth > parentWidth || childCommonEndHeight > parentHeight)
				{
					throw new InvalidChildrenSizeException();
				}
			}

			if (mResizeType == ResizeTypes::CROP)
			{
				childCommonWidth = 0; childCommonHeight = 0;
				for (View* child : viewChildren)
				{
					if (childCommonWidth > parentWidth || childCommonHeight > parentHeight)
					{
						ignoreChildList.push_back(child);
						continue;
					}

					ViewSize childSize = child->onResizeView(UNSPECIFIED);
					childCommonWidth += childSize.width;
					childCommonHeight += childSize.height;
				}
			}
		}
	}

	return parentSize;
}

bool ViewManager::isValidChildrenList(vector<View*> childrens) {
	for (vector<View*>::size_type i = 0; i < childrens.size(); i++)
	{
		View* child = childrens[i];
		for (vector<View*>::size_type j = i + 1; j < childrens.size(); j++)
		{
			if (child->equals(childrens[j]))
			{
				return false;
			}
		}
	}

	return true;
}

bool ViewManager::resolveCreate() {
	isInAttaching = true;

	vector<View*> children = bindedView->onCreateView();
	if (!isValidChildrenList(children))
	{
		return false;
	}
	
	viewChildren.clear();
	for (View* child : children)
		viewChildren.push_back(child);
	
	for (View* child : additionChildList)
		viewChildren.push_back(child);
	

	bool success = true;
	for (View* child : children)
	{
		LogicView* logicChild = dynamic_cast<LogicView*>(child);
		if (logicChild != 0)
		{
			if (!GlobalLogicStorage::getInstance()->isExist(logicChild))
				GlobalLogicStorage::getInstance()->addNewLogicView(logicChild);

			success = logicChild->getManager()->resolveCreate();
		}
		else
		{
			success = child->getManager()->resolveCreate();
		}
		if (!success)
		{
			break;
		}
	}

	return success;
}

bool ViewManager::actualStart() {

	resolveCreate();

	resolveSize(bindedView->getActualViewSize());

	confirmChanges();

	return true;
}

bool ViewManager::cascadeStart(ViewManager* parrentManager) {
	if (parrentManager != 0)
		parrentManager->viewChildren.push_back(bindedView);

	LogicView* logicBindedView = dynamic_cast<LogicView*>(bindedView);
	if (logicBindedView != 0)
	{
		if (ConsoleGlobalViewQueue::isDraw())
		{
			ConsoleGlobalViewQueue::addView(logicBindedView);
		}
		else
		{
			ConsoleGlobalViewQueue::setDraw(true);

			actualStart();

			if (waitForDestroying) {
				((LogicViewManager*) this)->destroy();
			}

			ConsoleGlobalViewQueue::setDraw(false);
			ConsoleGlobalViewQueue::drawNext();
		}
	}
	else
	{
		actualStart();

		if (waitForDestroying) {
			destroy();
		}
	}

	

	return true;
}

