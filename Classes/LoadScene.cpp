#include "LoadScene.h"
#include "GameScene.h"
#include "Player.h"
#include "DailyReward.h"

USING_NS_CC;

Scene* LoadScene::createLoadScene()
{
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	initBackGroud();
	iniLoadIng();
	return true;
}

void LoadScene::initBackGroud()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *bg = Sprite::create("images/Scene/MainMenuScene/start.png");
	bg->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	this->addChild(bg);
	ParticleSystem *m_pariticle=ParticleSystemQuad::create("particles/bubblePar_left.plist");
	m_pariticle->setPosition(visibleSize.width * 0.2f,visibleSize.height * 0.2f);
	m_pariticle->setPositionType(ParticleSystem::PositionType::GROUPED);
	m_pariticle->setAutoRemoveOnFinish(true);
	this->addChild(m_pariticle,10);

	ParticleSystem *m_pariticle1=ParticleSystemQuad::create("particles/bubblePar_right.plist");
	m_pariticle1->setPosition(visibleSize.width * 0.8f,visibleSize.height * 0.2f);
	m_pariticle1->setPositionType(ParticleSystem::PositionType::GROUPED);
	m_pariticle1->setAutoRemoveOnFinish(true);
	this->addChild(m_pariticle1,10);
	for(int i =1;i<8;i++)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(String::createWithFormat("fishFrame/fish%d.plist",i)->getCString());
	}
}

void LoadScene::iniLoadIng()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	procebg = Sprite::create("images/Scene/LoadScene/loading2.png");
	procebg->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	this->addChild(procebg);
	auto *start = Sprite::create("images/Scene/LoadScene/star.png");
	//start->setPosition(visibleSize.width * 0.5f - procebg->getContentSize().width * 0.5f+10,visibleSize.height * 0.5f);
	start->setPosition(20.0f,50.0f);
	procebg->addChild(start);
	auto *pto = ProgressTo::create(2,100);
	progress = Sprite::create("images/Scene/LoadScene/loading1.png");
	progresBar = ProgressTimer::create(progress);
	progresBar->setType(ProgressTimer::Type::BAR);
	progresBar->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	progresBar->setMidpoint(Vec2(0,1));
	progresBar->setBarChangeRate(Vec2(1,0));
	progresBar->setParent(0);
	progresBar->runAction(RepeatForever::create(pto));
	this->addChild(progresBar);
	this->schedule(schedule_selector(LoadScene::update),1);
}

void LoadScene::update(float dt)
{
	if(progresBar->getPercentage() >= 100)
	{
		this->unschedule(schedule_selector(LoadScene::update));
		progresBar->removeFromParentAndCleanup(true);
		procebg->removeFromParentAndCleanup(true);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto titleSprite= Sprite::create("images/Scene/MainMenuScene/logo.png");
		titleSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titleSprite->getContentSize().height / 2-10));
		this->addChild(titleSprite);
		Sprite *loadGold = Sprite::create("images/Scene/MainMenuScene/btn_coin.png");
		loadGold->setPosition(Vec2(visibleSize.width * 0.9f,visibleSize.height * 0.9f));
		this->addChild(loadGold);
		char AllGold[10]={0};
		sprintf(AllGold,"%d",Player::getInstance()->getCurGold());
		LabelAtlas *labelatlas = LabelAtlas::create(AllGold,"images/Number/num_gold.png",14,22,'0');
		labelatlas->setPosition(Vec2(visibleSize.width * 0.9f,visibleSize.height * 0.88f));
		this->addChild(labelatlas);
		LoadMenu();
	}
}

void LoadScene::LoadMenu()
{
	auto userItem = MenuItemImage::create("images/Scene/MainMenuScene/btn_start.png","images/Scene/MainMenuScene/btn_start.png",
		[](Object *sender) {
			Scene *scene = GameScene::createScene();
			Director::getInstance()->replaceScene(CCTransitionCrossFade::create(1.2f,scene));
	});
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_menus = Menu::createWithItem(userItem);
	m_menus->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.4f);
	//m_menus->setEnabled(false);
	this->addChild(m_menus);
	LoadRewardDaly();
}

void LoadScene::LoadRewardDaly()
{
	RewardDialog::PopReward(this);
	/*
	m_rewardLayer = Layer::create();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto *m_reward = Sprite::create("images/Scene/DailyScene/bg.png");
	m_reward->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	m_rewardLayer->addChild(m_reward);

	auto CloseItem = MenuItemImage::create("images/Common/btn_close2.png","images/Common/btn_close1.png",this,menu_selector(LoadScene::RemoveReward));
	auto GetBtn = MenuItemImage::create("images/Scene/DailyScene/btn_get.png","images/Scene/DailyScene/btn_get.png",[&](Object* sender)
	{

	});
	auto *m_rewardMenu = Menu::create(CloseItem,GetBtn,nullptr);
	m_rewardMenu->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	m_rewardLayer->addChild(m_rewardMenu);
	GetBtn->setPosition(0,-140);
	CloseItem->setPosition(430,70);
	this->addChild(m_rewardLayer);
	m_rewardLayer->setPosition(visibleSize.width * 0.005f, visibleSize.height * 0.001f);
	*/
	
	
	//auto *
}



void LoadScene::RemoveReward(Ref *sender)
{
	m_rewardLayer->removeFromParentAndCleanup(true);
	m_menus->setEnabled(true);
}
