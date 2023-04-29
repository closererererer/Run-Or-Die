#pragma once
#ifndef __Support_SCENE_H__
#define __Support_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Support :public::cocos2d::Sprite {
public:
	int index;//support类型
public:
	Support();
	~Support();
	void onEnterTransitionDidFinish();
	void onExit();
	virtual bool init();
	//初始化
	void initSupport(int index,Vec2 point);//根据index的不同来建立不同子弹资源
	int getIndex();
	void remove();

	void removeEX();
	CREATE_FUNC(Support);


};

#endif