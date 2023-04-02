#include "GameCharacter.h"

GameCharacter::GameCharacter() :Object("", "GameCharacter"), maxHealth(0), currentHealth(0), attack(0), defense(0) {}

GameCharacter::GameCharacter(string name, string tag, int hp, int atk, int def) : Object(name, tag), maxHealth(hp), currentHealth(hp), attack(atk), defense(def) {}

bool GameCharacter::checkIsDead() {
	if (currentHealth <= 0)
		return 1;
	return 0;
}

int GameCharacter::takeDamage(int damage) {
	int dam = damage - defense;
	if (dam >= 0)
		return currentHealth - dam;
	else
		return currentHealth;
}

void GameCharacter::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}

void GameCharacter::setCurrentHealth(int currentHealth) {
	this->currentHealth = currentHealth;
}

void GameCharacter::setAttack(int attack) {
	this->attack = attack;
}

void GameCharacter::setDefense(int defense) {
	this->defense = defense;
}

int GameCharacter::getMaxHealth() {
	return maxHealth;
}

int GameCharacter::getCurrentHealth() {
	return currentHealth;
}

int GameCharacter::getAttack() {
	return attack;
}

int GameCharacter::getDefense() {
	return defense;
}
