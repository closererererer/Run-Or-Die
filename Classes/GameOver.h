#pragma once

#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void cleanup();
	virtual void onEnterTransitionDidFinish();

	void nextScene(Ref* pSender);
	void Exit(Ref* pSender);
	void helloScene(Ref* pSender);
	CREATE_FUNC(GameOver);
};

#endif // __HELLOWORLD_SCENE_H__
