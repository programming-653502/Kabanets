#include "logicstorage.h"

using namespace core;

long findInVector(vector<LogicView*> *viewVector, LogicView* view) {

	bool find = false;
	long pos = 0;
	for (LogicView* internalView : *viewVector) {
		if (internalView->equals(view)) {
			return pos;
		}

		pos++;
	}

	return -1;
}

bool removeFromVector(vector<LogicView*> *viewVector, LogicView* view) {

	long pos = 0;
	if ((pos = findInVector(viewVector, view)) != -1) {
		(*viewVector).erase((*viewVector).begin() + pos);
	} else {
		return false;
	}

	return true;
}


GlobalLogicStorage::GlobalLogicStorage() {
}

GlobalLogicStorage* GlobalLogicStorage::getInstance() {
	
	static GlobalLogicStorage* mInstance = new GlobalLogicStorage();

	return mInstance;
}

LogicView* GlobalLogicStorage::getView(int index) {
	return mStorage[index];
}

long GlobalLogicStorage::getViewCount() {
	return mStorage.size();
}

bool GlobalLogicStorage::isExist(LogicView* view) {
		
	for (LogicView* savedView : mStorage)
	{
		if (savedView->equals(view))
		{
			return true;
		}
	}

	return false;
}

bool GlobalLogicStorage::addNewLogicView(LogicView* view) {
	if (isExist(view))
	{
		return false;
	}

	mStorage.push_back(view);

	return true;
}

LogicView* GlobalLogicStorage::getViewById(long id) {
	for (LogicView* savedView : mStorage)
	{
		if (id == savedView->getId())
		{
			return savedView;
		}
	}

	return 0;
}

bool GlobalLogicStorage::removeLogicView(LogicView* view) {
	if (!isExist(view))
	{
		return false;
	}

	bool success = removeFromVector(&mStorage, view);

	return success;
}