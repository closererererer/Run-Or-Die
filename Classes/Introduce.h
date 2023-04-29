#pragma once

#ifndef __Introduce_SCENE_H__
#define __Introduce_SCENE_H__

#include "cocos2d.h"

class Introduce : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void Exit(Ref* pSender);

	CREATE_FUNC(Introduce);
};

#endif // __HELLOWORLD_SCENE_H__