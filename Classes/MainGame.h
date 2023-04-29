#pragma once

#ifndef __MainGame_SCENE_H__
#define __MainGame_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class MainGame : public cocos2d::Scene
{
public:
	//��ͼ
	Sprite* bg;
	//��ɫ
	Sprite* player;
	int hp;
	int level;
	float speed;//�ƶ��ٶ�
	bool moveUp;//�ƶ�����
	bool moveDown;
	bool moveLeft;
	bool moveRight;
	int exper;

	//���｣
	Sprite* fight[4];
	String* nameStr;
	int damage;//��ǰ�ӵ��˺�

	//�������
	Point endPoint;
	
	//����
	Sprite* sup2;//����2
	Sprite* sup3[4];//����3
	//�ռ�����
	int power;
	bool isOK;
	Sprite* skill;

	//UI���
	Sprite* uiSprite;
	Label* labelScore;
	Label* labelLevel;
	int scoreNow = 0;
	ProgressTimer* progress;//������
	ProgressTimer* progress1;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void update(float delta);
	virtual void cleanup();

	//��ɫ��ʼ��
	void initPlayer();
	void playerDeath();

	//���｣��ʼ��
	void initFight();

	//���㴥������
	bool onTouchBegan(Touch *touch, Event *et);
	void onTouchMoved(Touch *touch, Event *et);
	void onTouchEnded(Touch *touch, Event *et);
	
	//���̼����¼�
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode,Event* et);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* et);
	//��Ӳ���
	void addVirus(float delta);

	//��Ӽ��ܰ�
	void addSupport(Vec2 point);

	//����ִ��
	void supportMaking(int index);
	//����2ʵ��
	void updateSup2(float tm);//����2����
	void overSup2();//��������2
	//����3ʵ��
	void updateSup3(float tm);//����2����
	void overSup3();//��������2
	//����4ʵ��
	void overSup4();
	//�ռ���
	void finalSkill();
	void finalSkillUpdate(float tm);
	void finalSkillOver();

	//��ײ��⺯��
	void isCrash(float tm);

	//���ֽ�ɫ������
	void setViewpointCenter(Vec2 pos);

	CREATE_FUNC(MainGame);
};

#endif // __HELLOWORLD_SCENE_H__