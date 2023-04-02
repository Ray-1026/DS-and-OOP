#include "NPC.h"

NPC::NPC() :GameCharacter("", "NPC", 0, 0, 0) {}

NPC::NPC(string name, string script, vector<Item> commodity) : GameCharacter(name, "NPC", 10000, 0, 0) {
	this->script = script;
	this->commodity = commodity;
}

void NPC::listCommodity() {
	char c = 'A';
	for (auto& it : commodity) {
		cout << " > " << c << ". " << it.getName() << " (" << it.getTag() << ", HP: +" << it.getHealth() << ", ATK: +" << it.getAttack() << ", DEF: +" << it.getDefense() << ")\n";
		c++;
	}
	cout << " > " << c << ". Exit.\n";
}

bool NPC::triggerEvent(Object* object) {
	char choice;
	Player* player = dynamic_cast<Player*> (object);
	if (commodity.empty()) {
		if (getName() == "Old_Wise_Man")
			cout << "\n" << script << "\n";
		else
			cout << "\nSorry, I have nothing to help you.\n";
		listCommodity();
		cin >> choice;
		return 1;
	}
	else {
		cout << "\n" << script << "\n";
		listCommodity();
		cin >> choice;
		if (choice >= 'a')
			choice -= 32;
		int idx = choice - 65;
		if (idx == commodity.size())
			return 1;
		if (player->getCoin() < 15) {
			cout << "\nSorry, you can't afford this.\n";
			return 1;
		}
		cout << "\nYou got the " << commodity[idx].getName() << ".\n\n";
		player->setCoin(player->getCoin() - 15);
		if (commodity[idx].getTag() != "BuffPotion" && commodity[idx].getTag() != "Key" && commodity[idx].getTag() != "DeBuffPotion") {
			do {
				cout << "Do you want to equip it?\n > A. Yes\n > B. No\n";
				cin >> choice;
			} while (choice != 'a' && choice != 'b' && choice != 'A' && choice != 'B');
			if (choice == 'a' || choice == 'A')
				player->equip(commodity[idx].getTag(), &commodity[idx]);
			else if (choice == 'b' || choice == 'B')
				player->addItem(commodity[idx]);
		}
		else
			player->addItem(commodity[idx]);
		commodity.erase(commodity.begin() + idx);
	}
	return 1;
}

void NPC::setScript(string script) {
	this->script = script;
}

void NPC::setCommodity(vector<Item> commodity) {
	this->commodity = commodity;
}

string NPC::getScript() {
	return this->script;
}

vector<Item> NPC::getCommodity() {
	return this->commodity;
}
