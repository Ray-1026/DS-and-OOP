#include "Item.h"

Item::Item() :Object() {}

Item::Item(string name, string type, int health, int attack, int defense) : Object(name, type) {
	this->health = health;
	this->attack = attack;
	this->defense = defense;
	this->type = type;
}

bool Item::triggerEvent(Object* object) {
	Player* player = dynamic_cast<Player*> (object);
	cout << "\nYou get an " << getTag() << " \"" << getName() << "\"\n";
	player->addItem(*this);
	return 1;
}

int Item::getHealth() {
	return health;
}

int Item::getAttack() {
	return attack;
}

int Item::getDefense() {
	return defense;
}

void Item::setHealth(int health) {
	this->health = health;
}

void Item::setAttack(int attack) {
	this->attack = attack;
}

void Item::setDefense(int defense) {
	this->defense = defense;
}
