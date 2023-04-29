#pragma once

#ifndef __MainGame_SCENE_H__
#define __MainGame_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class MainGame : public cocos2d::Scene
{
public:
	//地图
	Sprite* bg;
	//角色
	Sprite* player;
	int hp;
	int level;
	float speed;//移动速度
	bool moveUp;//移动方向
	bool moveDown;
	bool moveLeft;
	bool moveRight;
	int exper;

	//手里剑
	Sprite* fight[4];
	String* nameStr;
	int damage;//当前子弹伤害

	//点击坐标
	Point endPoint;
	
	//技能
	Sprite* sup2;//技能2
	Sprite* sup3[4];//技能3
	//终极技能
	int power;
	bool isOK;
	Sprite* skill;

	//UI组件
	Sprite* uiSprite;
	Label* labelScore;
	Label* labelLevel;
	int scoreNow = 0;
	ProgressTimer* progress;//进度条
	ProgressTimer* progress1;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void update(float delta);
	virtual void cleanup();

	//角色初始化
	void initPlayer();
	void playerDeath();

	//手里剑初始化
	void initFight();

	//单点触摸函数
	bool onTouchBegan(Touch *touch, Event *et);
	void onTouchMoved(Touch *touch, Event *et);
	void onTouchEnded(Touch *touch, Event *et);
	
	//键盘监听事件
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode,Event* et);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* et);
	//添加病毒
	void addVirus(float delta);

	//添加技能包
	void addSupport(Vec2 point);

	//技能执行
	void supportMaking(int index);
	//技能2实现
	void updateSup2(float tm);//技能2监听
	void overSup2();//结束技能2
	//技能3实现
	void updateSup3(float tm);//技能2监听
	void overSup3();//结束技能2
	//技能4实现
	void overSup4();
	//终极技
	void finalSkill();
	void finalSkillUpdate(float tm);
	void finalSkillOver();

	//碰撞检测函数
	void isCrash(float tm);

	//保持角色在中心
	void setViewpointCenter(Vec2 pos);

	CREATE_FUNC(MainGame);
};

#endif // __HELLOWORLD_SCENE_H__