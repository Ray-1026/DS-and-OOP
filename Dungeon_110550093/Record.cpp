#include "Record.h"

Record::Record() {}

void Record::savePlayer(Player* player, ofstream& file) {
	string str[7] = { "Helmet", "Necklace", "Armor", "Weapon", "Shield", "Pants", "Boots" };
	file << player->getName() << " " << player->getMaxHealth() << " " << player->getCurrentHealth() << " " << player->getAttack() << " " << player->getDefense() << " " << player->getCoin() << "\n\n" << player->getCurrentRoom()->getIndex() << " " << player->getPreviousRoom()->getIndex() << "\n\nBackpack\n";
	for (auto& it : player->getInventory())
		file << it.getTag() << " " << it.getName() << " " << it.getHealth() << " " << it.getAttack() << " " << it.getDefense() << "\n";
	file << "\nInventory\n";
	for (int i = 0; i < 7; i++)
		file << player->getBackpack()[str[i]].getTag() << " " << player->getBackpack()[str[i]].getName() << " " << player->getBackpack()[str[i]].getHealth() << " " << player->getBackpack()[str[i]].getAttack() << " " << player->getBackpack()[str[i]].getDefense() << "\n";
}

void Record::saveRooms(vector<Room>& room, ofstream& file) {
	for (int i = 0; i < 15; i++) {
		file << room[i].getIndex() << " " << room[i].getIsExit();
		if (!room[i].getObjects().empty()) {
			file << " ";
			for (auto& it : room[i].getObjects()) {
				file << it->getTag() << " ";
				if (it->getTag() == "Monster") {
					Monster* m = dynamic_cast<Monster*> (it);
					file << m->getName() << " " << m->getMaxHealth() << " " << m->getCurrentHealth() << " " << m->getAttack() << " " << m->getDefense() << " ";
				}
				else if (it->getTag() == "NPC") {
					NPC* n = dynamic_cast<NPC*> (it);
					file << n->getName() << " " << n->getScript() << " " << n->getCommodity().size() << " ";
					for (auto& it_2 : n->getCommodity())
						file << it_2.getTag() << " " << it_2.getName() << " " << it_2.getHealth() << " " << it_2.getAttack() << " " << it_2.getDefense() << " ";
				}
				else {
					Item* item = dynamic_cast<Item*> (it);
					file << item->getName() << " " << item->getHealth() << " " << item->getAttack() << " " << item->getDefense();
				}
			}
		}
		file << "\n";
	}
}

void Record::loadPlayer(Player* player, ifstream& file, vector<Room>& room) {
	int val[3] = { 0 }, status[5] = { 0 }, cur(0), prev(0);
	string name, tag;
	file >> name >> status[0] >> status[1] >> status[2] >> status[3] >> status[4] >> cur >> prev >> tag;
	player->setName(name);
	player->setCurrentRoom(&room[cur]);
	player->setPreviousRoom(&room[prev]);
	if (tag == "Backpack") {
		string type;
		while (file >> type) {
			if (type == "Inventory")
				break;
			file >> name >> val[0] >> val[1] >> val[2];
			Item in(name, type, val[0], val[1], val[2]);
			player->addItem(in);
		}
	}
	for (int i = 0; i < 7; i++) {
		file >> tag >> name >> val[0] >> val[1] >> val[2];
		if (name == "Empty")
			continue;
		Item eq(name, tag, val[0], val[1], val[2]);
		player->equip(tag, &eq);
	}
	player->setMaxHealth(status[0]);
	player->setCurrentHealth(status[1]);
	player->setAttack(status[2]);
	player->setDefense(status[3]);
	player->setCoin(status[4]);
}

void Record::loadRooms(vector<Room>& room, ifstream& file) {
	int idx(0), maxhp(0), hp(0), atk(0), def(0);
	bool ex(0);
	string line, temp, name;
	stringstream ss;
	room.reserve(15);
	for (int i = 0; i < 15; i++) {
		vector<Object*> objs;
		getline(file, line);
		ss.str("");
		ss.clear();
		ss << line;
		ss >> idx >> ex;
		while (ss >> temp) {
			if (temp == "Monster") {
				ss >> name >> maxhp >> hp >> atk >> def;
				objs.push_back(new Monster(name, hp, atk, def));
				Monster* m = dynamic_cast<Monster*> (objs.back());
				m->setCurrentHealth(maxhp);
			}
			else if (temp == "NPC") {
				int num(0);
				string scr = "", str, itname, ittag;
				vector<Item> itm;
				ss >> name;
				while (ss >> str) {
					scr += str;
					if (str == "?")
						break;
					scr += " ";
				}
				if (ss >> num) {
					itm.reserve(num);
					for (int j = 0; j < num; j++) {
						ss >> ittag >> itname >> hp >> atk >> def;
						itm.push_back(Item(itname, ittag, hp, atk, def));
					}
				}
				objs.push_back(new NPC(name, scr, itm));
			}
			else {
				ss >> name >> hp >> atk >> def;
				objs.push_back(new Item(name, temp, hp, atk, def));
			}
		}
		room.push_back(Room(ex, idx, objs));
	}
}

void Record::saveToFile(Player* player, vector<Room>& room) {
	ofstream file1(fpath1, ios::trunc), file2(fpath2, ios::trunc);
	savePlayer(player, file1);
	saveRooms(room, file2);
	file1.close();
	file2.close();
}

void Record::loadFromFile(Player* player, vector<Room>& room) {
	ifstream file1(fpath1), file2(fpath2);
	loadRooms(room, file2);
	loadPlayer(player, file1, room);
	file1.close();
	file2.close();
}
