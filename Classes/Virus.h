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
	float speed;//�ƶ��ٶ�
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
	
	//��ȡHP
	int getHP();
	void setHP(int hp);

	//����
	void virusDeath();

	CREATE_FUNC(Virus);
};

#endif // _HELLOWORLD_SCENE_H__