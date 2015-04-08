#include "LoadScene.h"
#include "GameScene.h"
#include "Player.h"
#include "DailyReward.h"
#include "ShopWin.h"

USING_NS_CC;

LoadScene* LoadScene::m_loadScene = nullptr;
bool LoadScene::duangOpen = true;
bool LoadScene::backOpen = true;


Scene* LoadScene::createLoadScene()
{
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	LoadScene::m_loadScene = layer;
	scene->addChild(layer);
	return scene;
}

bool LoadScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//if(LoadScene::backOpen)
	//	m_musicid = AudioEngine::play2d("music/bg_menu.ogg",true);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	initBackGroud();
	iniLoadIng();
	return true;
}

void LoadScene::initBackGroud()
{
	this->setKeyboardEnabled(true);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *bg = Sprite::create("images/Scene/MainMenuScene/start.png");
	bg->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	this->addChild(bg);
	ParticleSystem *m_pariticle=ParticleSystemQuad::create("particles/bubblePar_left.plist");
	m_pariticle->setPosition(visibleSize.width * 0.2f,visibleSize.height * 0.2f);
	m_pariticle->setPositionType(ParticleSystem::PositionType::GROUPED);
	m_pariticle->setAutoRemoveOnFinish(true);
	this->addChild(m_pariticle);

	ParticleSystem *m_pariticle1=ParticleSystemQuad::create("particles/bubblePar_right.plist");
	m_pariticle1->setPosition(visibleSize.width * 0.8f,visibleSize.height * 0.2f);
	m_pariticle1->setPositionType(ParticleSystem::PositionType::GROUPED);
	m_pariticle1->setAutoRemoveOnFinish(true);
	this->addChild(m_pariticle1);
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
	progresBar->runAction(Sequence::create(pto, CallFunc::create([]{
		if(LoadScene::backOpen) 
			AudioEngine::play2d("music/bg_menu.ogg",true);
	}), NULL));
	this->addChild(progresBar);
	this->schedule(schedule_selector(LoadScene::update),0.01);
}


extern float offsetx, offsety;

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
        
        auto loadGoldbtn = MenuItemImage::create("images/Scene/MainMenuScene/btn_coin.png","",[&](Ref* Sender){
            ShopWin::ShowShop();
        });
        auto menu = Menu::create(loadGoldbtn,nullptr);
		menu->setPosition(Vec2(visibleSize.width * 0.9f,visibleSize.height * 0.9f));
		this->addChild(menu);
		char AllGold[10]={0};
		int CurGold = Player::getInstance()->getCurGold();
		sprintf(AllGold,"%d",CurGold);
		labelatlas = LabelAtlas::create(AllGold,"images/Number/num_gold.png",14,22,'0');
		labelatlas->setPosition(Vec2(visibleSize.width * 0.9f,visibleSize.height * 0.88f));
		this->addChild(labelatlas);
		LoadMenu();
	}
}


void LoadScene::switchState(cocos2d::Sprite* sp, int flag)
{
	sp->setOpacity(sp->getOpacity() == 255 ? 0 : 255);
	if (sp->getOpacity() == 0)
	{
		if (flag == 1)
		{
			AudioEngine::play2d("music/bg_menu.ogg",true);
			LoadScene::backOpen = true;
		}
		else
			LoadScene::duangOpen = true;
	}
	else
	{
		if (flag == 1)
		{
			AudioEngine::stopAll();
			LoadScene::backOpen = false;
		}
		else
			LoadScene::duangOpen = false;
	}
}

void LoadScene::LoadMenu()
{
	auto userItem = MenuItemImage::create("images/Scene/MainMenuScene/btn_start.png","images/Scene/MainMenuScene/btn_start.png",
		[&](Ref *sender) {
            Player::getInstance()->setLoginTime(GameScene::GetTimeNow());
			AudioEngine::stop(m_musicid);
            m_loadScene = nullptr;
			Scene *scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);//CCTransitionCrossFade::create(1.2f,scene));
	});

	duangDis = Sprite::create("images/Scene/SettingScene/cross.png");
	backDis = Sprite::create("images/Scene/SettingScene/cross.png");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_menus = Menu::createWithItem(userItem);
	m_menus->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.4f);
	this->addChild(m_menus);

	auto BackMusicMenu = MenuItemImage::create("images/Scene/SettingScene/btn_bgmswitch.png", "images/Scene/SettingScene/btn_bgmswitch.png",
		[&](Ref *sender) {
			switchState(backDis,1);
	});
	auto DuangMusicMenu = MenuItemImage::create("images/Scene/SettingScene/btn_eftswitch.png", "images/Scene/SettingScene/btn_eftswitch.png",
		[&](Ref *sender) {
			switchState(duangDis, 2);
	});
	
	auto menus = Menu::create(BackMusicMenu, DuangMusicMenu, NULL);
	this->addChild(menus,200);
	menus->setPosition(50, 60);
	BackMusicMenu->setPosition(0, 60);
	BackMusicMenu->addChild(backDis);
	DuangMusicMenu->setPosition(0, 0);
	DuangMusicMenu->addChild(duangDis);
	duangDis->setPosition(30, 30);
	duangDis->setOpacity(LoadScene::duangOpen?0:255);
	backDis->setPosition(30, 30);
	backDis->setOpacity(LoadScene::backOpen?0:255);

	LoadRewardDaly();
}

void LoadScene::LoadRewardDaly()
{
	auto make = Sprite::create("images/Scene/DailyScene/bgm.png");
	this->addChild(make);
	make->setOpacity(120);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	make->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	RewardDialog::PopReward(this,make);
}
