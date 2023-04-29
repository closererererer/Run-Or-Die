#pragma once
#ifndef __Support_SCENE_H__
#define __Support_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Support :public::cocos2d::Sprite {
public:
	int index;//support����
public:
	Support();
	~Support();
	void onEnterTransitionDidFinish();
	void onExit();
	virtual bool init();
	//��ʼ��
	void initSupport(int index,Vec2 point);//����index�Ĳ�ͬ��������ͬ�ӵ���Դ
	int getIndex();
	void remove();

	void removeEX();
	CREATE_FUNC(Support);


};

#endif