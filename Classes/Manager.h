#pragma once
#ifndef __MANAGER_BASE_H_
#define __MANAGER_BASE_H_


#include "Virus.h"
#include "cocos2d.h"
#include "Support.h"
USING_NS_CC;

class Manager {
	Manager();
	~Manager();
public:
	static Manager * manager;
	Vector<Sprite*> player;
	Vector<Virus*> virusList;
	Vector<Support*> supportList;
	Vector<Support*> exList;
	int score;
public:
	//����
	static Manager* getInstance();
	//ɾ��
	static void deleteInstance();

	//���player
	void addPlayer(Sprite* p);
	void removePlayer(Sprite* p);
	Vector<Sprite*>& getPlayer() {
		return player;
	}
	
	//virus����
	Vector<Virus*>& getVirus() {
		return virusList;
	}
	//���virus
	void setVirus(Virus* v);
	void removeVirus(Virus* v);

	//supprot����
	Vector<Support*>& getSupport() {
		return supportList;
	}
	void setSupport(Support* s);
	void removeSupport(Support* s);

	//experience����
	Vector<Support*>& getEX() {
		return exList;
	}
	void setEX(Support* s);
	void removeEX(Support* s);

	//��ȡ����
	void setScore(int s);
	int getScore();
	void removeAll();
};


#endif