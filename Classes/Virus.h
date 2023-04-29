#pragma 
#ifndef __Virus_SCENE_H__
#define __Virus_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Virus : public cocos2d::Sprite
{
public:
	int vHp;
	float speed;//移动速度
	bool isDeath;
public:
	Virus();
	~Virus();
public:
	virtual bool init();
	void onEnterTransitionDidFinish();
	void onExit();

	void initVirus(int virusIndex);
	virtual void update(float delta);
	
	//获取HP
	int getHP();
	void setHP(int hp);

	//死亡
	void virusDeath();

	CREATE_FUNC(Virus);
};

#endif // _HELLOWORLD_SCENE_H__