#include "TipWin.h"
#include "GameScene.h"

USING_NS_CC;

bool TipWin::Init()
{
	auto bg = Sprite::create("images/Scene/GiftScene/bg.png");
	this->addChild(bg);
	auto BtnItem = MenuItemImage::create("images/Scene/GiftScene/btn_got.png","images/Scene/GiftScene/btn_got.png",
		[&](Object *sender) {
		this->Get();	
	});
	auto BtnClose = MenuItemImage::create("images/Common/btn_close2.png","images/Common/btn_close2.png",[&](Object *sender){
		this->CLosePop();
	});

	auto m_menus = Menu::create(BtnItem,BtnClose,NULL);
	this->addChild(m_menus,1);
	m_menus->setPosition(0,0);
	BtnItem->setPosition(10,-150);
	auto Effects = ScaleTo::create(0.3f,1.2f,1.2f);
	auto Effects1=ScaleTo::create(0.3f,1.0f,1.f);
	auto seq = Sequence::create(Effects,Effects1,NULL);
	BtnItem->runAction(RepeatForever::create(seq));
	BtnClose->setPosition(190,85);
	auto GetPng = Sprite::create("images/Scene/GiftScene/word_get.png");
	this->addChild(GetPng,1);
	GetPng->setPosition(-100,0);
	
	auto NoStop = Sprite::create("images/Scene/GiftScene/word_top.png");
	this->addChild(NoStop,1);
	NoStop->setPosition(-10,50);
	ParticleSystemQuad*    _leftemitter;
	_leftemitter = ParticleSystemQuad::create("particles/coin_left.plist");
	_leftemitter->retain();
	addChild(_leftemitter, -1);
	_leftemitter->setPosition(-50,0);
	ParticleSystemQuad*    _rightemitter;
	_rightemitter = ParticleSystemQuad::create("particles/coin_right.plist");
	_rightemitter->retain();
	addChild(_rightemitter, -1);
	_leftemitter->setPosition(-50,0);
	ParticleSystemQuad*    _midemitter;
	_midemitter = ParticleSystemQuad::create("particles/coin_mid.plist");
	_midemitter->retain();
	addChild(_midemitter, -1);
	_midemitter->setPosition(-50,0);
	AddFlash();
	return true;
}

void TipWin::AddFlash()
{
	auto plashbg = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
	this->addChild(plashbg);
	plashbg->setPosition(0,0);
	auto rote = RotateBy::create(2.f,360.0f);
	plashbg->runAction(RepeatForever::create(rote));
}

void TipWin::ShowTip()
{
	TipWin *popwin = new TipWin();
	if(popwin&&popwin->Init())
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		popwin->setPosition(Vec2(visibleSize.width * 0.5f,visibleSize.height * 0.5f));
		GameScene::m_GameMain->addChild(popwin,1000);
	}
}

void TipWin::CLosePop()
{
	this->removeFromParentAndCleanup(true);
}

void TipWin::Get()
{
	//sdk get
	CLosePop();
}

