#include "Introduce.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
cocos2d::Scene * Introduce::createScene()
{
	return Introduce::create();
}

bool Introduce::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg1.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg);

	auto s1 = Sprite::create("bg4.png");
	s1->setPosition(visibleSize.width / 2, visibleSize.height/2 +60);
	this->addChild(s1,2);


	auto menuItem = MenuItemFont::create("BACK", CC_CALLBACK_1(Introduce::Exit, this));
	menuItem->setFontNameObj("Comic Sans MS");
	menuItem->setFontSize(36);
	menuItem->setColor(ccc3(0, 0, 0));

	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(100, visibleSize.height - 50);
	this->addChild(menu, 2);

	auto s5 = Sprite::create("v4.png");
	s5->setPosition(Vec2(1300, 50));
	this->addChild(s5, 0);
	auto ac1 = JumpTo::create(12, Vec2(-20, 50), 30, 12);
	auto ac2 = JumpTo::create(12, Vec2(1300, 50), 30, 12);
	auto ac3 = FlipX::create(true);
	auto ac4 = FlipX::create(false);
	s5->runAction(RepeatForever::create(Sequence::create(ac1, ac3, ac2, ac4, NULL)));

	return true;
}



void Introduce::Exit(Ref * pSender)
{
	Director::getInstance()->popScene();
	SimpleAudioEngine::getInstance()->playEffect("Radio/click.mp3");
}
