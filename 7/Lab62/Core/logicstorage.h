#ifndef H_LOGICSTORAGE
#define H_LOGICSTORAGE


#include "logicview.h"

using namespace core;

namespace core {
	class GlobalLogicStorage;
}

class core::GlobalLogicStorage {

public:

	long getViewCount();

	static GlobalLogicStorage* getInstance();

	LogicView* getView(int);

	bool isExist(LogicView*);

	bool addNewLogicView(LogicView*);

	LogicView* getViewById(long);

	bool removeLogicView(LogicView*);

private:
	GlobalLogicStorage();

	vector<LogicView*> mStorage;
};

#endif //!H_LOGICSTORAGE