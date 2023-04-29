#include "Support.h"
#include "SimpleAudioEngine.h"
#include "Manager.h"
USING_NS_CC;
Support::Support()
{
}
Support::~Support()
{
}
void Support::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
}
void Support::onExit()
{
	Sprite::onExit();
}
bool Support::init()
{
	if (!Sprite::init())
		return false;
	return true;
}

void Support::initSupport(int i,Vec2 point)
{
	index = i;
	//加载图片
	this->initWithFile(String::createWithFormat("s%d.png", index)->getCString());

	//获取屏幕大小
	auto size = Director::getInstance()->getWinSize();

	String* nameStr = String::createWithFormat("sup%d.png", index);
	this->setTexture(nameStr->getCString());
	this->setPosition(point);


}

int Support::getIndex()
{
	return index;
}

void Support::remove()
{
	auto reAc = RemoveSelf::create();
	this->runAction(reAc);
	Manager::getInstance()->removeSupport(this);
}

void Support::removeEX()
{
	auto reAc = RemoveSelf::create();
	this->runAction(reAc);
	Manager::getInstance()->removeEX(this);
}
