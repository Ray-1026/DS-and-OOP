#include "Player.h"

Player::Player() :GameCharacter("", "Player", 0, 0, 0), coin(0), currentRoom(nullptr), previousRoom(nullptr) {
	inventory["Helmet"] = Item("Empty", "Helmet", 0, 0, 0);
	inventory["Necklace"] = Item("Empty", "Necklace", 0, 0, 0);
	inventory["Armor"] = Item("Empty", "Armor", 0, 0, 0);
	inventory["Weapon"] = Item("Empty", "Weapon", 0, 0, 0);
	inventory["Shield"] = Item("Empty", "Shield", 0, 0, 0);
	inventory["Pants"] = Item("Empty", "Pants", 0, 0, 0);
	inventory["Boots"] = Item("Empty", "Boots", 0, 0, 0);
}

Player::Player(string  name, int currentHealth, int attack, int defense, int money) : GameCharacter(name, "Player", currentHealth, attack, defense), coin(money), currentRoom(nullptr), previousRoom(nullptr) {
	inventory["Helmet"] = Item("Empty", "Helmet", 0, 0, 0);
	inventory["Necklace"] = Item("Empty", "Necklace", 0, 0, 0);
	inventory["Armor"] = Item("Empty", "Armor", 0, 0, 0);
	inventory["Weapon"] = Item("Empty", "Weapon", 0, 0, 0);
	inventory["Shield"] = Item("Empty", "Shield", 0, 0, 0);
	inventory["Pants"] = Item("Empty", "Pants", 0, 0, 0);
	inventory["Boots"] = Item("Empty", "Boots", 0, 0, 0);
}

void Player::addItem(Item item) {
	backpack.push_back(item);
	if (item.getName() == "Map")
		MapExist = 1;
}

void Player::popItem(string name) {
	for (auto it = backpack.begin(); it != backpack.end(); it++) {
		if (it->getName() == name) {
			backpack.erase(it);
			break;
		}
	}
}

void Player::increaseStatus(int health, int attack, int defense) {
	int m_hp = this->getMaxHealth() + health, c_hp = this->getCurrentHealth() + health, atk = this->getAttack() + attack, def = this->getDefense() + defense;
	if (c_hp < 0)
		c_hp = 0;
	if (atk < 0)
		atk = 0;
	if (def < 0)
		def = 0;
	this->setMaxHealth(m_hp);
	this->setCurrentHealth(c_hp);
	this->setAttack(atk);
	this->setDefense(def);
}

void Player::changeRoom(Room* newRoom) {
	previousRoom = currentRoom;
	currentRoom = newRoom;
}

void Player::printMap() {
	int x(0), y(0);
	switch (getCurrentRoom()->getIndex()) {
	case 0:
		Map[12][21] = 'X';
		x = 12;
		y = 21;
		break;
	case 1:
		Map[4][21] = 'X';
		x = 4;
		y = 21;
		break;
	case 2:
		Map[20][21] = 'X';
		x = 20;
		y = 21;
		break;
	case 3:
		Map[20][7] = 'X';
		x = 20;
		y = 7;
		break;
	case 4:
		Map[12][35] = 'X';
		x = 12;
		y = 35;
		break;
	case 5:
		Map[12][49] = 'X';
		x = 12;
		y = 49;
		break;
	case 6:
		Map[4][49] = 'X';
		x = 4;
		y = 49;
		break;
	case 7:
		Map[12][63] = 'X';
		x = 12;
		y = 63;
		break;
	case 8:
		Map[20][63] = 'X';
		x = 20;
		y = 63;
		break;
	case 9:
		Map[20][49] = 'X';
		x = 20;
		y = 49;
		break;
	case 10:
		Map[28][49] = 'X';
		x = 28;
		y = 49;
		break;
	case 11:
		Map[28][35] = 'X';
		x = 28;
		y = 35;
		break;
	case 12:
		Map[36][35] = 'X';
		x = 36;
		y = 35;
		break;
	case 13:
		Map[36][49] = 'X';
		x = 36;
		y = 49;
		break;
	case 14:
		Map[20][77] = 'X';
		x = 20;
		y = 77;
		break;
	}
	for (int i = 0; i < 40; i++)
		cout << Map[i] << "\n";
	cout << "\n";
	Map[x][y] = ' ';
}

void Player::equip(string tag, Item* eq) {
	if (inventory[tag].getName() != "Empty") {
		increaseStatus(inventory[tag].getHealth() * -1, inventory[tag].getAttack() * -1, inventory[tag].getDefense() * -1);
		addItem(inventory[tag]);
	}
	inventory[tag] = *eq;
	increaseStatus(eq->getHealth(), eq->getAttack(), eq->getDefense());
}

bool Player::checkMapExist() {
	return MapExist;
}

bool Player::triggerEvent(Object*) {
	string str[7] = { "Helmet", "Necklace", "Armor", "Weapon", "Shield", "Pants", "Boots" }, space[7] = { "  ", "", "   ", "  ", "  ", "   ", "   " };
	cout << "\nPlayer Status:\n------------------------------------------------\n [" << getName() << "]\n > Health: " << getCurrentHealth() << "/" << getMaxHealth() << "\n > Attack: " << getAttack() << "\n > Defense: " << getDefense() << "\n\nCoin: $" << getCoin() << "\n\nInventory:\n";
	for (int i = 0; i < 7; i++) {
		cout << " > " << str[i] << space[i] << ": ";
		if (inventory[str[i]].getName() != "Empty")
			cout << inventory[str[i]].getName() << " (HP +" << inventory[str[i]].getHealth() << ", ATK +" << inventory[str[i]].getAttack() << ", DEF +" << inventory[str[i]].getDefense() << ")";
		else
			cout << "X";
		cout << "\n";
	}
	cout << "\nBackpack:\n";
	if (!backpack.empty()) {
		for (auto& it : backpack) {
			if (it.getTag() != "Item" && it.getTag() != "Key" && it.getTag() != "DeBuffPotion")
				cout << " > " << it.getName() << " (" << it.getTag() << ", HP: +" << it.getHealth() << " ATK : +" << it.getAttack() << " DEF : +" << it.getDefense() << ")";
			else if(it.getTag()=="DeBuffPotion")
				cout << " > " << it.getName() << " (" << it.getTag() << ", HP: -" << it.getHealth() << " ATK : -" << it.getAttack() << " DEF : -" << it.getDefense() << ")";
			else
				cout << " > " << it.getName() << "(" << it.getTag() << ")";
			cout << "\n";
		}
	}
	cout << "------------------------------------------------\n";
	return 1;
}

void Player::setCurrentRoom(Room* room) {
	currentRoom = room;
}

void Player::setPreviousRoom(Room* room) {
	previousRoom = room;
}

void Player::setInventory(vector<Item> item) {
	backpack = item;
}

void Player::setBackpack(map<string, Item> bp) {
	inventory = bp;
}

void Player::setCoin(int coins) {
	coin = coins;
}

Room* Player::getCurrentRoom() {
	return currentRoom;
}

Room* Player::getPreviousRoom() {
	return previousRoom;
}

vector<Item> Player::getInventory() {
	return backpack;
}

map<string, Item> Player::getBackpack() {
	return inventory;
}

int Player::getCoin() {
	return coin;
}