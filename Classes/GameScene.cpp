#include "GameScene.h"
#include "PropButton.h"
#include "TipWin.h"


USING_NS_CC;
GameScene* GameScene::m_GameMain=NULL;
bool GameScene::duangOpen = true;
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	m_GameMain = this;
    InitBackGroud();
    LoadPlayerInfo();
	LoadCannon();
    initFishLayer();
	this->schedule(schedule_selector(GameScene::update),1);
	this->schedule(schedule_selector(GameScene::updateGame), 0.05f);
    return true;
}

void GameScene::onEnter()
{
	MusicOn();
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::LoadPlayerInfo()
{
	auto Head = new PlayerExp();
	Head->init(this);	
}

void GameScene::LoadCannon()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannonFrame/cannon.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannonFrame/CannonEffectFrame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannonFrame/PropEffectFrame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/Coins/coins.plist");
	TextureCache::getInstance()->addImage("images/Bullets/bullet001.png");
	TextureCache::getInstance()->addImage("images/Bullets/bullet002.png");
	TextureCache::getInstance()->addImage("images/Bullets/bullet003.png");
	
	m_pCannon = Cannon::createWithCannonType(1,this);	
}

void GameScene::InitBackGroud()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto layerMap = Layer::create();
	auto Item3 = MenuItemImage::create("images/Scene/GameScene/btn_gift.png","images/Scene/GameScene/btn_gift.png",
		[&](Object *sender) {
			this->ChangeCanno(2);
	});
	auto ICONmenus = Menu::create(Item3,NULL);
	layerMap->addChild(ICONmenus,1);
	ICONmenus->setPosition(Vec2(visibleSize.width * 0.9f + origin.x, visibleSize.height* 0.9f + origin.y));
	Sprite *bg = Sprite::create("images/FishBg/fishBg_02.png");
	bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	layerMap->addChild(bg,0);
	
	this->addChild(layerMap,0);


	m_bottom = Layer::create();
	Sprite *pBottomBar=Sprite::create("images/Scene/GameScene/batteryBg.png");
	m_bottom->addChild(pBottomBar);
	m_bottom->setPosition(Vec2(visibleSize.width/2 + origin.x, 30));
    this->addChild(m_bottom,2);
	m_bottom->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height * 0.05 + origin.y));
	auto userItem = MenuItemImage::create("images/Scene/GameScene/btn_sub_up.png","images/Scene/GameScene/btn_sub_down.png",
		[&](Object *sender) {	
			this->ChangeCanno(1);
	});
	auto Item2 = MenuItemImage::create("images/Scene/GameScene/btn_add_up.png","images/Scene/GameScene/btn_add_down.png",
		[&](Object *sender) {
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

	PropButton *btnpro1 = PropButton::CreateButtonWidthPNG("images/Scene/LotteryScene/item/lottery_item_012.png",1);
	this->addChild(btnpro1,3);
	btnpro1->setTag(1);
	btnpro1->setPosition(Vec2(visibleSize.width/2 + origin.x-100, visibleSize.height * 0.9f));
	PropButton *btnpro2 = PropButton::CreateButtonWidthPNG("images/Scene/LotteryScene/item/lottery_item_013.png",1);
	this->addChild(btnpro2,3);
	btnpro2->setTag(2);
	btnpro2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height * 0.9f));
	PropButton *btnpro3 = PropButton::CreateButtonWidthPNG("images/Scene/LotteryScene/item/lottery_item_014.png",1);
	this->addChild(btnpro3,3);
	btnpro3->setPosition(Vec2(visibleSize.width/2 + origin.x+100, visibleSize.height * 0.9f));
	btnpro3->setTag(3);
}

void GameScene::ChangeCanno(int tag)
{
	if(tag == 1 && m_pCannon->getCanType() > 1)
	{
		m_pCannon->ChangeType(m_pCannon->getCanType()-1);
	}
	else if(tag == 2 && m_pCannon->getCanType() <9)
	{
		m_pCannon->ChangeType(m_pCannon->getCanType()+1);
	}
}

void GameScene::initFishLayer()
{
	srand((unsigned int)time(NULL));
    m_FishPlayer = FishPlayer::createFishPlayer(this);
    this->addChild(m_FishPlayer,1);
    m_FishPlayer->start();
}

void GameScene::update(float dt)
{
	m_FishPlayer->FishTick(dt);
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
	m_pCannon->fire();
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	m_pCannon->RotatePoint(touch->getLocationInView());
	m_pCannon->fire();
	this->schedule(schedule_selector(GameScene::fire), 0.15f);
	return true;
}

void GameScene::MusicOn()
{
	AudioEngine::play2d("music/bg_hokkaido.ogg");
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	m_pCannon->RotatePoint(touch->getLocationInView());
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	this->unschedule(schedule_selector(GameScene::fire));
	CCLOG("endgame");
}
Rect GameScene::cacleRect(Rect rc,float xr,float yr)
{
	float w = rc.size.width * xr;
	float h = rc.size.height * yr;
	Vec2 pt=Vec2(rc.origin.x + rc.size.width * (1.0f - xr)/2,rc.origin.y + rc.size.height * (1.0f - yr)/2);
	return Rect(pt.x,pt.y,w,h);

}
void GameScene::updateGame(float dt)
{
	bool caught = false;
	Bomb *curBomb = NULL;
	for(Bomb *buttle : this->m_pBullets)
	{
		if(buttle->getCaught())
		{
			continue;
		}
		for (Fish *fish : this->m_pFishes)
		{
			int fishState = fish->getFishState();
			if (fishState == 1)
			{
				Rect hitRec = this->cacleRect(fish->getFishSprite()->boundingBox(),0.8f,0.5f);
				Vec2 pBullte = buttle->getSpriteBullet()->getPosition();
				if(hitRec.containsPoint(pBullte))
				{
					caught = true;
					fish->showCaught(buttle->getHurt());
					curBomb = buttle;
					break;
				}
			}
			else
			{
				continue;
			}
		}
	}
	if(caught && curBomb != NULL)
	{
		curBomb->explode();
	}
}