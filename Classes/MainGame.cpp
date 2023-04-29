
#include "MainGame.h"
#include "SimpleAudioEngine.h"
#include "Virus.h"
#include "Manager.h"
#include "Support.h"
#include "GameOver.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* MainGame::createScene()
{
	return MainGame::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	//变量初始化
	moveUp = false;
	moveLeft = false;
	moveRight = false;
	moveDown = false;
	speed = 3;
	level = 1;
	damage = 1;
	exper = 0;
	power = 0;
	hp = 100;
	isOK = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//变量定义
	endPoint = Point(visibleSize.width / 2, visibleSize.height / 2);


	//背景
	bg = Sprite::create("bg2.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg,-1);

	initPlayer();//初始化角色
	
	//--------------单点触摸事件监听器---------------
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
	//设置吞噬触摸
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(listener, player);
	//------------------------------------------------
	uiSprite = Sprite::create();
	uiSprite->setPosition(0, visibleSize.height - 50);
	this->addChild(uiSprite,20);

	labelScore = Label::createWithTTF(String::createWithFormat("Score: %d",scoreNow)->getCString(), "fonts/arial.ttf", 30);
	labelScore->setColor(ccc3(0, 0, 0));
	labelScore->setPosition(100,0);
	uiSprite->addChild(labelScore,4);
	
	labelLevel = Label::createWithTTF(String::createWithFormat("Level: %d", level)->getCString(), "fonts/arial.ttf", 30);
	labelLevel->setColor(ccc3(0, 0, 0));
	labelLevel->setPosition(300, 0);
	uiSprite->addChild(labelLevel, 4);
	
	//创建进度条
	//HP
	auto jc2 = Sprite::create("jc1.png");
	jc2->setPosition(120, -25);
	uiSprite->addChild(jc2);

	auto j2 = Sprite::create("j2.png");
	progress1 = ProgressTimer::create(j2);
	progress1->setPosition(120, -25);
	progress1->setType(ProgressTimer::Type::BAR);
	progress1->setMidpoint(Vec2(0, 0.5));
	progress1->setBarChangeRate(Vec2(1, 0));
	progress1->setPercentage(100);
	uiSprite->addChild(progress1, 1, 10);

	//技能条
	auto jc1 = Sprite::create("jc1.png");
	jc1->setPosition(120, -40);
	uiSprite->addChild(jc1);

	auto j1 = Sprite::create("j1.png");
	progress = ProgressTimer::create(j1);
	progress->setPosition(120, -40);
	progress->setType(ProgressTimer::Type::BAR);
	progress->setMidpoint(Vec2(0, 0.5));
	progress->setBarChangeRate(Vec2(1, 0));
	progress->setPercentage(0);
	uiSprite->addChild(progress,1,10);

	auto l1 = Label::createWithTTF("HP","fonts/arial.ttf",16);
	l1->setPosition(30,-25);
	l1->setColor(ccc3(0, 0, 0));
	uiSprite->addChild(l1);
	auto l2 = Label::createWithTTF("F", "fonts/arial.ttf", 16);
	l2->setPosition(30, -40);
	l2->setColor(ccc3(0, 0, 0));
	uiSprite->addChild(l2);

	return true;
}

void MainGame::onEnter()
{
	Scene::onEnter();
	//-------------键盘监听事件---------------------
	EventListenerKeyboard*listener1 = EventListenerKeyboard::create();

	listener1->onKeyPressed = CC_CALLBACK_2(MainGame::onKeyPressed, this);
	listener1->onKeyReleased = CC_CALLBACK_2(MainGame::onKeyReleased, this);

	EventDispatcher* eventdis = Director::getInstance()->getEventDispatcher();
	eventdis->addEventListenerWithSceneGraphPriority(listener1, this);
	//---------------------------------------------
}

void MainGame::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	scheduleUpdate();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Radio/m2.mp3", true);
	//病毒
	this->schedule(SEL_SCHEDULE(&MainGame::addVirus), 0.5f);
	//碰撞逻辑检测
	this->schedule(SEL_SCHEDULE(&MainGame::isCrash));
}

void MainGame::update(float delta)
{
	//移动并判定边界
	if (moveUp) {
		if (player->getPositionY()<1440) {
			player->setPositionY(player->getPositionY() + speed);
		}
		else {
			player->setPositionY(1440);
		}
	}
	if (moveDown) {
		if (player->getPositionY()>-720) {
			player->setPositionY(player->getPositionY() - speed);
		}
		else {
			player->setPositionY(-720);
		}
	}
	if (moveLeft) {
		if (player->getPositionX()>-1280) {
			player->setPositionX(player->getPositionX() - speed);
		}
		else {
			player->setPositionX(-1280);
		}
	}
	if (moveRight) {
		if (player->getPositionX()<2560) {
			player->setPositionX(player->getPositionX() + speed);
		}
		else {
			player->setPositionX(2560);
		}
	}
	setViewpointCenter(player->getPosition());
	
	if (level < 4) {
		labelLevel->setString(String::createWithFormat("Level: %d", level)->getCString());
	}
	else {
		labelLevel->setString("Level: 4(MAX)");
	}

	//进度条控制
	if (power <= 20)
		//修改进度条进度.
		progress->setPercentage(power*5);
	progress1->setPercentage(hp);

}

void MainGame::cleanup()
{
	Scene::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("Radio/m2.mp3");
	this->removeAllChildren();
	Manager::getInstance()->removeAll();
}

void MainGame::initPlayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//添加角色
	player = Sprite::create("player.png");
	player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	player->setAnchorPoint(Point(0.5, 0.5));
	player->setScale(1.2);
	this->addChild(player, 1);
	
	auto ac = RotateBy::create(2, 360);
	player->runAction(RepeatForever::create(ac));
	initFight();
	Manager::getInstance()->addPlayer(player);

}

void MainGame::playerDeath()
{
	Manager::getInstance()->setScore(scoreNow);
	this->removeChild(player);
	Director::getInstance()->replaceScene(GameOver::createScene());
}

void MainGame::initFight()
{
	player->removeAllChildren();
	if (level <=2) {
		nameStr = String::createWithFormat("b%d.png", 1);
	}
	else if (level == 3) {
		nameStr = String::createWithFormat("b%d.png", 2);
	}
	else {
		nameStr = String::createWithFormat("b%d.png", 3);
	}
	for (int j = 0; j < 4; j++) {	
		fight[j] = Sprite::create();
		fight[j]->setTexture(nameStr->getCString());
	} 

	//这里添加子节点位置有偏移，改了很多地方都没解决，最后手动设置
	fight[0]->setPosition(Vec2(15, -60));
	fight[1]->setPosition(Vec2(90, 15));
	fight[2]->setPosition(Vec2(15, 90));
	fight[3]->setPosition(Vec2(-60, 15));

	

	if (level == 1) {//一级
		player->addChild(fight[0]);
		auto ac = RotateBy::create(0.8, 360);
		fight[0]->runAction(RepeatForever::create(ac));
	}
	else{
		for (int j = 0; j < 4; j++) {
			player->addChild(fight[j]);
			auto ac = RotateBy::create(0.8, 360);
			fight[j]->runAction(RepeatForever::create(ac));
		}
	}
	
	
}

bool MainGame::onTouchBegan(Touch * touch, Event * et)
{
	//获取点击点
	endPoint = touch->getLocation();
	
	return true;

}

void MainGame::onTouchMoved(Touch * touch, Event * et)
{
	////获取移动距离
	//auto point2 = touch->getLocation() - touch->getPreviousLocation();
	//player->setPosition(player->getPosition() + point2);

	////判断移动范围，防止超出边界
	//auto size = Director::getInstance()->getWinSize();
	//auto player_size = player->getContentSize();
	////x方向
	//if (player->getPositionX() < 0) {
	//	player->setPositionX(0);
	//}
	//else if (player->getPositionX() > size.width) {
	//	player->setPositionX(size.width);
	//}

	////y方向
	//if (player->getPositionY() < 0) {
	//	player->setPositionY(0);
	//}
	//else if (player->getPositionY() > size.height) {
	//	player->setPositionY(size.height);
	//}

}

void MainGame::onTouchEnded(Touch * touch, Event * et)
{
	//endPoint = touch->getLocation();
	//this->schedule(SEL_SCHEDULE(&MainGame::playerRun), 1.0f);
}

void MainGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * et)
{
	log("%d", keyCode);
	switch (int(keyCode))
	{
	case 146:
		moveUp = true;
		break;
	case 142:
		moveDown = true;
		break;
	case 124:
		moveLeft = true;
		break;
	case 127:
		moveRight = true;
		break;
	case 129:
		if (isOK) {
			isOK = false;
			power = 0;
			finalSkill();
		}
		break;
	case 6:
		Manager::getInstance()->setScore(scoreNow);
		Director::getInstance()->replaceScene(GameOver::createScene());
		break;
	default:
		break;
	}
}

void MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * et)
{
	switch (int(keyCode))
	{
	case 146:
		moveUp = false;
		break;
	case 142:
		moveDown = false;
		break;
	case 124:
		moveLeft = false;
		break;
	case 127:
		moveRight = false;
		break;
	default:
		break;
	}
}

void MainGame::addVirus(float delta)
{
	auto virus = Virus::create();
	float ran=CCRANDOM_0_1();
	if (ran < 0.5) {
		virus->initVirus(1);
	}
	else if(ran>=0.5&&ran<0.8){
		virus->initVirus(2);
	}
	else if (ran >= 0.8&&ran<0.85) {
		virus->initVirus(3);
	}
	else if (ran >= 0.85&&ran<1) {
		virus->initVirus(4);
	}
	
	this->addChild(virus);
	
	//将virus添加到管理器
	Manager::getInstance()->setVirus(virus);
}

void MainGame::addSupport(Vec2 point)
{
	if (CCRANDOM_0_1() > 0.8) {
		auto supp = Support::create();
		supp->initSupport(CCRANDOM_0_1() * 4 + 1, point);
		this->addChild(supp);
		//将supp添加到管理器
		Manager::getInstance()->setSupport(supp);
		auto ac1 = MoveTo::create(0.3, supp->getPosition() + Vec2(20, 30));
		auto ac2 = MoveTo::create(0.3, supp->getPosition() - Vec2(-40, 30));
		supp->runAction(Sequence::create(ac1, ac2, NULL));
	}
	auto ex = Support::create();
	ex->initSupport(0, point);
	this->addChild(ex);
	//将supp添加到管理器
	Manager::getInstance()->setEX(ex);
	auto ac1 = MoveTo::create(0.3, ex->getPosition() + Vec2(-20, 30));
	auto ac2 = MoveTo::create(0.3, ex->getPosition() - Vec2(20, 30));
	ex->runAction(Sequence::create(ac1, ac2, NULL));

}

void MainGame::supportMaking(int index)
{
	//技能1
	if (index == 1) {
		log("support1");
		auto sup1 = Sprite::create("s1.png");
		sup1->setPosition(player->getPosition());
		sup1->setScale(1.5);
		this->addChild(sup1,3);

		//碰撞检测
		auto & virusList = Manager::getInstance()->getVirus();
		for (int i = virusList.size() - 1; i >= 0; i--) {
			//病毒
			auto virus = virusList.at(i);
			if (virus->getHP() <= 0) {
				//若死亡则不检测
				continue;
			}
			auto rect = sup1->getBoundingBox();
			auto point = virus->getPosition();

			//判断是否碰撞
			if (rect.containsPoint(point)) {
				//主角死亡
				virus->setHP(virus->getHP() - 100);
				if (virus->getHP() <= 0) {
					addSupport(virus->getPosition());
					virus->virusDeath();
				}
			}
		}
		SimpleAudioEngine::getInstance()->playEffect("Radio/beng.mp3");
		//执行动画并清除
		auto ac1 = FadeIn::create(0.5);
		auto ac2 = FadeOut::create(1);
		auto ac3 = RemoveSelf::create();
		auto ac4 = Sequence::create(ac1,ac2,ac3,NULL);
		sup1->runAction(ac4);
	}

	//技能2
	if (index == 2) {
		this->removeChild(sup2);
		sup2 = Sprite::create("s2.png");
		sup2->setPosition(player->getPosition());
		speed = 8;
		this->addChild(sup2, 3);
		this->schedule(SEL_SCHEDULE(&MainGame::updateSup2));
		auto ac1 = RotateBy::create(0.5, 360);
		sup2->runAction(RepeatForever::create(ac1));
		sup2->runAction(Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(MainGame::overSup2, this)), NULL));

		SimpleAudioEngine::getInstance()->playEffect("Radio/go.mp3");
	}

	//技能3
	if (index == 3) {
		MoveTo* ac3[4];
		ac3[0] = MoveTo::create(0.5, player->getPosition() + Vec2(-500, 0));
		ac3[1] = MoveTo::create(0.5, player->getPosition() + Vec2(500, 0));
		ac3[2] = MoveTo::create(0.5, player->getPosition() + Vec2(0, 500));
		ac3[3] = MoveTo::create(0.5, player->getPosition() + Vec2(0, -500));
		for (int i = 0; i < 4; i++) {
			sup3[i] = Sprite::create("s3.png");
			sup3[i]->setPosition(player->getPosition());
			this->addChild(sup3[i]);
			sup3[i]->runAction(RepeatForever::create(RotateBy::create(0.4, 360)));
		}
		this->schedule(SEL_SCHEDULE(&MainGame::updateSup3));
		for (int i = 0; i < 4; i++) {
			sup3[i]->runAction(Sequence::create(ac3[i], DelayTime::create(1) , CallFunc::create(CC_CALLBACK_0(MainGame::overSup3, this)), RemoveSelf::create(), NULL));
		}
		SimpleAudioEngine::getInstance()->playEffect("Radio/fire.mp3");
	}

	if (index == 4) {
		speed = 8;
		if (hp < 100) {
			hp += 20;
			if (hp > 100) {
				hp = 100;
			}
		}
		
		SimpleAudioEngine::getInstance()->playEffect("Radio/go.mp3");
		player->runAction(RepeatForever::create(RotateBy::create(0.5, 360)));
		player->runAction(Sequence::create(DelayTime::create(4),CallFunc::create(CC_CALLBACK_0(MainGame::overSup4,this)),NULL));
		
	}

}

void MainGame::updateSup2(float tm)
{
	auto & virusList = Manager::getInstance()->getVirus();
	sup2->setPosition(player->getPosition());
	//倒叙遍历
	for (int i = virusList.size() - 1; i >= 0; i--) {
		//病毒
		auto virus = virusList.at(i);
		if (virus->getHP() <= 0) {
			//若死亡则不检测
			continue;
		}
		auto rect = sup2->getBoundingBox();
		auto point =virus->getPosition();

		//判断是否碰撞
		if (rect.containsPoint(point)) {
			virus->setHP(virus->getHP() - 100);
			if (virus->getHP() <= 0) {
				addSupport(virus->getPosition());
				virus->virusDeath();
				scoreNow++;
				labelScore->setString(String::createWithFormat("Score: %d", scoreNow)->getCString());
			}
		}
	}
}

void MainGame::overSup2()
{
	speed = 3;
	this->unschedule(SEL_SCHEDULE(&MainGame::updateSup2));
	auto reAc = RemoveSelf::create();
	sup2->runAction(reAc);

}

void MainGame::updateSup3(float tm)
{
	auto & virusList = Manager::getInstance()->getVirus();

	//倒叙遍历
	for (int i = virusList.size() - 1; i >= 0; i--) {
		//病毒
		auto virus = virusList.at(i);
		if (virus->getHP() <= 0) {
			//若死亡则不检测
			continue;
		}

		Rect rect[4];
		auto point = virus->getPosition();
		for (int i = 0; i < 4;i++){
			rect[i] = sup3[i]->getBoundingBox();
		}
		//判断是否碰撞
		if (rect[0].containsPoint(point)|| rect[1].containsPoint(point)|| rect[2].containsPoint(point)|| rect[3].containsPoint(point)) {
			virus->setHP(virus->getHP() - 100);
			if (virus->getHP() <= 0) {
				addSupport(virus->getPosition());
				virus->virusDeath();
				scoreNow++;
				labelScore->setString(String::createWithFormat("Score: %d", scoreNow)->getCString());
			}
		}
	}
}

void MainGame::overSup3()
{
	this->unschedule(SEL_SCHEDULE(&MainGame::updateSup3));
}

void MainGame::overSup4()
{
	speed = 3;
	player->runAction(RepeatForever::create(RotateBy::create(2, 360)));
}

void MainGame::finalSkill()
{
	skill = Sprite::create("f1.png");
	skill->setScale(0.1);
	skill->setPosition(Vec2(player->getPositionX(), player->getPositionY() + 800));
	this->addChild(skill,10);

	auto text = Sprite::create("d1.png");
	text->setScale(0.1);
	text->setPosition(Vec2(100, -300));
	text->setOpacity(0);
	uiSprite->addChild(text,11);

	auto tac1 = ScaleTo::create(0.1, 1);
	text->runAction(Sequence::create(DelayTime::create(2.5), FadeIn::create(0.1),tac1, DelayTime::create(3), RemoveSelf::create(), NULL));

	this->schedule(SEL_SCHEDULE(&MainGame::finalSkillUpdate));
	auto ac1 = MoveTo::create(0.6, player->getPosition());
	auto ac2 = JumpTo::create(2, player->getPosition(), 30, 1);
	auto ac3 = ScaleTo::create(0.2, 1);
	skill->runAction(Sequence::create(ac1,ac2, ac3, DelayTime::create(3),CallFunc::create(CC_CALLBACK_0(MainGame::finalSkillOver,this)),RemoveSelf::create(), NULL));
	SimpleAudioEngine::getInstance()->playEffect("Radio/x.mp3");
}

void MainGame::finalSkillUpdate(float tm)
{
	auto & virusList = Manager::getInstance()->getVirus();
	//倒叙遍历
	for (int i = virusList.size() - 1; i >= 0; i--) {
		//病毒
		auto virus = virusList.at(i);
		if (virus->getHP() <= 0) {
			//若死亡则不检测
			continue;
		}
		auto rect = skill->getBoundingBox();
		auto point = virus->getPosition();

		//判断是否碰撞
		if (rect.containsPoint(point)) {
			virus->setHP(virus->getHP() - 300);
			if (virus->getHP() <= 0) {
				addSupport(virus->getPosition());
				virus->virusDeath();
				scoreNow++;
				labelScore->setString(String::createWithFormat("Score: %d", scoreNow)->getCString());
			}
		}
	}
}

void MainGame::finalSkillOver()
{
	this->unschedule(SEL_SCHEDULE(&MainGame::finalSkillUpdate));
}

void MainGame::isCrash(float tm)
{
	auto & virusList = Manager::getInstance()->getVirus();

	//倒叙遍历
	for (int i = virusList.size() - 1; i >= 0; i--) {
		//病毒
		auto virus = virusList.at(i);
		if (virus->getHP() <= 0) {
			//若死亡则不检测
			continue;
		}
		auto rect = player->getBoundingBox();
		auto point = virus->getPosition();

		//判断是否碰撞
		if (rect.containsPoint(point)) {
			//主角死亡
			hp-=20;
			virus->virusDeath();
			if (hp <= 0) {
				playerDeath();
			}
			
		}
	}

	for (int i = virusList.size() - 1; i >= 0; i--) {
		//病毒
		auto virus = virusList.at(i);
		if (virus->getHP() <= 0) {
			//若死亡则不检测
			continue;
		}

		auto rect = virus->getBoundingBox();
		if (level == 1) {
			//子节点坐标转化
			auto point = fight[0]->getParent()->convertToWorldSpace(fight[0]->getPosition())-this->getPosition();
			//判断是否碰撞
			if (rect.containsPoint(point)) {
				virus->setHP(virus->getHP() - damage);
				if (virus->getHP() <= 0) {
					addSupport(virus->getPosition());
					virus->virusDeath();
					scoreNow++;
					labelScore->setString(String::createWithFormat("Score: %d", scoreNow)->getCString());
				}
			}
		}
		else {
			//子节点坐标转化
			Point point0, point1, point2, point3;
			point0 = fight[0]->getParent()->convertToWorldSpace(fight[0]->getPosition()) - this->getPosition();
			point1 = fight[1]->getParent()->convertToWorldSpace(fight[1]->getPosition()) - this->getPosition();
			point2 = fight[2]->getParent()->convertToWorldSpace(fight[2]->getPosition()) - this->getPosition();
			point3 = fight[3]->getParent()->convertToWorldSpace(fight[3]->getPosition()) - this->getPosition();
			
			//判断是否碰撞
			if (rect.containsPoint(point0)|| rect.containsPoint(point1)|| rect.containsPoint(point2)|| rect.containsPoint(point3)) {
				log("Death");
				virus->setHP(virus->getHP()-damage);
				if (virus->getHP() <= 0) {
					addSupport(virus->getPosition());
					virus->virusDeath();
					scoreNow++;
					labelScore->setString(String::createWithFormat("Score: %d", scoreNow)->getCString());
				}
			}
		}
		
	}
	//判断player与support是否碰撞
	auto supportList= Manager::getInstance()->getSupport();
	//倒叙遍历
	for (int i = supportList.size() - 1; i >= 0; i--) {
		//
		auto support = supportList.at(i);

		auto rect = player->getBoundingBox();
		auto point = support->getPosition();

		//判断是否碰撞
		if (rect.containsPoint(point)) {
			supportMaking(support->getIndex());
			support->remove();
		}
	}
	//判断获取经验值
	auto exList = Manager::getInstance()->getEX();
	//倒叙遍历
	for (int i = exList.size() - 1; i >= 0; i--) {
		//
		auto ex = exList.at(i);

		auto rect = player->getBoundingBox();
		auto point = ex->getPosition();

		//判断是否碰撞
		if (rect.containsPoint(point)) {
			ex->removeEX();
			SimpleAudioEngine::getInstance()->playEffect("Radio/pick.mp3");
			exper++;
			power++;
			if (power >= 20) {
				isOK = true;
			}
			log("%d", exper);
			if (exper == 5) {
				level = 2;
				initFight();
			}
			else if (exper == 12) {
				level = 3;
				damage = 2;
				initFight();
			}
			else if(exper>=20){
				level = 4;
				damage = 3;
				initFight();
			}
			
		}
	}
}

void MainGame::setViewpointCenter(Vec2 pos)
{
	Size visiblesize = Director::getInstance()->getVisibleSize();
	//x的坐标最小不能小于屏幕宽度的一半否则左边就会出现黑边
	int x = MAX(pos.x, -640);
	//y的坐标最小不能小于屏幕宽度的一半否则下边就会出现黑边
	int y = MAX(pos.y, -360);
	////x最大不能大于地图宽度减去屏幕宽度的一半，否则右边会出现黑边
	x = MIN(x, 1920 );
	////y最大不能大于地图宽度减去屏幕宽度的一半，否则上边会出现黑边
	y = MIN(y, 1080);

	//屏幕中心点e
	Vec2 pointA = Vec2(visiblesize.width / 2, visiblesize.height / 2);
	//Vec2 point =pos;
	Vec2 pointB = Vec2(x, y);//将处理过的x，y作为b点的坐
	
	Vec2 offset = pointA - pointB;
	this->setPosition(offset);


	Vec2 offset2 = pointB - pointA+Vec2(0, visiblesize.height - 50);
	uiSprite->setPosition(offset2);

}
