#include "GameScene.h"
#include "TipWin.h"
#include "ShopWin.h"
#include "luopan.h"
#include "taskMgr.h"
#include "LoadScene.h"


USING_NS_CC;
GameScene* GameScene::m_GameMain=NULL;

Node* tt = NULL;
#define ROCKET_EXPLORE_DIS  200

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto Layer = GameScene::create();
	scene->addChild(Layer);
	return scene;
}

bool GameScene::init()
{
    m_rolltm=0;
    m_tipOpen = false;
	this->setKeyboardEnabled(true);
	goldTipTotal = 0;
	BUBBLE;
	if ( !Layer::init() )
    {
        return false;
    }
	G_MainGame = this;
	m_GameMain = this;
	m_Rollbg = NULL;
	m_UILayer = Layer::create();
	m_mapLayer = Layer::create();
	this->addChild(m_UILayer,UI_INDEX);
	this->addChild(m_mapLayer,MAP_INDEX);
	InitBackGroud();
	LoadPlayerInfo();
	LoadCannon();
	initFishLayer();
	this->schedule(schedule_selector(GameScene::update),1);
	this->schedule(schedule_selector(GameScene::updateGame), 0.01f);
	InitTask();
	InitProgress();
	InitCountDown();
	specialCanno = false;
    return true;
}


void GameScene::InitProgress()
{
	currentGoldGet = 0;
	flashingProgress = false;
	progressSprite = ProgressTimer::create(Sprite::create("images/Scene/GameScene/laser_progress_01.png"));
	progressSprite->setType(ProgressTimer::Type::BAR);
	progressSprite->setMidpoint(Vec2(0,0));
	progressSprite->setBarChangeRate(Vec2(1, 0));
	progressSprite->setPosition(270,-14);
	progressSprite->runAction(ProgressTo::create(0.1, 1));
	m_GameMain->m_bottom->addChild(progressSprite);
	char FramePng[50] = {0};
	cocos2d::Vector<cocos2d::SpriteFrame *> frameList;
	for(int i = 1; i <= 4; ++i)
	{
		sprintf(FramePng, "images/Scene/GameScene/laser_progress_%02d.png", i);
		auto f = SpriteFrame::create(FramePng, Rect(0,0,154,27));
		frameList.pushBack(f);
	}
	Animation* aa = Animation::createWithSpriteFrames(frameList,0.1f);
	aa->setDelayPerUnit(0.2f);
	aa->setRestoreOriginalFrame(true);
	flashProgress = Sprite::create("images/Scene/GameScene/laser_progress_01.png");
	flashProgress->runAction(RepeatForever::create(Animate::create(aa)));
	flashProgress->setOpacity(0);
	m_GameMain->m_bottom->addChild(flashProgress);
	flashProgress->setPosition(270,-14);
}



void GameScene::FlashProgress()
{
	//progressSprite->runAction(ProgressTo::create(0.1, 1));
	flashingProgress = true;
	flashProgress->setOpacity(255);
	m_pCannon->ChangeType(7);
}

void GameScene::SetProgress(float fpro, float tm)
{
	float pro = fpro;
	if (m_pCannon->getCanType() > 7)
	{
		pro = MIN(99.9, pro);
	}

	if(flashingProgress)
		return;
	flashProgress->setOpacity(0);
	progressSprite->stopAllActions();

	progressSprite->runAction(ProgressTo::create(tm, pro));
	if(pro >= 99.99)
		FlashProgress();
}



void GameScene::onEnter()
{
	Layer::onEnter();
	AudioEngine::stopAll();
	if(LoadScene::backOpen)
		MusicOn();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [this](cocos2d::Touch *touch,cocos2d::Event *unused_event){return this->onTouchBegan(touch, unused_event);};
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	BottomGold();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact){return this->onContactBegin(contact);};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	specialReady = false;
	TipWin::ShowTip(3);
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{

	return true;
}

void GameScene::LoadPlayerInfo()
{
	auto Head = new PlayerExp();
	Head->init(this);	
}


cocos2d::Sprite* GameScene::CreateLight()
{
	auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Lightning_launch001.png"));
	cocos2d::Vector<cocos2d::SpriteFrame*> array;
	char pngName[1024];
	for (int i = 1; i < 3; i++)
	{
		sprintf(pngName, "Lightning_launch%03d.png", i);
		SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
		if (tempFrame != NULL)
		{
			array.pushBack(tempFrame);
		}
	}

	Animation* animation = Animation::createWithSpriteFrames(array, 0.2f);
	animation->setRestoreOriginalFrame(false);
	Animate* animat = Animate::create(animation);
	CallFunc *call = CallFunc::create(std::bind(&CCNode::removeFromParent, sp));
	auto q = Sequence::create(animat, call ,NULL);
	sp->runAction(q);
	return sp;
}

void GameScene::LoadCannon()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannonFrame/cannon.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannonFrame/CannonEffectFrame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannonFrame/PropEffectFrame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/Coins/coins.plist");
   SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/Plist/taskfish/taskfish.plist");
	TextureCache::getInstance()->addImage("images/Bullets/bullet001.png");
	TextureCache::getInstance()->addImage("images/Bullets/bullet002.png");
	TextureCache::getInstance()->addImage("images/Bullets/bullet003.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/Plist/water.plist");
	
	m_pCannon = Cannon::createWithCannonType(2);
}

void GameScene::InitBackGroud()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite *bg = Sprite::create("images/FishBg/fishBg_02.png");
	bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	m_mapLayer->addChild(bg);
	auto Item3 = MenuItemImage::create("images/Scene/GameScene/btn_gift.png","images/Scene/GameScene/btn_gift.png",
		[&](Ref *sender) {
			this->MainMenuCallBack(2);
	});
	auto Item4 = MenuItemImage::create("images/Scene/GameScene/btn_shop.png","images/Scene/GameScene/btn_shop.png",
		[&](Ref *sender) {
			this->MainMenuCallBack(1);
	});
	auto bgshop = Sprite::create("images/Scene/GameScene/shopLight.png");
    m_UILayer->addChild(bgshop);
	FadeOut *out = FadeOut::create(1.0f);
	FadeIn *inAc = FadeIn::create(1.0f);
	auto seq = Sequence::create(out,inAc,nullptr);
	bgshop->runAction(RepeatForever::create(seq));
	auto ICONmenus = Menu::create(Item3,Item4,NULL);
	m_UILayer->addChild(ICONmenus);
	Item4->setPosition(30,10);
	Item3->setPosition(-80,10);
    
    bgshop->setPosition(Vec2(visibleSize.width*0.93 + origin.x, visibleSize.height-15));
    
    Vec2 pos = Vec2(visibleSize.width*0.9 + origin.x, visibleSize.height-20);
	ICONmenus->setPosition(pos);
	
	

	m_bottom = Layer::create();
	Sprite *pBottomBar=Sprite::create("images/Scene/GameScene/batteryBg.png");
	m_bottom->addChild(pBottomBar);
	m_bottom->setPosition(Vec2(visibleSize.width/2 + origin.x, 30));
    m_UILayer->addChild(m_bottom);
	m_bottom->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height * 0.05 + origin.y));
	auto userItem = MenuItemImage::create("images/Scene/GameScene/btn_sub_up.png","images/Scene/GameScene/btn_sub_down.png",
		[&](Ref *sender) {
			this->ChangeCanno(1);
	});
	auto Item2 = MenuItemImage::create("images/Scene/GameScene/btn_add_up.png","images/Scene/GameScene/btn_add_down.png",
		[&](Ref *sender) {
			this->ChangeCanno(2);
	});	
	userItem->setPosition(0,0);
	Item2->setPosition(220,0);
	auto m_menus = Menu::create(userItem,Item2,NULL);
	m_menus->setPosition(-110,0);
	m_bottom->addChild(m_menus);
	auto *GoldFlag = Sprite::create("images/Scene/GameScene/batteryCoin.png");
	m_bottom->addChild(GoldFlag);
	GoldFlag->setPosition(-(pBottomBar->getContentSize().width * 0.5f),0);

	m_oneCan = PropButton::CreateButtonWidthPNG("images/Scene/GameScene/prop008.png",1);
	m_UILayer->addChild(m_oneCan);
	m_oneCan->setTag(1);
	m_oneCan->setPosition(Vec2(visibleSize.width/2 + origin.x-100, visibleSize.height-45));
	m_secCan = PropButton::CreateButtonWidthPNG("images/Scene/GameScene/prop007.png",2);
	m_UILayer->addChild(m_secCan);
	m_secCan->setTag(2);
	m_secCan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height-45));
	m_thrCan = PropButton::CreateButtonWidthPNG("images/Scene/GameScene/prop006.png",3);
	m_UILayer->addChild(m_thrCan);
	m_thrCan->setPosition(Vec2(visibleSize.width/2 + origin.x+100, visibleSize.height-45));
	m_thrCan->setTag(3);

	ShowMenu();
    RocallMsg();
}

void GameScene::ShowTask()
{
	
}

void GameScene::ChangeCanno(int tag)
{
	if(tag == 2)
	{
		if(m_pCannon->getCanType() == 6)
		{
			m_pCannon->ChangeType(1);
		}
		else
		{
			m_pCannon->ChangeType(m_pCannon->getCanType()+1);
		}
	}
	else
	{
		if(m_pCannon->getCanType() == 1)
		{
			m_pCannon->ChangeType(6);
		}
		else
		{
			m_pCannon->ChangeType(m_pCannon->getCanType()-1);
		}
	}
	if(m_pCannon->getCanType() < 7 && specialCanno)
	{
		specialCanno = false;
	}

}

void GameScene::initFishLayer()
{
	srand((unsigned int)time(NULL));
    m_fishLayer = FishPlayer::createFishPlayer();
    this->addChild(m_fishLayer,FISH_INDEX);
    m_fishLayer->start();
}


float offsetx,offsety;
void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		offsetx --;
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		offsetx ++;
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		offsety ++;
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		offsety --;
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		offsetx -= 10;
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		offsetx += 10;
	else if (keyCode == EventKeyboard::KeyCode::KEY_W)
		offsety += 10;
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		offsety -= 10;
	else if (keyCode == EventKeyboard::KeyCode::KEY_8)
	{
		ShowRmbWindow();
	}
}

void GameScene::update(float dt)
{
	m_fishLayer->FishTick(dt);
	m_oneCan->Tick();
	m_secCan->Tick();
	m_thrCan->Tick();
    taskMgr::getInstance()->Tick();
    if(m_rolltm == 0)
    {
        m_rolltm = 30;
        RocallMsg();
    }
    else
    {
        m_rolltm--;
    }
    CountDownReward();
}

void GameScene::setCannon(int stype)
{
	if(m_pCannon)
	{
		m_pCannon->ChangeType(stype);
	}
}

void GameScene::fire(float)
{
	if (m_pCannon->getCanType() >= 7)
	{
		this->unschedule(schedule_selector(GameScene::fire));
		return;
	}
	m_pCannon->fire();
	//if(CannoState >= 3)
	//{
	//	CannoState = 0;
	//	this->unschedule(schedule_selector(GameScene::fire));
	//}
}

bool GameScene::CheckFire()
{
	if(m_pCannon->getCanType() == 7)
	{
		return m_oneCan->GetPropNum() > 0;
	}
	else if(m_pCannon->getCanType() == 8)
	{
		return m_thrCan->GetPropNum() > 0;
	}
	else if(m_pCannon->getCanType() == 9)
	{
		return m_secCan->GetPropNum() > 0;
	}
	return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto p = this->convertToWorldSpace(touch->getLocation());
	if (/*CheckFire() &&*/!specialCanno && !specialReady)
	{
		if (m_pCannon->getCanType() == 7 || m_pCannon->getCanType() == 8 || m_pCannon->getCanType() == 9)
		{
			
			m_pCannon->RotatePoint(p);
			if (m_pCannon->getRotation() > 75 || m_pCannon->getRotation() < -75)
			{
				PlayMusic("music/eft_firefail.mp3");
				return true;
			}
			m_pCannon->fire();
			specialCanno = true;
		}
		else
		{
			m_pCannon->RotatePoint(p);
			m_pCannon->fire();
			this->schedule(schedule_selector(GameScene::fire), Bomb::G_CanInfo[m_pCannon->getCanType()-1].speed);
		}
		return true;
	}
	else
	{
		return false;
	}
}

void GameScene::MusicOn()
{
	backMusic = AudioEngine::play2d("music/bg_hokkaido.ogg", true);
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (m_pCannon->getCanType() >= 7)
		return;
	m_pCannon->RotatePoint(this->convertToWorldSpace(touch->getLocation()));
}


void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	/*static DrawNode* ns = DrawNode::create();
	static DrawNode* ne = DrawNode::create();
	if(f == 3)
	{
	ns->drawCircle(s, 5, 360, 10, true, Color4F(1,0,0,1));
	ne->drawCircle(s, 5, 360, 10, true, Color4F(1,0,0,1));
	this->m_GameMain->addChild(ns, 1000);
	this->m_GameMain->addChild(ne, 1000);
	}

	f %= 2;
	if(f == 1)
	{
	s = this->convertToWorldSpace(touch->getLocation());
	}
	else
	{
	e = this->convertToWorldSpace(touch->getLocation());
	}
	ns->setPosition(s);
	ne->setPosition(e);
	if(f == 0)
	{
	Vec2 dir = e - s;
	auto l = CreateLight();
	float len = dir.length();
	l->setScaleY(len / 280);
	dir.normalize();
	this->m_GameMain->addChild(l, 1000);
	l->setPosition(s + dir * (len / 2));
	Vec2 t(0,1);
	float degree = acosf(t.dot(dir));
	l->setRotation(degree / M_PI * 180 * (dir.x < 0?-1:1));
	}
	f++;*/

	if(!specialCanno)
	{
		this->unschedule(schedule_selector(GameScene::fire));
	}
	CCLOG("endgame");
}
Rect GameScene::cacleRect(Rect rc,float xr,float yr)
{
	float w = rc.size.width * xr;
	float h = rc.size.height * yr;
	Vec2 pt=Vec2(rc.origin.x + rc.size.width * (1.0f - xr)/2,rc.origin.y + rc.size.height * (1.0f - yr)/2);
	return Rect(pt.x,pt.y,w,h);
}

void GameScene::Explord(Bomb* bomb)
{
	bool caught = false;
	Bomb *curBomb = NULL;
	Vec2 temp = bomb->getParent()->convertToWorldSpace(bomb->getPos());
	for (auto item : this->m_pFishes)
	{
		caught = false;
		int fishState = item.second->getFishState();

		if (fishState == 1)
		{
			Vec2 fishPos = item.second->convertToWorldSpace(item.second->getFishSprite()->getPosition());
			if ((temp - fishPos).lengthSquared() < ROCKET_EXPLORE_DIS * ROCKET_EXPLORE_DIS)
			{
				item.second->showCaught(100000);
			}
		}
	}

	bomb->explode();
	char pngName[1024];
	Vector<SpriteFrame *> veccatch;
	for (int i = 1; i < 8; i++)
	{
		sprintf(pngName, "Torpedo_bomb%03d.png", i);
		SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
		if (tempFrame != NULL)
		{
			veccatch.pushBack(tempFrame);       
		}
	}
	SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Torpedo_bomb001.png");

	auto bb = Sprite::createWithSpriteFrame(Frame);

	if (veccatch.size() > 0)
	{
		Animation* animation = Animation::createWithSpriteFrames(veccatch, 0.3f);
		animation->setRestoreOriginalFrame(true);
		Animate* animat = Animate::create(animation);
		CallFunc *call = CallFunc::create(std::bind(&Node::removeFromParent, bb));
		bb->runAction(Sequence::create(animat, call, NULL));
		this->addChild(bb, 100);
		bb->setPosition(temp);
	}
}

void GameScene::BombFishExplored(cocos2d::Vec2 pos)
{
	for (auto item : this->m_pFishes)
	{
		int fishState = item.second->getFishState();

		if (fishState == 1)
		{
			Vec2 fishPos = item.second->convertToWorldSpace(item.second->getFishSprite()->getPosition());
			if ((pos - fishPos).lengthSquared() < 130 * 130)
			{
				item.second->showCaught(100000);
			}
		}
	}

	char pngName[1024];
	Vector<SpriteFrame *> veccatch;
	for (int i = 1; i < 8; i++)
	{
		sprintf(pngName, "Torpedo_bomb%03d.png", i);
		SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
		if (tempFrame != NULL)
		{
			veccatch.pushBack(tempFrame);
		}
	}
	SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Torpedo_bomb001.png");

	auto bb = Sprite::createWithSpriteFrame(Frame);

	if (veccatch.size() > 0)
	{
		Animation* animation = Animation::createWithSpriteFrames(veccatch, 0.3f);
		animation->setRestoreOriginalFrame(true);
		Animate* animat = Animate::create(animation);
		CallFunc *call = CallFunc::create(std::bind(&Node::removeFromParent, bb));
		bb->runAction(Sequence::create(animat, call, NULL));
		this->addChild(bb, 100);
		bb->setPosition(pos);
	}

}

void GameScene::ExplordLight(Fish* fish)
{
	Fish* curFish = fish;
	fish->showCaught(10000);
	{
		Vec2 pf1 = this->convertToWorldSpace(fish->getFishSprite()->getPosition());		
		char FramePng[50] = {0};
		cocos2d::Vector<cocos2d::SpriteFrame *> caughtVec;
		for(int i = 1;i<= 4;i++)
		{
			sprintf(FramePng,"Lightning_catch%03d.png",i);		 
			SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(FramePng);
			caughtVec.pushBack(tempFrame);
		}
		auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Lightning_catch001.png"));
		Animation* animation = Animation::createWithSpriteFrames(caughtVec,0.3f);
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		Animate* animat = Animate::create(animation);
		sp->runAction(RepeatForever::create(animat));
		sp->runAction(Sequence::create(MoveBy::create(1, Vec3(0,0,1)), CallFunc::create([sp]{sp->removeFromParent();}), NULL));
		sp->setPosition(pf1);
		this->addChild(sp, 1000);
	}
	for(auto f: m_pFishes)
	{
		if(f.second->getFishIndex() == fish->getFishIndex() && f.second != curFish && f.second->getFishState() == 1 )
		{
			Vec2 pf1 = this->convertToWorldSpace(curFish->getFishSprite()->getPosition());			
			Vec2 pf2 = this->convertToWorldSpace(f.second->getFishSprite()->getPosition());
			
			if(pf2.x < 0 || pf2.y < 0 || pf2.x > 960 || pf2.y > 640)
				continue;

			Vec2 dir = pf2 - pf1;
			auto l = CreateLight();
			this->m_GameMain->addChild(l, 1000);
			float len = dir.length();
			l->setScaleY(len / 280);
			dir.normalize();
			l->setPosition(pf1 + dir * (len / 2));
			Vec2 t(0,1);
			float degree = acosf(t.dot(dir));
			l->setRotation(degree / M_PI * 180 * (dir.x < 0?-1:1));
			curFish = f.second;
			f.second->showCaught(10000);

			char FramePng[50] = {0};
			cocos2d::Vector<cocos2d::SpriteFrame *> caughtVec;
			for(int i = 1;i<= 4;i++)
			{
				sprintf(FramePng,"Lightning_catch%03d.png",i);		 
				SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(FramePng);
				caughtVec.pushBack(tempFrame);
			}
			auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Lightning_catch001.png"));
			Animation* animation = Animation::createWithSpriteFrames(caughtVec,0.3f);
			animation->setDelayPerUnit(0.2f);
			animation->setRestoreOriginalFrame(true);
			Animate* animat = Animate::create(animation);
			sp->runAction(RepeatForever::create(animat));
			sp->runAction(Sequence::create(MoveBy::create(1, Vec3(0,0,1)), CallFunc::create([sp]{sp->removeFromParent();}), NULL));
			sp->setPosition(pf2);
			this->addChild(sp, 1000);
			//Lightning_catch001
		}
	}
}


void GameScene::LaserExplord(Bomb* bomb)
{
	float degree = bomb->getRotation();
	Vec2 dir(sin(degree / 180 * M_PI), cos(degree/ 180 * M_PI));

	Vec2 bombPos = this->convertToWorldSpace(bomb->getPosition());

	Vec2 s(bombPos + dir * 320);
	Vec2 e(bombPos - dir * 320);
	//Vec3 d(0,0,1);
	//Vec3 n(dir.x, dir.y, 0);
	//d.cross(n);
	//dir.x = d.x;
	//dir.y = d.y;
	//dir.normalize();
	dir = Vec2(1,0);

	for (auto item : this->m_pFishes)
	{
		Vec2 fishPos = this->convertToWorldSpace(item.second->getFishSprite()->getPosition());
		if(fishPos.x < 0 || fishPos. x > 960 || fishPos.y < 0 || fishPos.y > 640)
			continue;

		if(item.second->getHp() <= 0)
			continue;

		auto bx = item.second->getFishSprite()->getBoundingBox();

		Vec2 expandPos = fishPos + dir * 100;

		Vec2 crossPos = Vec2::getIntersectPoint(s, e, fishPos, expandPos);
		Vec2 a(fishPos - Vec2(bx.size.width * 0.5, 0));
		Vec2 b(fishPos + Vec2(bx.size.width * 0.5, 0));
		// œ¬√Êƒ«∏ˆ900 = 30 °¡ 30£¨æÕ «æ‡¿Î30
		if(((a - crossPos).lengthSquared() < 900 || ((b - crossPos).lengthSquared() < 900
			|| (a - crossPos).dot(b - crossPos) < 0)))
		{
			item.second->showCaught(10000);
		}
		/*{
			{
				auto dn = DrawNode::create();
				dn->drawPoint(fishPos - Vec2(bx.size.width * 0.5, 0), 10, Color4F(1,0,0,1));
				G_MainGame->addChild(dn, 10000);
				dn->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0,0)), CallFunc::create([dn]{dn->removeFromParent();}), NULL));
			}
			{
				auto dn = DrawNode::create();
				dn->drawPoint(crossPos, 10, Color4F(1,0,1,1));
				G_MainGame->addChild(dn, 10000);
				dn->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0,0)), CallFunc::create([dn]{dn->removeFromParent();}), NULL));
			}

			{
				auto dn = DrawNode::create();
				dn->drawPoint(fishPos + Vec2(bx.size.width * 0.5, 0), 10, Color4F(1,0,0,1));
				G_MainGame->addChild(dn,10000);
				dn->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0,0)), CallFunc::create([dn]{dn->removeFromParent();}), NULL));
			}
		}*/
		continue;
	}
}


long GameScene::GetTimeNow()
{
	struct timeval tm;
	gettimeofday(&tm, NULL);
	return tm.tv_sec;
}

void GameScene::ShowGoldTip(int gold)
{
	auto sp = Sprite::create("images/Scene/TipScene/levelUp/levelup_bg.png");
	ParticleSystemQuad*    _leftemitter;
	_leftemitter = ParticleSystemQuad::create("particles/coin_left.plist");
	_leftemitter->retain();
	sp->addChild(_leftemitter, -1);
	//_leftemitter->setPosition(-50, 0);
	ParticleSystemQuad*    _rightemitter;
	_rightemitter = ParticleSystemQuad::create("particles/coin_right.plist");
	_rightemitter->retain();
	sp->addChild(_rightemitter, -1);
	//_leftemitter->setPosition(-50, 0);
	ParticleSystemQuad*    _midemitter;
	_midemitter = ParticleSystemQuad::create("particles/coin_mid.plist");
	_midemitter->retain();
	sp->addChild(_midemitter, -1);
	//_midemitter->setPosition(, 0);
	GameScene::m_GameMain->addChild(sp, 1000);
	sp->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	auto titleSp = Sprite::create("images/Scene/TipScene/itemGet/get_title.png");
	sp->addChild(titleSp, 100);
	titleSp->setPosition(231, 269);

	auto bgSp = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
	bgSp->setPosition(219, 144);
	sp->addChild(bgSp, -1);
	bgSp->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1, 1.5), ScaleTo::create(1, 1), NULL)));

	auto lGold = LabelAtlas::create(StringUtils::format("%d", gold), "images/Number/shop_coin_num.png", 22, 28, '0');
	sp->addChild(lGold, 101);
	lGold->setPosition(183 + (gold > 10000?-14:0), 77);
	CallFunc *call = CallFunc::create([=]{sp->removeFromParent(); });
	auto action = ScaleTo::create(0.2, 1.3, 1.3, 1);
	auto raction = ScaleTo::create(0.1, 1, 1, 1);
	auto ra = ScaleTo::create(0.2, 0.3, 0.3, 1);
	auto sleepAction = ScaleTo::create(4, 1.001, 1.001, 10);
	auto q = Sequence::create(action, raction, sleepAction, ra, call, NULL);
	sp->runAction(q);
}



void GameScene::updateGame(float dt)
{
#if 0
	if (tt)
	{
		tt->setPosition(offsetx, offsety);
	}
#endif
	bool caught = false;
	Bomb *curBomb = NULL;
	for(Bomb *buttle : this->m_pBullets)
	{
		Vec2 bulletPos = buttle->getParent()->convertToWorldSpace(buttle->getPos());
		//bulletPos = G_MainGame->m_fishLayer->convertToWorldSpace(bulletPos);
		if (buttle->getCaught() || buttle->getType() == 9)
		{
			continue;
		}
		   
		if(buttle->getType() == 7)
		{
			LaserExplord(buttle);
			continue;
		}

		for (auto item : this->m_pFishes)
		{
			caught = false;
			int fishState = item.second->getFishState();
			
			Vec2 fishPos = this->convertToWorldSpace(item.second->getFishSprite()->getPosition());
			if(fishPos.x < 0 || fishPos.x > 960 || fishPos.y < 0 || fishPos.y > 640)
				continue;

			if (fishState == 1)
			{
				Rect hitRec = item.second->getFishSprite()->boundingBox();
				if(hitRec.containsPoint(bulletPos))
				{
					if(buttle->getType() == 8)
					{
						PlayMusic("music/lightningFire.mp3");
						buttle->LightDis();
						ExplordLight(item.second);
						return;
					}
					caught = true;
					item.second->showCaught(buttle->getHurt());
					curBomb = buttle;
				}
			}
			else
			{
				continue;
			}
			if(caught && curBomb != NULL)
			{
				curBomb->explode();
			}
			
		}
	}
	
}

void GameScene::BottomGold()
{
	m_bottomSprie = MenuItemImage::create("images/Scene/GameScene/btn_coin_up.png","images/Scene/GameScene/btn_coin_down.png",[&](Ref* Sender){
		ShopWin::ShowShop();
	});
    m_bottomBuy = MenuItemImage::create("images/Scene/GameScene/buyCoinButton_Blink.png","",[&](Ref* Sender){
        //buy sdk
    });
	auto menu = Menu::create(m_bottomSprie,m_bottomBuy,nullptr);
	int num = Player::getInstance()->getCurGold();
	m_bottomgold = LabelAtlas::create(StringUtils::format("%d",num),"images/Number/prop_num.png",16,21,'0');
	this->m_bottom->addChild(menu);
	menu->setPosition(-261,-12);
	this->m_bottom->addChild(m_bottomgold,2);
	m_bottomgold->setPosition(-300,-30);
    m_bottomBuy->setVisible(false);
    m_btnbuy = Label::createWithSystemFont("2元3800金币", "Arial", 19);
    this->m_bottom->addChild(m_btnbuy,2);
    
    m_btnbuy->setColor(Color3B(87,88,100));
    m_btnbuy->setPosition(-256,-15);
    
    m_btnbuy->setVisible(false);
    m_ShowBuyMoney = false;
}


void GameScene::ShowBuyMoney(bool IsShow)
{
    if(IsShow)
    {
        m_ShowBuyMoney = true;
        m_bottomBuy->setOpacity(255);
        m_btnbuy->setVisible(true);
        m_bottomgold->setVisible(false);
        auto blink = Blink::create(1.f, 2);
        m_bottomBuy->runAction(RepeatForever::create(blink));
    }
    else
    {
        m_ShowBuyMoney = false;
        m_bottomBuy->setOpacity(0);
        m_btnbuy->setVisible(false);
        m_bottomgold->setVisible(true);
    }
}

void GameScene::MainMenuCallBack(int Flag)
{
	switch (Flag)
	{
	case 1:
		ShopWin::ShowShop();
		break;
	case 2:
		BUBBLE;
        //CLuoPan::ShowLuoPan();
		TipWin::ShowTip(3);
		break;
	default:
		break;
	}
}

void GameScene::InitTask()
{
    taskMgr::getInstance();
}

void GameScene::rotMenu(int sFlag)
{
	if(sFlag == 1)
	{
		bool f = settingMenu->getRotation() <= 0;
		settingMenu->runAction(RotateBy::create(0.3, f?180:-180));
		BackMusicMenu->runAction(MoveBy::create(0.3, f ? Vec2(80,0) : Vec2(-80,0)));
		DuangMusicMenu->runAction(MoveBy::create(0.3, f ? Vec2(80, 0) : Vec2(-80, 0)));
		homeMenu->runAction(MoveBy::create(0.3, f ? Vec2(80, 0) : Vec2(-80, 0)));
	}
	else
	{
		auto Sence = LoadScene::createLoadScene();
		Director::getInstance()->replaceScene(Sence);
	}
}

void GameScene::switchState(cocos2d::Sprite* sp, int flag)
{
	sp->setOpacity(sp->getOpacity() == 255 ? 0 : 255);
	if (sp->getOpacity() == 0)
	{
		if (flag == 1)
		{
			MusicOn();
			LoadScene::backOpen = true;
		}
		else
			LoadScene::duangOpen = true;
	}
	else
	{
		if (flag == 1)
		{
			AudioEngine::stop(backMusic);
			LoadScene::backOpen = false;
		}
		else
			LoadScene::duangOpen = false;
	}
}

void GameScene::ShowMenu()
{
	settingMenu = MenuItemImage::create("images/Scene/SettingScene/btn_setting.png", "images/Scene/SettingScene/btn_setting.png",
		[&](Ref *sender) {
		rotMenu(1);
	});
	BackMusicMenu = MenuItemImage::create("images/Scene/SettingScene/btn_bgmswitch.png", "images/Scene/SettingScene/btn_bgmswitch.png",
		[&](Ref *sender) {
		switchState(backDis,1);
	});
	DuangMusicMenu = MenuItemImage::create("images/Scene/SettingScene/btn_eftswitch.png", "images/Scene/SettingScene/btn_eftswitch.png",
		[&](Ref *sender) {
		switchState(duangDis, 2);
	});
	homeMenu = MenuItemImage::create("images/Scene/SettingScene/btn_home.png", "images/Scene/SettingScene/btn_home.png",
		[&](Ref *sender) {
			Scene *scene = LoadScene::createLoadScene();
			AudioEngine::stopAll();
			Director::getInstance()->replaceScene(scene);
            Player::getInstance()->m_callBack=nullptr;
            Player::getInstance()->setLoginGet(false);
            G_MainGame = nullptr;
            m_GameMain = nullptr;
	});

	duangDis = Sprite::create("images/Scene/SettingScene/cross.png");
	backDis = Sprite::create("images/Scene/SettingScene/cross.png");

	//settingMenu->setPosition(0, 0);
	/*Item2->setPosition(220, 0);*/
	auto menus = Menu::create(settingMenu, BackMusicMenu, DuangMusicMenu, homeMenu, NULL);
	this->addChild(menus,200);
	menus->setPosition(50, 80);
	BackMusicMenu->setPosition(-80, 200);
	BackMusicMenu->addChild(backDis);
	DuangMusicMenu->setPosition(-80, 140);
	DuangMusicMenu->addChild(duangDis);
	duangDis->setPosition(30, 30);
	duangDis->setOpacity(LoadScene::duangOpen?0:255);
	backDis->setPosition(30, 30);
	backDis->setOpacity(LoadScene::backOpen?0:255);
	homeMenu->setPosition(-80, 80);
}


void ShowWater(Vec2 pos)
{
	char pngName[1024];
	sprintf(pngName, "water%03d.png", 1);
	SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);

	auto water = Sprite::createWithSpriteFrame(Frame);
	GameScene::m_GameMain->addChild(water, 50);
	cocos2d::Vector<cocos2d::SpriteFrame*> array;
	for (int i = 1; i < 3; i++)
	{
		sprintf(pngName, "water%03d.png", i);
		SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
		if (tempFrame != NULL)
		{
			array.pushBack(tempFrame);
		}
	}

	Animation* animation = Animation::createWithSpriteFrames(array, 0.2f);
	animation->setRestoreOriginalFrame(false);
	Animate* animat = Animate::create(animation);
	CallFunc *call = CallFunc::create(std::bind(&CCNode::removeFromParent, water));
	auto q = Sequence::create(animat, call, NULL);
	water->runAction(q);
	water->setPosition(pos);
}

void GameScene::RocallMsg()
{
    if(m_Rollbg != nullptr)
    {
        m_Rollbg->setVisible(true);
        if(rand()%2 == 0)
        {
            m_scrotext->setString("按住屏幕可以连续发射炮弹");
        }
        else
        {
            m_scrotext->setString("分值越高的炮，越容易捕获");
        }
        this->schedule(schedule_selector(GameScene::RollText),0.05);
    }
    else
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        m_scrotext = Label::createWithSystemFont("按住屏幕可以连续发射炮弹","Arial",22);
        m_scrotext->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        
        
        auto pMask = Sprite::create("images/Scene/GameScene/rollBg.png");
        m_Rollbg = Sprite::createWithTexture(pMask->getTexture());
        m_UILayer->addChild(m_Rollbg);
        m_Rollbg->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
        auto clipper=ClippingNode::create();
        clipper->setInverted(false);
        clipper->setStencil(pMask);
        clipper->setAlphaThreshold(0.05f);
        clipper->setAnchorPoint(Vec2(0.5f,0.5f));
        clipper->addChild(m_scrotext);
        
        this->schedule(schedule_selector(GameScene::RollText),0.05);
        
        m_UILayer->addChild(clipper);
        clipper->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
        m_scrotext->setPositionX(280);
    }
    
    
}

void GameScene::InitCountDown()
{
	CountNode = Node::create();
	auto bg = Sprite::create("images/Scene/GameScene/bottom_timeDown.png");
	auto CountDw = Sprite::create("images/Scene/GameScene/bottom_clock.png");
	m_countdown = LabelAtlas::create("0", "images/Number/num_gold.png", 14, 22, '0');
	bg->addChild(CountDw);
	bg->addChild(m_countdown);
	bg->setName("CountDown");
	CountDw->setPosition(20, 15);
	m_countdown->setPosition(Vec2(40, 5));
	bg->setPosition(-250, 20);
	CountNode->addChild(bg);
	m_bottom->addChild(CountNode, 100);
	CountNode->setPosition(-6, 4);
	RMBTipsNode = Node::create();
	auto Tips = Sprite::create("images/Scene/GameScene/dialogBg.png");
    auto lab = Label::createWithSystemFont("点击兑换金币","Arial", 18);
	Tips->setFlipX(true);
	RMBTipsNode->addChild(Tips);
    RMBTipsNode->addChild(lab);
    lab->setPosition(0,10);
    lab->setColor(Color3B(253,248,170));
	this->m_UILayer->addChild(RMBTipsNode);
	RMBTipsNode->setPosition(174, 120);
	RMBTipsNode->setVisible(false);
}

void GameScene::ShowRmbWindow()
{
	if (!m_tipOpen)
	{
		m_tipOpen = true;
		TipWin::ShowTip(3,m_tipOpen);
	}
}

void GameScene::CheckCountNode()
{
	if (CountNode)
		CountNode->setVisible(Player::getInstance()->getCurGold() < 1000);
	static bool bFirstOpenGame = true;
	if (RMBTipsNode)
	{
		if (Player::getInstance()->getCurGold() < 500)
		{
			if (bFirstOpenGame)
			{
				RMBTipsNode->setVisible(true);
				RMBTipsNode->runAction(Sequence::create(MoveBy::create(5, Vec2(0, 0)), CallFunc::create([=]{
					RMBTipsNode->setVisible(false);
					bFirstOpenGame = false; }), NULL));
			}
		}
		else
		{
			RMBTipsNode->setVisible(false);
		}

	}
}

void GameScene::RollText(float dt)
{
    float x = m_scrotext->getPositionX();
    if(x < -500)
    {
        this->unschedule(schedule_selector(GameScene::RollText));
        m_Rollbg->setVisible(false);
        m_scrotext->setPositionX(280);
    }
    else
    {
        m_scrotext->setPositionX(m_scrotext->getPositionX()-4);
    }
}

void GameScene::CountDownReward()
{
    static int CountDown=0;
	CheckCountNode();
    if(CountDown == 0 && Player::getInstance()->getCurGold() < 1000)
    {
        CountDown = 60;
        
     }
    if(CountDown != 0)
    {
        CountDown--;
        if(CountDown == 0)
        {
            Player::getInstance()->AddGold(100);
			auto goldNode = Node::create();
			auto lGold = LabelAtlas::create(StringUtils::format("%d", 100), "images/Number/showup_gold.png", 36, 47, '0');
			auto plusSp = Sprite::create("images/Scene/GameScene/+.png");
			goldNode->addChild(lGold);
			goldNode->addChild(plusSp);
			this->m_GameMain->addChild(goldNode, 1000);
			goldNode->setScale(0.8);
			goldNode->setPosition(228, 2);
			plusSp->setPosition(-17, 20);
			goldNode->runAction(Sequence::create(MoveBy::create(1, Vec3(0, 10, 0)), CallFunc::create([=]{
				goldNode->removeFromParent();}), NULL));
			goldNode->runAction(FadeOut::create(1));
        }
    }
	m_countdown->setString(StringUtils::format("%d", CountDown));
}
