#include "Manager.h"
Manager* Manager::manager = NULL;

Manager::Manager()
{
	score = 0;
}

Manager::~Manager()
{
}

Manager * Manager::getInstance()
{
	if (manager == NULL) {
		manager = new Manager();
	}
	return manager;
}

void Manager::deleteInstance()
{
	if (manager) {
		delete manager;
		manager = NULL;
	}
}

void Manager::addPlayer(Sprite * p)
{
	player.pushBack(p);
}

void Manager::removePlayer(Sprite * p)
{
	player.eraseObject(p);
}

void Manager::setVirus(Virus * v)
{
	virusList.pushBack(v);
}

void Manager::removeVirus(Virus * v)
{
	virusList.eraseObject(v);
}

void Manager::setSupport(Support * s)
{
	supportList.pushBack(s);
}

void Manager::removeSupport(Support * s)
{
	supportList.eraseObject(s);
}

void Manager::setEX(Support * s)
{
	exList.pushBack(s);
}

void Manager::removeEX(Support * s)
{
	exList.eraseObject(s);
}

void Manager::setScore(int s)
{
	score = s;
}

int Manager::getScore()
{
	return score;
}

void Manager::removeAll()
{

	manager = NULL;
}

