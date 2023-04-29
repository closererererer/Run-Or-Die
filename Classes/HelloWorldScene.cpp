
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainGame.h"
#include "Introduce.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg3.png");
	bg->setPosition(visibleSize.width * 0.5, visibleSize.height*0.5);
	this->addChild(bg);


	auto menuItem1 = MenuItemFont::create("GAME START", CC_CALLBACK_1(HelloWorld::nextScene, this));
	menuItem1->setFontNameObj("Comic Sans MS");
	menuItem1->setFontSize(36);
	menuItem1->setColor(ccc3(0, 0, 0));

	auto menuItem2 = MenuItemFont::create("INTRODUCE", CC_CALLBACK_1(HelloWorld::introduceScene, this));
	menuItem2->setFontNameObj("Comic Sans MS");
	menuItem2->setFontSize(36);
	menuItem2->setColor(ccc3(0, 0, 0));

	auto menuItem3 = MenuItemFont::create("EXIT", CC_CALLBACK_1(HelloWorld::Exit, this));
	menuItem3->setFontNameObj("Comic Sans MS");
	menuItem3->setFontSize(36);
	menuItem3->setColor(ccc3(0, 0, 0));

	auto menu = Menu::create(menuItem1, menuItem2, menuItem3,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2-100);
	this->addChild(menu,2);

	auto s1 = Sprite::create("b3.png");
	s1->setPosition(visibleSize.width / 2, visibleSize.height*0.7);
	s1->setScale(2);
	this->addChild(s1,1);
	s1->runAction(RepeatForever::create(RotateBy::create(2, 360)));

	auto s2 = Sprite::create("v3.png");
	s2->setPosition(10, visibleSize.height*0.2-20);
	s2->setScale(4);
	this->addChild(s2,1);
	s2->runAction(RepeatForever::create(RotateBy::create(5, 360)));

	auto s3 = Sprite::create("s2.png");
	s3->setPosition(visibleSize.width, visibleSize.height*0.7);
	this->addChild(s3);
	s3->runAction(RepeatForever::create(RotateBy::create(6, 360)));

	auto s4 = Sprite::create("sup0.png");
	s4->setPosition(60, visibleSize.height*0.9+20);
	this->addChild(s4);

	auto s5 = Sprite::create("v4.png");
	s5->setPosition(Vec2(1300, 50));
	this->addChild(s5,0);
	auto ac1 = JumpTo::create(12, Vec2(0, 50),30,12);
	auto ac2 = JumpTo::create(12, Vec2(1300, 50), 30, 12);
	auto ac3 = FlipX::create(true);
	auto ac4 = FlipX::create(false);
	s5->runAction(RepeatForever::create(Sequence::create(ac1,ac3,ac2,ac4,NULL)));

	SimpleAudioEngine::getInstance()->playBackgroundMusic("Radio/m1.mp3",true);
    return true;
}

void HelloWorld::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Radio/m1.mp3", true);
}

void HelloWorld::cleanup()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("Radio/m1.mp3");
	Scene::cleanup();
}

void HelloWorld::nextScene(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Radio/click.mp3");
	Director::getInstance()->replaceScene(MainGame::createScene());
}

void HelloWorld::introduceScene(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Radio/click.mp3");
	Director::getInstance()->pushScene(Introduce::createScene());
}

void HelloWorld::Exit(Ref * pSender)
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

