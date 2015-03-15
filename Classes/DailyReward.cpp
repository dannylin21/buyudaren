#include "DailyReward.h"

USING_NS_CC;

void RewardDialog::PopReward(Layer *Parent)
{
	RewardDialog *Dialog = new RewardDialog();
	if(Dialog && Dialog->init())
	{
		Dialog->autorelease();
		Parent->addChild(Dialog);
	}
	else
	{
		delete Dialog;
		Dialog = nullptr;
	}
}

bool RewardDialog::init()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);
	auto m_reward = Sprite::create("images/Scene/DailyScene/bg.png");
	this->addChild(m_reward);

	auto CloseItem = MenuItemImage::create("images/Common/btn_close2.png","images/Common/btn_close1.png",this,menu_selector(RewardDialog::CloseReward));
	auto GetBtn = MenuItemImage::create("images/Scene/DailyScene/btn_get.png","images/Scene/DailyScene/btn_get.png",[&](Object* sender)
	{

	});
	auto m_rewardMenu = Menu::create(CloseItem,GetBtn,nullptr);
	m_rewardMenu->setPosition(0,0);
	this->addChild(m_rewardMenu);
	GetBtn->setPosition(0,-140);
	CloseItem->setPosition(430,70);
	LoadItem();
	return true;
}

void RewardDialog::CloseReward(Ref *sender)
{
	this->removeFromParentAndCleanup(true);
}

RewardDialog::~RewardDialog()
{
	CCLOG("delelelelellelelle");
}

void RewardDialog::LoadItem()
{
	auto Coin1 = Sprite::create("images/Scene/ShopScene/money/coin1.png");
	auto Coin2 = Sprite::create("images/Scene/ShopScene/money/coin4.png");
	auto Coin3 = Sprite::create("images/Scene/ShopScene/money/coin5.png");
	auto Coin4 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
	this->addChild(Coin1);
	Coin1->setPosition(-350,0);
	this->addChild(Coin2);
	Coin2->setPosition(-200,0);
	this->addChild(Coin3);
	Coin3->setPosition(-100,0);
	this->addChild(Coin4);
	Coin4->setPosition(0,-20);
}