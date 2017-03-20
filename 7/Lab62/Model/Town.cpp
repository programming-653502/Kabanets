#include "model.h"

using namespace model;

Town::~Town() {
	
	for (Place* place : mPlaces) {
		delete place;
	}
	mPlaces.clear();


	for (Sight* sight : mSights) {
		delete sight;
	}
	mSights.clear();

}