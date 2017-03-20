#ifndef H_CONSOLEQUEUE
#define H_CONSOLEQUEUE

#include <queue>

#include "logicview.h"


using namespace core;

namespace core {
	class ConsoleGlobalViewQueue;
}

class core::ConsoleGlobalViewQueue {
	
public:

	static bool isDraw() {
		return drawFlag;
	}

	static void setDraw(bool draw) {
		drawFlag = draw;
	}

	static void addView(LogicView*);

	static LogicView* getView();

	static void drawNext();

private:
	static bool drawFlag;

	static queue<LogicView*> views;
};

#endif //!H_CONSOLEQUEUE