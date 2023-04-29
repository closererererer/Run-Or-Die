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
	//创建
	static Manager* getInstance();
	//删除
	static void deleteInstance();

	//添加player
	void addPlayer(Sprite* p);
	void removePlayer(Sprite* p);
	Vector<Sprite*>& getPlayer() {
		return player;
	}
	
	//virus管理
	Vector<Virus*>& getVirus() {
		return virusList;
	}
	//添加virus
	void setVirus(Virus* v);
	void removeVirus(Virus* v);

	//supprot管理
	Vector<Support*>& getSupport() {
		return supportList;
	}
	void setSupport(Support* s);
	void removeSupport(Support* s);

	//experience管理
	Vector<Support*>& getEX() {
		return exList;
	}
	void setEX(Support* s);
	void removeEX(Support* s);

	//获取分数
	void setScore(int s);
	int getScore();
	void removeAll();
};


#endif