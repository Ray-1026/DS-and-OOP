#include "Dungeon.h"

Dungeon::Dungeon() {}

void Dungeon::createPlayer() {
	string name;
	cin >> name;
	player = Player(name, 120, 30, 0, 55);
}

void Dungeon::createMap() {
	if (rooms.empty()) {
		rooms.reserve(20);
		vector<Object*> objects[15];
		vector<Item> products[4];
		for (int i = 0; i < 15; i++)
			objects[i].reserve(5);
		for (int i = 0; i < 4; i++)
			products[i].reserve(5);
		products[0].push_back(Item("Sword", "Weapon", 10, 20, 0));
		products[0].push_back(Item("Wood_Shield", "Shield", 10, 5, 15));
		products[0].push_back(Item("Smelly_Underpants", "Pants", 15, 5, 8));
		products[0].push_back(Item("Crystal", "Necklace", 30, 8, 5));
		products[1].push_back(Item("Heal", "BuffPotion", 40, 0, 0));
		products[1].push_back(Item("Silly_Hat", "Helmet", 0, 12, 12));
		products[2].push_back(Item("Ex_Curry_Stick", "Weapon", 15, 30, 0));
		products[2].push_back(Item("Weed", "DeBuffPotion", 0, 30, 0));
		products[2].push_back(Item("EXPLOSION!", "DeBuffPotion", 35, 15, 5));
		products[3].push_back(Item("Golden_Shield", "Shield", 15, 5, 25));
		products[3].push_back(Item("Gold_Chain", "Necklace", 30, 10, 10));
		products[3].push_back(Item("Bless", "BuffPotion", 90, 40, 20));
		objects[0].push_back(new NPC("JOJO", "I can help you beat the Boss Dio. What do you want ?", products[3]));
		objects[1].push_back(new Monster("Dark_Wizard", 230, 55, 0));
		objects[1].push_back(new Item("Key-2", "Key", 0, 0, 0));
		objects[2].push_back(new Monster("Dio_Brando", 350, 90, 40));
		objects[5].push_back(new Monster("Goblin_King", 200, 45, 20));
		objects[6].push_back(new NPC("Smuggler_AKA_Drug_Dealer", "I have lots of drugs. Do you want some ?", products[2]));
		objects[6].push_back(new Item("Old_Armor", "Armor", 15, 5, 15));
		objects[6].push_back(new Item("Magician_Cloak", "Armor", 10, 19, 9));
		objects[7].push_back(new Monster("Widow", 150, 1000, 5));
		objects[8].push_back(new NPC("Old_Wise_Man", "The Key may appear at the next room. Maybe there will be a scary Monster too ?", products[1]));
		objects[9].push_back(new NPC("Businessman_Bob", "Hello, my friend. What can I help you ?", products[0]));
		objects[10].push_back(new Monster("Slime", 15, 5, 0));
		objects[12].push_back(new Item("Poison", "DeBuffPotion", 30, 0, 10));
		objects[13].push_back(new Item("Map", "Item", 0, 0, 0));
		objects[13].push_back(new Item("Warrior's_Hat", "Helmet", 20, 15, 10));
		objects[13].push_back(new Item("Old_Boots", "Boots", 15, 7, 10));
		objects[14].push_back(new Monster("Giant_Bee", 40, 15, 5));
		objects[14].push_back(new Item("Key-13", "Key", 0, 0, 0));
		for (int i = 0; i < 15; i++) {
			Room r(0, i, objects[i]);
			rooms.push_back(r);
		}
		rooms[3].setIsExit(1);
		player.setCurrentRoom(&rooms[11]);
	}
	rooms[0].setUpRoom(&rooms[1]);
	rooms[1].setDownRoom(&rooms[0]);
	rooms[0].setDownRoom(&rooms[2]);
	rooms[2].setUpRoom(&rooms[0]);
	rooms[2].setLeftRoom(&rooms[3]);
	rooms[3].setRightRoom(&rooms[2]);
	rooms[0].setRightRoom(&rooms[4]);
	rooms[4].setLeftRoom(&rooms[0]);
	rooms[4].setRightRoom(&rooms[5]);
	rooms[5].setLeftRoom(&rooms[4]);
	rooms[5].setUpRoom(&rooms[6]);
	rooms[6].setDownRoom(&rooms[5]);
	rooms[5].setRightRoom(&rooms[7]);
	rooms[7].setLeftRoom(&rooms[5]);
	rooms[5].setDownRoom(&rooms[9]);
	rooms[9].setUpRoom(&rooms[5]);
	rooms[7].setDownRoom(&rooms[8]);
	rooms[8].setUpRoom(&rooms[7]);
	rooms[9].setRightRoom(&rooms[8]);
	rooms[8].setLeftRoom(&rooms[9]);
	rooms[9].setDownRoom(&rooms[10]);
	rooms[10].setUpRoom(&rooms[9]);
	rooms[10].setLeftRoom(&rooms[11]);
	rooms[11].setRightRoom(&rooms[10]);
	rooms[11].setDownRoom(&rooms[12]);
	rooms[12].setUpRoom(&rooms[11]);
	rooms[10].setDownRoom(&rooms[13]);
	rooms[13].setUpRoom(&rooms[10]);
	rooms[8].setRightRoom(&rooms[14]);
	rooms[14].setLeftRoom(&rooms[8]);
}

void Dungeon::handleMovement(Room* next) {
	if (next->getIndex() == 13) {
		int flag(0);
		for (auto& it : player.getInventory()) {
			if (it.getName() == "Key-13") {
				cout << "\nYou unlock the Room_13 !!!\n";
				player.changeRoom(next);
				flag = 1;
				break;
			}
		}
		if (!flag)
			cout << "\nSorry, you have no corresponding KEY, \"Key-13\", to enter the Room_13. QQ\n";
	}
	else if (next->getIndex() == 2) {
		int flag(0);
		for (auto& it : player.getInventory()) {
			if (it.getName() == "Key-2") {
				cout << "\nYou unlock the Room_2 !!!\n";
				player.changeRoom(next);
				flag = 1;
				break;
			}
		}
		if (!flag)
			cout << "\nSorry, you have no corresponding KEY, \"Key-2\", to enter the Room_2. QQ\n";
	}
	else
		player.changeRoom(next);
}

void Dungeon::handleEvent(Object* object) {
	if (object->getTag() == "Monster") {
		Monster* monster = dynamic_cast<Monster*> (object);
		if (!monster->triggerEvent(&player)) {
			player.getCurrentRoom()->popObject(monster);
			player.setCoin(player.getCoin() + 10);
			cout << "\nCongratulaitons!!! The monster is dead!!!\nYou get 10 coins\n";
		}
	}
	else if (object->getTag() == "NPC") {
		NPC* npc = dynamic_cast<NPC*>(object);
		npc->triggerEvent(&player);
	}
	else if (object->getTag() == "Player") {
		char c = 'A', act = ' ';
		int i(0);
		vector<int> idx;
		idx.reserve(15);
		Player* p = dynamic_cast<Player*> (object);
		cout << "\nWhich equipments do you want to change or equip ?\n";
		for (int j = 0; j < p->getInventory().size(); j++) {
			if (p->getInventory()[j].getTag() == "Item" || p->getInventory()[j].getTag() == "Key" || p->getInventory()[j].getTag() == "BuffPotion" || p->getInventory()[j].getTag() == "DeBuffPotion")
				continue;
			cout << " > " << c << ". " << p->getInventory()[j].getName() << " (" << p->getInventory()[j].getTag() << ", HP: +" << p->getInventory()[j].getHealth() << ", ATK: +" << p->getInventory()[j].getAttack() << ", DEF: +" << p->getInventory()[j].getDefense() << ")\n";
			idx.push_back(j);
			c++;
		}
		cout << " > " << c << ". " << "Quit.\n";
		cin >> act;
		if (act != c && act != c + 32) {
			if (act < 91)
				i += act - 65;
			else
				i += act - 97;
			p->equip(p->getInventory()[idx[i]].getTag(), &(p->getInventory()[idx[i]]));
			p->popItem(p->getInventory()[idx[i]].getName());
		}
	}
}

void Dungeon::startGame() {
	Record record;
	string ans;
	cout << "Do you want to enter the Dungeon? Ans(Y or N): ";
	cin >> ans;
	while (ans != "Y" && ans != "N" && ans != "n" && ans != "y") {
		cout << "\nINVALID INPUT!!!\nLet's try again. Do you want to enter the Dungeon? Ans(Y or N): ";
		cin >> ans;
	}
	if (ans == "N" || ans == "n") {
		cout << "\nAlright, goodbye. (¢E¡s¢E)\n";
		return;
	}
	record.loadFromFile(&player, rooms);
	if (player.getName() == "") {
		cout << "\n---------------------------------------------------------\n\nWelcome to the Dungeon!!!\nPlease enter your name to start the adventure.\nName:";
		createPlayer();
		rooms.clear();
		cout << "\nFriendly Remind : \n > Beat a Monster can earn 10 coins.\n > Buy an Item from the NPC will cost 15 coins.\n\nGood Luck!!!\n\n---------------------------------------------------------\n\n";
		system("pause");
	}
	else {
		do {
			cout << "\nDo you want to load previous data?\n > A. Yes\n > B. No\n";
			cin >> ans;
		} while (ans != "A" && ans != "a" && ans != "B" && ans != "b");
		if (ans == "B" || ans == "b") {
			ofstream file1("Save_player.txt", ios::trunc), file2("Save_room.txt", ios::trunc);
			file1.close();
			file2.close();
			cout << "\n---------------------------------------------------------\n\nWelcome to the Dungeon!!!\nPlease enter your name to start the adventure.\nName:";
			createPlayer();
			rooms.clear();
			cout << "\nFriendly Remind : \n > Beat a Monster can earn 10 coins.\n > Buy an Item from the NPC will cost 15 coins.\n\nGood Luck!!!\n\n---------------------------------------------------------\n\n";
			system("pause");
		}
	}
	player.triggerEvent(&player);
	createMap();
}

void Dungeon::chooseAction() {
	Record record;
	vector<Object*> things = player.getCurrentRoom()->getObjects();
	map<char, char> determine;
	map<int, int> idx;
	int i(0);
	char c = 'A', act = ' ', act_2 = ' ';
	cout << "\nWhat do you want to do?\n";
	if (things.size() > 0 && things[0]->getTag() == "Monster") {
		cout << " > " << c << ". Attack " << things[0]->getName() << ".\n";
		determine[c] = 'm';
		determine[c + 32] = 'm';
		c++;
		for (int j = 0; j < player.getInventory().size(); j++) {
			if (player.getInventory()[j].getTag() == "BuffPotion") {
				cout << " > " << c << ". Use " << player.getInventory()[j].getName() << ".\n";
				determine[c] = 'b';
				determine[c + 32] = 'b';
				idx[c] = j;
				idx[c + 32] = j;
				c++;
				i++;
			}
			else if (player.getInventory()[j].getTag() == "DeBuffPotion") {
				cout << " > " << c << ". Use " << player.getInventory()[j].getName() << ".\n";
				determine[c] = 'D';
				determine[c + 32] = 'D';
				idx[c] = j;
				idx[c + 32] = j;
				c++;
				i++;
			}
		}
		cout << " > " << c << ". Retreat.\n";
		determine[c] = 'w';
		determine[c + 32] = 'w';
		c++;
	}
	else {
		if (player.getCurrentRoom()->getUpRoom()) {
			cout << " > " << c << ". Go up.\n";
			determine[c] = 'u';
			determine[c + 32] = 'u';
			c++;
		}
		if (player.getCurrentRoom()->getDownRoom()) {
			cout << " > " << c << ". Go down.\n";
			determine[c] = 'd';
			determine[c + 32] = 'd';
			c++;
		}
		if (player.getCurrentRoom()->getRightRoom()) {
			cout << " > " << c << ". Go right.\n";
			determine[c] = 'r';
			determine[c + 32] = 'r';
			c++;
		}
		if (player.getCurrentRoom()->getLeftRoom()) {
			cout << " > " << c << ". Go left.\n";
			determine[c] = 'l';
			determine[c + 32] = 'l';
			c++;
		}
		for (auto it : things) {
			if (it->getTag() == "NPC") {
				NPC* n = dynamic_cast<NPC*> (it);
				cout << " > " << c << ". Speak to " << it->getName() << ".\n";
				determine[c] = 'n';
				determine[c + 32] = 'n';
				idx[c] = i;
				idx[c + 32] = i;
			}
			else {
				cout << " > " << c << ". Pick up " << it->getName() << "\n";
				determine[c] = 'p';
				determine[c + 32] = 'p';
				idx[c] = i;
				idx[c + 32] = i;
			}
			i++;
			c++;
		}
	}
	if (player.getCurrentRoom()->getIndex() % 4 == 0) {
		cout << " > " << c << ". Save file.\n";
		determine[c] = 's';
		determine[c + 32] = 's';
		c++;
	}
	cout << " > " << c << ". Others.\n";
	determine[c] = 'o';
	determine[c + 32] = 'o';
	cin >> act;
	switch (determine[act]) {
	case 'u':
		handleMovement(player.getCurrentRoom()->getUpRoom());
		break;
	case 'd':
		handleMovement(player.getCurrentRoom()->getDownRoom());
		break;
	case 'r':
		handleMovement(player.getCurrentRoom()->getRightRoom());
		break;
	case 'l':
		handleMovement(player.getCurrentRoom()->getLeftRoom());
		break;
	case 'm':
		handleEvent(things[idx[act]]);
		break;
	case 'n':
		handleEvent(things[idx[act]]);
		break;
	case 'b':
		cout << "\nYou use the " << player.getInventory()[idx[act]].getName() << ". You become STRONGER !!!\nYour hp +" << player.getInventory()[idx[act]].getHealth() << ", atk +" << player.getInventory()[idx[act]].getAttack() << ", def +" << player.getInventory()[idx[act]].getDefense() << ".\n";
		if (player.getCurrentHealth() + player.getInventory()[idx[act]].getHealth() > player.getMaxHealth())
			player.setCurrentHealth(player.getMaxHealth());
		else
			player.setCurrentHealth(player.getCurrentHealth() + player.getInventory()[idx[act]].getHealth());
		player.setAttack(player.getAttack() + player.getInventory()[idx[act]].getAttack());
		player.setDefense(player.getDefense() + player.getInventory()[idx[act]].getDefense());
		player.popItem(player.getInventory()[idx[act]].getName());
		cout << "\nStatus:\n------------------\n [" << player.getName() << "]\n > Health: " << player.getCurrentHealth() << "/" << player.getMaxHealth() << "\n > Attack: " << player.getAttack() << "\n > Defense: " << player.getDefense() << "\n------------------\n";
		break;
	case 'D':
	{
		cout << "\nYou use " << player.getInventory()[idx[act]].getName() << " to the Monster.\nThe Monster's hp -" << player.getInventory()[idx[act]].getHealth() << ", atk -" << player.getInventory()[idx[act]].getAttack() << ", def -" << player.getInventory()[idx[act]].getDefense() << ".\n";
		Monster* m = dynamic_cast<Monster*> (things[0]);
		m->setCurrentHealth(m->getCurrentHealth() - player.getInventory()[idx[act]].getHealth());
		m->setAttack(m->getAttack() - player.getInventory()[idx[act]].getAttack());
		m->setDefense(m->getDefense() - player.getInventory()[idx[act]].getDefense());
		player.popItem(player.getInventory()[idx[act]].getName());
		if (m->checkIsDead()) {
			player.getCurrentRoom()->popObject(m);
			cout << "\nCongratulaitons!!! The monster is dead!!!\n";
		}
		else
			cout << "\nStatus:\n------------------\n [" << m->getName() << "]\n > Health: " << m->getCurrentHealth() << "/" << m->getMaxHealth() << "\n > Attack: " << m->getAttack() << "\n > Defense: " << m->getDefense() << "\n------------------\n";
		break;
	}
	case 'o':
	{
		if (player.checkMapExist())
			cout << "\n > A. Show status.\n > B. Change Equipment.\n > C. Quit the game.\n > D. Print map.\n > E. Exit.\n";
		else
			cout << "\n > A. Show status.\n > B. Change Equipment.\n > C. Quit the game.\n > D. Exit.\n";
		cin >> act_2;
		if (act_2 == 'A' || act_2 == 'a')
			player.triggerEvent(&player);
		else if (act_2 == 'B' || act_2 == 'b')
			handleEvent(&player);
		else if (act_2 == 'C' || act_2 == 'c') {
			char check;
			cout << "\nAre you sure to quit the Dungeon Game??? (If yes, the system will consider you to be DEAD.)\n > A. Yes, I don't want to stay in the game anymore.\n > B. No, I change my mind.\n";
			cin >> check;
			if (check == 'a' || check == 'A')
				player.setCurrentHealth(0);
			else if (check == 'B' || check == 'b')
				cout << "\nWelcome to come back!!!\n";
		}
		else if (player.checkMapExist() && (act_2 == 'D' || act_2 == 'd'))
			player.printMap();
		break;
	}
	case 'p':
		things[idx[act]]->triggerEvent(&player);
		player.getCurrentRoom()->popObject(things[idx[act]]);
		break;
	case 's':
		record.saveToFile(&player, rooms);
		break;
	case 'w':
		handleMovement(player.getPreviousRoom());
		break;
	default:
		break;
	}
}

bool Dungeon::checkGameLogic() {
	if (!player.checkIsDead())
		return player.getCurrentRoom()->getIsExit();
	return player.checkIsDead();
}

void Dungeon::runDungeon() {
	startGame();
	while (!checkGameLogic())
		chooseAction();
	system("CLS");
	Sleep(300);
	if (player.checkIsDead()) {
		cout << "\n___________________________________________________________________________";
		cout << "\n|                                                                          |";
		cout << "\n|             \033[31m@@@@@   @@@@@@      @      @@@@@       \\     |     /\033[0m         |";
		cout << "\n|             \033[31m@    @  @          @ @     @    @       \\    |    /\033[0m          |";
		cout << "\n|             \033[31m@    @  @@@@@     @   @    @    @        \\   |   /\033[0m           |";
		cout << "\n|             \033[31m@    @  @        @@@@@@@   @    @         \\  |  /\033[0m            |";
		cout << "\n|             \033[31m@@@@@   @@@@@@  @       @  @@@@@           \\ | /\033[0m             |";
		cout << "\n|                                                                          |";
		cout << "\n|                                                                          |";
		cout << "\n| \033[31m@@@@@@     @     @       @  @@@@@@     @@@@@@  @       @  @@@@@@  @@@@@\033[0m  |";
		cout << "\n| \033[31m@         @ @    @@     @@  @          @    @   @     @   @       @    @\033[0m |";
		cout << "\n| \033[31m@   @@   @   @   @ @   @ @  @@@@@      @    @    @   @    @@@@@   @@@@@\033[0m  |";
		cout << "\n| \033[31m@    @  @@@@@@@  @  @ @  @  @          @    @     @ @     @       @  @\033[0m   |";
		cout << "\n| \033[31m@@@@@@ @       @ @   @   @  @@@@@@     @@@@@@      @      @@@@@@  @   @\033[0m  |";
		cout << "\n|__________________________________________________________________________|\n";
	}
	else {
		ofstream file1("Save_player.txt", ios::trunc), file2("Save_room.txt", ios::trunc);
		file1.close();
		file2.close();
		cout << "\n____________________________________________________________________________________";
		cout << "\n|                                                                                   |";
		cout << "\n|                                                                                   |";
		cout << "\n|  \033[1;34m@@@@@@@@@  @@@@@@@@@    @       @   @@@@@@@@@   @@@@@@@@@   @       @     @ @ @\033[0m  |";
		cout << "\n|  \033[1;34m@              @        @@      @       @       @           @       @     @ @ @\033[0m  |";
		cout << "\n|  \033[1;34m@              @        @ @     @       @       @           @       @     @ @ @\033[0m  |";
		cout << "\n|  \033[1;34m@              @        @  @    @       @       @           @       @     @ @ @\033[0m  |";
		cout << "\n|  \033[1;34m@@@@@@@        @        @   @   @       @       @@@@@@@@@   @@@@@@@@@     @ @ @\033[0m  |";
		cout << "\n|  \033[1;34m@              @        @    @  @       @               @   @       @     @ @ @\033[0m  |";
		cout << "\n|  \033[1;34m@              @        @     @ @       @               @   @       @     @ @ @\033[0m  |";
		cout << "\n|  \033[1;34m@              @        @      @@       @               @   @       @\033[0m            |";
		cout << "\n|  \033[1;34m@          @@@@@@@@@    @       @   @@@@@@@@@   @@@@@@@@@   @       @     @ @ @\033[0m  |";
		cout << "\n|                                                                                   |";
		cout << "\n|___________________________________________________________________________________|\n";
	}
}
