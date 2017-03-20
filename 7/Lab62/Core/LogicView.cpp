#include "logicview.h"

#include "logicstorage.h"

LogicView::LogicView() {

}

inline LogicViewManager* LogicView::getManager() {
	if (mManager == 0)
	{
		mManager = new LogicViewManager(this);
	}

	return (LogicViewManager*) mManager;
}



LogicViewManager::LogicViewManager(LogicView* view) : ViewManager(view) {

}

bool LogicViewManager::start() {
	GlobalLogicStorage::getInstance()->addNewLogicView(static_cast<LogicView*>(bindedView));
	return cascadeStart(0);
}

ViewManager::DestroyType LogicViewManager::destroy() {
	GlobalLogicStorage* storage = GlobalLogicStorage::getInstance();

	DestroyType destroyType = ViewManager::destroy();

	storage->removeLogicView(static_cast<LogicView*>(bindedView));

	return destroyType;
}