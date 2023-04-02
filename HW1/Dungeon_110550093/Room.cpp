#include "Room.h"

Room::Room():isExit(0), upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr){}

Room::Room(bool isExit, int index, vector<Object*> objects) :upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr) {
	this->isExit = isExit;
	this->index = index;
	this->objects = objects;
}

bool Room::popObject(Object* object) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i] == object) {
			objects.erase(objects.begin() + i);
			break;
		}
	}
	return 1;
}

void Room::setUpRoom(Room* upRoom) {
	this->upRoom = upRoom;
}

void Room::setDownRoom(Room* downRoom) {
	this->downRoom = downRoom;
}

void Room::setLeftRoom(Room* leftRoom) {
	this->leftRoom = leftRoom;
}

void Room::setRightRoom(Room* rightRoom) {
	this->rightRoom = rightRoom;
}

void Room::setIsExit(bool isExit) {
	this->isExit = isExit;
}

void Room::setIndex(int idx) {
	index = idx;
}

void Room::setObjects(vector<Object*> obj) {
	objects = obj;
}

bool Room::getIsExit() {
	return isExit;
}

int Room::getIndex() {
	return index;
}

vector<Object*> Room::getObjects() {
	return objects;
}

Room* Room::getUpRoom() {
	return upRoom;
}

Room* Room::getDownRoom() {
	return downRoom;
}

Room* Room::getLeftRoom() {
	return leftRoom;
}

Room* Room::getRightRoom() {
	return rightRoom;
}
