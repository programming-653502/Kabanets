#include "consolequeue.h"

using namespace core;

bool ConsoleGlobalViewQueue::drawFlag = false;

queue<LogicView*> ConsoleGlobalViewQueue::views;

void ConsoleGlobalViewQueue::addView(LogicView* view) {
	views.push(view);
}

LogicView* ConsoleGlobalViewQueue::getView() {
	LogicView* view = views.front();
	views.pop();
	return view;
}

void ConsoleGlobalViewQueue::drawNext() {
	if (!drawFlag)
	{
		if (views.size() > 0) {
			LogicView* view = getView();
			view->getManager()->start();
		}
	}
}