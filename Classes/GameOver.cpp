#include "GameOver.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainGame.h"
#include "Manager.h"
USING_NS_CC;
using namespace CocosDenshion;


cocos2d::Scene * GameOver::createScene()
{
	return GameOver::create();
}

bool GameOver::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg2.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg);

	auto nameStr = String::createWithFormat("Score: %d", Manager::getInstance()->getScore());
	auto label = Label::createWithTTF(nameStr->getCString(), "fonts/arial.ttf", 76);
	label->setColor(ccc3(0, 0, 0));
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2+150);
	this->addChild(label);

	auto menuItem1 = MenuItemFont::create("RESTART", CC_CALLBACK_1(GameOver::nextScene, this));
	menuItem1->setFontNameObj("Comic Sans MS");
	menuItem1->setFontSize(36);
	menuItem1->setColor(ccc3(0, 0, 0));

	auto menuItem2 = MenuItemFont::create("BACK MENU", CC_CALLBACK_1(GameOver::helloScene, this));
	menuItem2->setFontNameObj("Comic Sans MS");
	menuItem2->setFontSize(36);
	menuItem2->setColor(ccc3(0, 0, 0));

	auto menuItem3 = MenuItemFont::create("EXIT", CC_CALLBACK_1(GameOver::Exit, this));
	menuItem3->setFontNameObj("Comic Sans MS");
	menuItem3->setFontSize(36);
	menuItem3->setColor(ccc3(0, 0, 0));

	auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 -50);
	this->addChild(menu, 2);

	auto s5 = Sprite::create("v4.png");
	s5->setPosition(Vec2(1300, 50));
	this->addChild(s5, 0);
	auto ac1 = JumpTo::create(12, Vec2(0, 50), 30, 12);
	auto ac2 = JumpTo::create(12, Vec2(1300, 50), 30, 12);
	auto ac3 = FlipX::create(true);
	auto ac4 = FlipX::create(false);
	s5->runAction(RepeatForever::create(Sequence::create(ac1, ac3, ac2, ac4, NULL)));

	

	return true;
}

void GameOver::cleanup()
{
	Scene::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("Radio/m3.mp3");
}

void GameOver::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Radio/m3.mp3", true);
}

void GameOver::nextScene(Ref * pSender)
{
	Director::getInstance()->replaceScene(MainGame::createScene());
}

void GameOver::Exit(Ref * pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)  
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
	#endif  

		Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
		exit(0);
	#endif  
}

void GameOver::helloScene(Ref * pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
