#include "Virus.h"
#include "MainGame.h"
#include "Manager.h"
#include "MainGame.h"
USING_NS_CC;
using namespace std;
Virus::Virus()
{
}

Virus::~Virus()
{
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Virus::init()
{
	isDeath = false;
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Virus::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void Virus::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();

}

void Virus::initVirus(int virusIndex)
{
	//获取屏幕大小
	Size size = Director::getInstance()->getWinSize();
	if (virusIndex == 1) {
		//给定血量
		vHp = 1;
		speed = CCRANDOM_0_1()*0.5 + 0.5;
		//初始化病毒
		String* nameStr = String::createWithFormat("v%d.png", virusIndex);
		this->setTexture(nameStr->getCString());
	}
	else if (virusIndex == 2) {
		//给定血量
		vHp = 100;
		speed = CCRANDOM_0_1()*1.0 + 0.5;
		//初始化病毒
		String* nameStr = String::createWithFormat("v%d.png", virusIndex);
		this->setTexture(nameStr->getCString());
	}
	else if (virusIndex == 3) {
		//给定血量
		vHp = 300;
		speed = CCRANDOM_0_1()*0.3 + 0.5;
		//初始化病毒
		String* nameStr = String::createWithFormat("v%d.png", virusIndex);
		this->setTexture(nameStr->getCString());
	}
	else if (virusIndex == 4) {
		//给定血量
		vHp = 150;
		speed = CCRANDOM_0_1()*0.7 + 0.5;
		//初始化病毒
		String* nameStr = String::createWithFormat("v%d.png", virusIndex);
		this->setTexture(nameStr->getCString());
	}
	

	auto & player = Manager::getInstance()->getPlayer();
	Vec2 pos = player.at(0)->getPosition();

	int x = CCRANDOM_0_1()*size.width+pos.x-640;
	int y = CCRANDOM_0_1()*size.height+pos.y-360;

	auto ac1 = RotateBy::create(4, 360);
	this->runAction(RepeatForever::create(ac1));

	//在角色视角外生成virus
	Vec2 pos1 = Vec2(-30+pos.x-640,y);
	Vec2 pos2 = Vec2(size.width+30+pos.y-360, y);
	Vec2 pos3 = Vec2(x, -30+ pos.y - 360);
	Vec2 pos4 = Vec2(x, pos.y - 360+size.height+30);
	
	//随机生成
	int is = CCRANDOM_0_1() * 4;

	if(is==0){
		this->setPosition(pos1);
	}
	else if(is==1){
		this->setPosition(pos2);
	}
	else if (is == 2) {
		this->setPosition(pos3);
	}
	else {
		this->setPosition(pos4);
	}
}

void Virus::update(float delta)
{
	if (isDeath) {
		return;
	}
	auto & player = Manager::getInstance()->getPlayer();
	Vec2 pos = player.at(0)->getPosition();
	
	float x = pos.x - this->getPositionX();
	float y = pos.y - this->getPositionY();
	float c = sqrtf(pow(x, 2) + pow(y, 2));

	//移动
	if (pos.x - this->getPositionX() > 0)
		this->setPositionX(getPositionX() + speed*abs(x/c));
	else
		this->setPositionX(getPositionX() - speed*abs(x / c));

	if(pos.y - this->getPositionY() > 0)
		this->setPositionY(getPositionY() + speed*abs(y / c));
	else
		this->setPositionY(getPositionY() - speed*abs(y / c));
}

int Virus::getHP()
{
	return vHp;
}

void Virus::setHP(int hp)
{
	this->vHp = hp;
}

void Virus::virusDeath()
{
	auto reAc = RemoveSelf::create();
	this->runAction(reAc);
	Manager::getInstance()->removeVirus(this);
}
