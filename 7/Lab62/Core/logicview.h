#ifndef H_LOGICVIEW
#define H_LOGICVIEW

#include "view.h"

using namespace core;

namespace core {
	class LogicView;
	class LogicViewManager;
}

class core::LogicViewManager : public ViewManager {

public:

	LogicViewManager(LogicView*);

	bool start();
	ViewManager::DestroyType destroy();
};

class core::LogicView : public View {

public:

	LogicView();

	LogicViewManager* getManager();
};

#endif //!H_LOGICVIEW