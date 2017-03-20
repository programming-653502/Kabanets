#ifndef H_FUNCTIONVIEW
#define H_FUNCTIONVIEW

#include "view.h"

using namespace core;

namespace core {
	class FuncView;
	class FuncViewManager;
}

class core::FuncView : public View {

public:

	FuncView();

};

class core::FuncViewManager : public ViewManager {

public:
	
	bool removeView(View*) override;

	View* getView(long) const override;

protected:

	FuncViewManager(FuncView*);

};

#endif //!H_FUNCTIONVIEW