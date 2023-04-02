#include "Monster.h"

Monster::Monster() :GameCharacter("", "Monster", 0, 0, 0) {}

Monster::Monster(string name, int currentHealth, int attack, int defense) : GameCharacter(name, "Monster", currentHealth, attack, defense) {}

bool Monster::triggerEvent(Object* object) {
	Player* player = dynamic_cast<Player*> (object);
	int m_dam = getAttack() - player->getDefense(), p_dam = player->getAttack() - getDefense();
	if (m_dam < 0)
		m_dam = 0;
	if (p_dam < 0)
		p_dam = 0;
	cout << fight << "\n\nYour attack does " << p_dam << " damage.\n" << this->getName() << "\'s attack does " << m_dam << " damage\n\n";
	player->setCurrentHealth(player->takeDamage(this->getAttack()));
	this->setCurrentHealth(this->takeDamage(player->getAttack()));
	system("pause");
	cout << "\nStatus:\n------------------\n [" << player->getName() << "]\n > Health: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << "\n > Attack: " << player->getAttack() << "\n > Defense: " << player->getDefense() << "\n------------------\n";
	cout << "------------------\n [" << getName() << "]\n > Health: " << getCurrentHealth() << "/" << getMaxHealth() << "\n > Attack: " << getAttack() << "\n > Defense: " << getDefense() << "\n------------------\n";
	if (this->checkIsDead())
		return 0;
	return 1;
}
