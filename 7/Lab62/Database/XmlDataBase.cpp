#include "database.h"

#include "rapidxml_print.hpp"

#include <fstream>
#include <sstream>

using namespace database;
using namespace model;

using namespace rapidxml;

XmlDataBase::XmlDataBase() {
	mFileName = DEFAULT_FILE_NAME;
}

XmlDataBase::XmlDataBase(string fileName) {
	mFileName = fileName;
}

XmlDataBase::XmlDataBase(XmlDataBase::DataBaseFileType fileType) {
	
	switch (fileType) {
	case DataBaseFileType::TOWNS:

		mFileName = TOWNS_FILE_NAME;

		break;
	case DataBaseFileType::PLACES_SIGHTS:

		mFileName = PLACES_SIGHTS_FILE_NAME;

		break;

	case DataBaseFileType::COMMENT:

		mFileName = COMMENT_FILE_NAME;

		break;
	}
}

XmlDataBase::~XmlDataBase() {
}

void XmlDataBase::writeTown(Town* town) {

	xml_document<> doc;
	
	ifstream streamReader(mFileName, ifstream::in);

	stringstream buffer;
	buffer << streamReader.rdbuf();
	string content(buffer.str());
	
	doc.parse<0>(&content[0]);

	long id = 1;

	xml_node<>* idNode = doc.first_node(ID_TAG);

	if (idNode != 0) {	

		string idStr = idNode->value();
		id = stol(idStr);

		id++;

		doc.remove_node(idNode);
		idNode->remove_all_nodes();

	} else {

		idNode = doc.allocate_node(node_type::node_element, ID_TAG);
		
	}

	char bufferCh[100];
	_itoa_s(id, bufferCh, 100, 10);

	string townName = " " + town->getName();
	xml_node<>* rootTownNode = doc.allocate_node(node_type::node_element, TOWN_TAG, &townName[1]);
	doc.append_node(rootTownNode);

	xml_attribute<>* idTownAttribute = doc.allocate_attribute(ID_TAG, bufferCh);
	rootTownNode->append_attribute(idTownAttribute);

	xml_node<>* idNodeData = doc.allocate_node(node_type::node_data, 0, bufferCh);
	idNode->append_node(idNodeData);
	doc.append_node(idNode);

	ofstream streamWriter(mFileName, ofstream::out);
	streamWriter << doc;
	streamWriter.close();
	doc.clear();
}

vector<Town*> XmlDataBase::getTowns() {

	vector<Town*> townsArray;

	xml_document<> doc;

	ifstream streamReader(mFileName, ifstream::in);

	stringstream buffer;
	buffer << streamReader.rdbuf();
	string content(buffer.str());

	doc.parse<0>(&content[0]);

	xml_node<>* townNode;
	while ((townNode = doc.first_node(TOWN_TAG)) != 0) {
		xml_attribute<>* townIdAttribute = townNode->first_attribute(ID_TAG);

		Town* town = new Town(townNode->value());
		town->setId(stol(townIdAttribute->value()));
		townsArray.push_back(town);

		doc.remove_node(townNode);
	}

	doc.clear();
	return townsArray;
}

void XmlDataBase::writePlace(Place* place, string townId) {

	xml_document<> doc;

	xml_node<>* rootPlaceNode = doc.allocate_node(node_type::node_element, PLACE_TAG);
	doc.append_node(rootPlaceNode);

	xml_attribute<>* placeTownId = doc.allocate_attribute(TOWNID_TAG, townId.c_str());
	rootPlaceNode->append_attribute(placeTownId);

	xml_node<>* placeType = 0;
	switch (place->getType()) {
	case PlaceType::HOTEL:

		placeType = doc.allocate_node(node_type::node_element, TYPE_TAG, HOTEL_H);

		break;
	case PlaceType::CINEMA:

		placeType = doc.allocate_node(node_type::node_element, TYPE_TAG, CINEMA_H);

		break;
	case PlaceType::THEATER:

		placeType = doc.allocate_node(node_type::node_element, TYPE_TAG, THEATER_H);

		break;
	case PlaceType::MESEUM:

		placeType = doc.allocate_node(node_type::node_element, TYPE_TAG, MESEUM_H);

		break;
	case PlaceType::RESTAURANT:

		placeType = doc.allocate_node(node_type::node_element, TYPE_TAG, RESTAURANT_H);

		break;
	}

	if (placeType != 0) {
		rootPlaceNode->append_node(placeType);
	}

	string name = place->getName();
	string adress = place->getAdress();
	string openTime = place->getOpenTime();
	string closeTime = place->getCloseTime();
	string additions = place->getAddtions();

	xml_node<>* placeName = doc.allocate_node(node_type::node_element, NAME_TAG, name.c_str());
	rootPlaceNode->append_node(placeName);

	xml_node<>* placeAdress = doc.allocate_node(node_type::node_element, ADRESS_TAG, adress.c_str());
	rootPlaceNode->append_node(placeAdress);

	xml_node<>* placeOpenTime = doc.allocate_node(node_type::node_element, OPENTIME_TAG, openTime.c_str());
	rootPlaceNode->append_node(placeOpenTime);

	xml_node<>* placeCloseTime = doc.allocate_node(node_type::node_element, CLOSETIME_TAG, closeTime.c_str());
	rootPlaceNode->append_node(placeCloseTime);

	xml_node<>* placeAddtions = doc.allocate_node(node_type::node_element, ADDTIONS_TAG, additions.c_str());
	rootPlaceNode->append_node(placeAddtions);

	
	ofstream streamWriter(mFileName, ofstream::out | ofstream::app);
	streamWriter << doc;
	streamWriter.close();
	doc.clear();

}

void XmlDataBase::writeSight(Sight* sight, string townId) {

	xml_document<> doc;

	xml_node<>* rootSightNode = doc.allocate_node(node_type::node_element, SIGHT_TAG);
	doc.append_node(rootSightNode);

	xml_attribute<>* sightTownId = doc.allocate_attribute(TOWNID_TAG, townId.c_str());
	rootSightNode->append_attribute(sightTownId);

	xml_node<>* sightType = 0;
	switch (sight->getType()) {
	case SightType::MONUMENT:

		sightType = doc.allocate_node(node_type::node_element, TYPE_TAG, MONUMENT_H);

		break;
	case SightType::BUILDING:

		sightType = doc.allocate_node(node_type::node_element, TYPE_TAG, BUILDING_H);

		break;
	}

	if (sightType != 0) {
		rootSightNode->append_node(sightType);
	}

	string name = sight->getName();
	string adress = sight->getAdress();
	string openTime = sight->getOpenTime();
	string closeTime = sight->getCloseTime();
	string additions = sight->getAddtions();

	xml_node<>* sightName = doc.allocate_node(node_type::node_element, NAME_TAG, name.c_str());
	rootSightNode->append_node(sightName);

	xml_node<>* sightAdress = doc.allocate_node(node_type::node_element, ADRESS_TAG, adress.c_str());
	rootSightNode->append_node(sightAdress);

	xml_node<>* sightOpenTime = doc.allocate_node(node_type::node_element, OPENTIME_TAG, openTime.c_str());
	rootSightNode->append_node(sightOpenTime);

	xml_node<>* sightCloseTime = doc.allocate_node(node_type::node_element, CLOSETIME_TAG, closeTime.c_str());
	rootSightNode->append_node(sightCloseTime);

	xml_node<>* sightAddtions = doc.allocate_node(node_type::node_element, ADDTIONS_TAG, additions.c_str());
	rootSightNode->append_node(sightAddtions);


	ofstream streamWriter(mFileName, ofstream::out | ofstream::app);
	streamWriter << doc;
	streamWriter.close();
	doc.clear();
}

vector<Place*> XmlDataBase::getPlaces(string townId) {
	
	vector<Place*> placesArray;

	xml_document<> doc;

	ifstream streamReader(mFileName, ifstream::in);

	stringstream buffer;
	buffer << streamReader.rdbuf();
	string content(buffer.str());

	doc.parse<0>(&content[0]);

	xml_node<>* placeNode;
	while ((placeNode = doc.first_node(PLACE_TAG)) != 0) {
		xml_attribute<>* placeTownIdAttribute = placeNode->first_attribute(TOWNID_TAG);

		if (placeTownIdAttribute->value() == townId) {
			Place* place = new Place();
			
			xml_node<>* typeNode = placeNode->first_node(TYPE_TAG);
			if (strcmp(typeNode->value(), HOTEL_H) == 0) {
				place->setType(PlaceType::HOTEL);
			}
			if (strcmp(typeNode->value(), CINEMA_H) == 0) {
				place->setType(PlaceType::CINEMA);
			}
			if (strcmp(typeNode->value(), THEATER_H) == 0) {
				place->setType(PlaceType::THEATER);
			}
			if (strcmp(typeNode->value(), MESEUM_H) == 0) {
				place->setType(PlaceType::MESEUM);
			}
			if (strcmp(typeNode->value(), RESTAURANT_H) == 0) {
				place->setType(PlaceType::RESTAURANT);
			}

			xml_node<>* nameNode = placeNode->first_node(NAME_TAG);
			place->setName(nameNode->value());

			xml_node<>* adressNode = placeNode->first_node(ADRESS_TAG);
			place->setAdress(adressNode->value());

			xml_node<>* openTimeNode = placeNode->first_node(OPENTIME_TAG);
			place->setOpenTime(openTimeNode->value());

			xml_node<>* closeTimeNode = placeNode->first_node(CLOSETIME_TAG);
			place->setCloseTime(closeTimeNode->value());

			xml_node<>* additionsNode = placeNode->first_node(ADDTIONS_TAG);
			place->setAddtions(additionsNode->value());

			placesArray.push_back(place);
		}
			
		doc.remove_node(placeNode);
	}

	doc.clear();
	return placesArray;
}

vector<Sight*> XmlDataBase::getSights(string townId) {
	
	vector<Sight*> sightsArray;

	xml_document<> doc;

	ifstream streamReader(mFileName, ifstream::in);

	stringstream buffer;
	buffer << streamReader.rdbuf();
	string content(buffer.str());

	doc.parse<0>(&content[0]);

	xml_node<>* sightNode;
	while ((sightNode = doc.first_node(SIGHT_TAG)) != 0) {
		xml_attribute<>* sightTownIdAttribute = sightNode->first_attribute(TOWNID_TAG);

		if (sightTownIdAttribute->value() == townId) {
			Sight* sight = new Sight();

			xml_node<>* typeNode = sightNode->first_node(TYPE_TAG);
			if (strcmp(typeNode->value(), MONUMENT_H) == 0) {
				sight->setType(SightType::MONUMENT);
			}
			if (strcmp(typeNode->value(), BUILDING_H) == 0) {
				sight->setType(SightType::BUILDING);
			}

			xml_node<>* nameNode = sightNode->first_node(NAME_TAG);
			sight->setName(nameNode->value());

			xml_node<>* adressNode = sightNode->first_node(ADRESS_TAG);
			sight->setAdress(adressNode->value());

			xml_node<>* openTimeNode = sightNode->first_node(OPENTIME_TAG);
			sight->setOpenTime(openTimeNode->value());

			xml_node<>* closeTimeNode = sightNode->first_node(CLOSETIME_TAG);
			sight->setCloseTime(closeTimeNode->value());

			xml_node<>* additionsNode = sightNode->first_node(ADDTIONS_TAG);
			sight->setAddtions(additionsNode->value());

			sightsArray.push_back(sight);
		}

		doc.remove_node(sightNode);
	}

	doc.clear();
	return sightsArray;
}


void XmlDataBase::writeComment(Comment* comment) {

	xml_document<> doc;

	string townName = comment->getTownName();
	string commentStr = comment->getComment();

	xml_node<>* commentNode = doc.allocate_node(node_type::node_element, COMMENT_TAG, commentStr.c_str());
	doc.append_node(commentNode);

	xml_attribute<>* commentTownId = doc.allocate_attribute(TOWNNAME_TAG, townName.c_str());
	commentNode->append_attribute(commentTownId);

	ofstream streamWriter(mFileName, ofstream::out | ofstream::app);
	streamWriter << doc;
	streamWriter.close();
	doc.clear();
}

vector<Comment*> XmlDataBase::getComment() {
	
	vector<Comment*> commentArray;

	xml_document<> doc;

	ifstream streamReader(mFileName, ifstream::in);

	stringstream buffer;
	buffer << streamReader.rdbuf();
	string content(buffer.str());

	doc.parse<0>(&content[0]);

	xml_node<>* commentNode;
	while ((commentNode = doc.first_node(COMMENT_TAG)) != 0) {
		Comment* comment = new Comment();
		
		xml_attribute<>* townNameAttribute = commentNode->first_attribute(TOWNNAME_TAG);
		comment->setTownName(townNameAttribute->value());
		comment->setComment(commentNode->value());
		
		commentArray.push_back(comment);

		doc.remove_node(commentNode);
	}

	return commentArray;
}
