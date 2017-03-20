#include "view.h"

using namespace core;

namespace core {
	class ViewExistException;
	class InvalidChildrenSizeException;
}

class core::ViewExistException {
public:
	ViewExistException();
};

class core::InvalidChildrenSizeException {
public:
	InvalidChildrenSizeException();
};