#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;

class Player : public GameCharacter
{
private:
	Room* currentRoom;
	Room* previousRoom;
	int coin;
	vector<Item> backpack;
	map<string, Item> inventory;
	bool MapExist = 0;
	string Map[40] = {
		" ___________________________________________________________________________________ ",
		"|                                                                                   |",
		"|                 -------                     -------                               |",
		"|                |       |                   |       |                              |",
		"|                |       |                   |       |                              |",
		"|                |       |                   |       |                              |",
		"|                 -------                     -------                               |",
		"|                    *                           *                                  |",
		"|                    *                           *                                  |",
		"|                    *                           *                                  |",
		"|                 -------       -------       -------       -------                 |",
		"|                |       |     |       |     |       |     |       |                |",
		"|                |       |*****|       |*****|       |*****|       |                |",
		"|                |       |     |       |     |       |     |       |                |",
		"|                 -------       -------       -------       -------                 |",
		"|                    *                           *             *                    |",
		"|                    *                           *             *                    |",
		"|                    *                           *             *                    |",
		"|   -------       -------                     -------       -------       -------   |",
		"|  |       |     |       |                   |       |     |       |     |       |  |",
		"|  |       |*****|       |                   |       |*****|       |*****|       |  |",
		"|  |       |     |       |                   |       |     |       |     |       |  |",
		"|   -------       -------                     -------       -------       -------   |",
		"|                                                *                                  |",
		"|                                                *                                  |",
		"|                                                *                                  |",
		"|                               -------       -------                               |",
		"|                              |       |     |       |                              |",
		"|                              |       |*****|       |                              |",
		"|                              |       |     |       |                              |",
		"|                               -------       -------                               |",
		"|                                  *             *                                  |",
		"|                                  *             *                                  |",
		"|                                  *             *                                  |",
		"|                               -------       -------                               |",
		"|                              |       |     |       |                              |",
		"|                              |       |*****|       |                              |",
		"|                              |       |     |       |                              |",
		"|                               -------       -------        X : Player's Position  |",
		"|___________________________________________________________________________________|"
	};
public:
	Player();
	Player(string, int, int, int, int);
	void addItem(Item);
	void popItem(string);
	void increaseStatus(int, int, int);
	void changeRoom(Room*);
	void printMap();
	void equip(string, Item*);
	bool checkMapExist();

	/* Virtual function that you need to complete   */
	/* In Player, this function should show the     */
	/* status of player.                            */
	bool triggerEvent(Object*);

	/* Set & Get function*/
	void setCurrentRoom(Room*);
	void setPreviousRoom(Room*);
	void setInventory(vector<Item>);
	void setBackpack(map<string, Item>);
	void setCoin(int);
	Room* getCurrentRoom();
	Room* getPreviousRoom();
	vector<Item> getInventory();
	map<string, Item> getBackpack();
	int getCoin();
};

#endif // PLAYER_H_INCLUDED
