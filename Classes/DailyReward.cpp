#include "DailyReward.h"
#include "Player.h"
#include "TipWin.h"
USING_NS_CC;

HasGet RewardDialog::m_HaveGet[7] = 
{
	{-360,-55},
	{-240,-55},
	{-118,-55},
	{-2,-55},
	{120,-55},
	{240,-55},
	{364,-55}
};

void RewardDialog::PopReward(Layer *Parent,Sprite *make)
{
	RewardDialog *Dialog = new RewardDialog();
	if(Dialog && Dialog->init())
	{
		Dialog->m_make = make;
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
		this->GetItem();
	});
	auto m_rewardMenu = Menu::create(CloseItem,GetBtn,nullptr);
	m_rewardMenu->setPosition(0,0);
	this->addChild(m_rewardMenu,3);
	GetBtn->setPosition(0,-140);
	CloseItem->setPosition(430,70);
	LoadItem();
	auto Effects = ScaleTo::create(0.5f,1.2f,1.2f);
	auto Effects1=ScaleTo::create(0.5f,1.0f,1.f);
	auto seq = Sequence::create(Effects,Effects1,NULL);
	GetBtn->runAction(RepeatForever::create(seq));
    int CurGet = Player::getInstance()->getGetReward();
    LabelTTF *rmb=nullptr;
    switch (CurGet) {
        case 1:
            rmb = LabelTTF::create("仅需8元", "Arial", 17);
            break;
        case 2:
            rmb = LabelTTF::create("仅需10元", "Arial", 17);
            break;
        case 3:
        	rmb = LabelTTF::create("仅需12元", "Arial", 17);
            break;
        case 4:
        case 5:
        case 6:
            rmb = LabelTTF::create("仅需16元", "Arial", 17);
            break;
        default:
            break;
    }
    if(rmb)
    {
        rmb->setColor(Color3B(132, 138, 110));
        rmb->setPosition(98, -136);
        rmb->setOpacity(255);
        this->addChild(rmb, 2);
    }
	return true;
}

void RewardDialog::CloseReward(Ref *sender)
{
	BUBBLE;
	m_make->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
	TipWin::ShowTip(3);
}

RewardDialog::~RewardDialog()
{
	CCLOG("delelelelellelelle");
}

void RewardDialog::LoadItem()
{
	auto Coin1 = Sprite::create("images/Scene/ShopScene/money/coin1.png");
	auto Label1 = LabelAtlas::create("1888","images/Number/dailylog.png",19,18,'0');
	auto Coin2 = Sprite::create("images/Scene/ShopScene/money/coin4.png");
	auto Label2 = LabelAtlas::create("18888","images/Number/dailylog.png",19,18,'0');
	auto Coin3 = Sprite::create("images/Scene/ShopScene/money/coin5.png");
	auto Label3 = LabelAtlas::create("28888","images/Number/dailylog.png",19,18,'0');
	auto Coin4 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
	auto Label4 = LabelAtlas::create("38888","images/Number/dailylog.png",19,18,'0');
	this->addChild(Coin1,2);
	this->addChild(Label1,3);
	this->addChild(Label2,3);
	this->addChild(Label3,3);
	this->addChild(Label4,3);
	Coin1->setScale(0.9f,0.9f);
	Coin2->setScale(0.9f,0.9f);
	Coin3->setScale(0.8f,0.9f);
	Coin4->setScale(0.9f,0.9f);
	Coin1->setPosition(-360,-60);
	Label1->setPosition(-400,-110);

	this->addChild(Coin2,2);
	Coin2->setPosition(-240,-60);
	Label2->setPosition(-290,-110);
	this->addChild(Coin3,2);
	Coin3->setPosition(-118,-60);
	Label3->setPosition(-186,-110);
	this->addChild(Coin4,2);
	Coin4->setPosition(-3,-60);
	Label4->setPosition(-50,-110);

	auto plashbg5 = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
	this->addChild(plashbg5,1);
	plashbg5->setScale(0.5f,0.5f);
	plashbg5->setPosition(120,-40);
	auto rote = RotateBy::create(3.f,360.0f);
	auto rote1 = RotateBy::create(3.f,360.0f);
	auto rote2 = RotateBy::create(3.f,360.0f);
	plashbg5->runAction(RepeatForever::create(rote));

	auto plashbg6 = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
	this->addChild(plashbg6,1);
	plashbg6->setScale(0.5f,0.5f);
	plashbg6->setPosition(240,-40);
	plashbg6->runAction(RepeatForever::create(rote1));
	
	auto plashbg7 = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
	this->addChild(plashbg7,1);
	plashbg7->setScale(0.5f,0.5f);
	plashbg7->setPosition(360,-40);
	plashbg7->runAction(RepeatForever::create(rote2));

	auto Coin5 = Sprite::create("images/Scene/GameScene/prop006.png");
	auto Coin6 = Sprite::create("images/Scene/GameScene/prop007.png");
	auto Coin7 = Sprite::create("images/Scene/GameScene/prop008.png");
	this->addChild(Coin5,2);
	this->addChild(Coin6,2);
	this->addChild(Coin7,2);
	Coin5->setPosition(120,-40);
	Coin6->setPosition(240,-40);
	Coin7->setPosition(360,-40);
	Coin5->setScale(0.6f,0.6f);
	Coin6->setScale(0.5f,0.5f);
	Coin7->setScale(0.6f,0.6f);

	auto Coin51 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
	auto Coin61 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
	auto Coin71 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
	this->addChild(Coin51,3);
	this->addChild(Coin61,3);
	this->addChild(Coin71,3);
	Coin51->setScale(0.35f,0.35f);
	Coin61->setScale(0.35f,0.35f);
	Coin71->setScale(0.35f,0.35f);

	Coin51->setPosition(80,-90);
	Coin61->setPosition(200,-90);
	Coin71->setPosition(323,-90);


	auto Coin52 = LabelAtlas::create("2","images/Number/gift_prop.png",20,30,'0');
	auto Coin62 = LabelAtlas::create("2","images/Number/gift_prop.png",20,30,'0');
	auto Coin72 = LabelAtlas::create("2","images/Number/gift_prop.png",20,30,'0');
	this->addChild(Coin72,3);
	this->addChild(Coin62,3);
	this->addChild(Coin52,3);
	Coin52->setPosition(150,-80);
	Coin62->setPosition(270,-80);
	Coin72->setPosition(400,-80);

	auto Coin53 = LabelAtlas::create("16666","images/Number/shop_price_num.png",17,22,'0');
	auto Coin63 = LabelAtlas::create("8888","images/Number/shop_price_num.png",17,22,'0');
	auto Coin73 = LabelAtlas::create("6666","images/Number/shop_price_num.png",17,22,'0');
	this->addChild(Coin73,3);
	this->addChild(Coin63,3);
	this->addChild(Coin53,3);
	Coin53->setPosition(90,-110);
	Coin63->setPosition(210,-110);
	Coin73->setPosition(340,-110);
	int CurGet = Player::getInstance()->getGetReward();
	Sprite *GetPic=nullptr;
	for (int i=0;i<CurGet;i++)
	{
		GetPic = Sprite::create("images/Scene/DailyScene/got.png");
		this->addChild(GetPic,4);
		GetPic->setPosition(m_HaveGet[i].x,m_HaveGet[i].y);
	}
	if(CurGet < 7 && !Player::getInstance()->getLoginGet())
	{
		auto CurGetB = Sprite::create("images/Scene/DailyScene/bottom.png");
		auto CurGetStart=Sprite::create("images/Scene/DailyScene/light.png");
		this->addChild(CurGetB);
		this->addChild(CurGetStart);
		CurGetB->setPosition(m_HaveGet[CurGet].x,m_HaveGet[CurGet].y);
		CurGetStart->setPosition(m_HaveGet[CurGet].x,m_HaveGet[CurGet].y);
	}
}

void RewardDialog::GetItem()
{
	if(!Player::getInstance()->getLoginGet())
	{
		Player::getInstance()->setLoginGet(true);
		int CurGet = Player::getInstance()->getGetReward();
        switch (CurGet) {
            case 0:
                Player::getInstance()->AddGold(1888);
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                break;
        }
		if(CurGet < 7)
		{
			CurGet ++;
			Player::getInstance()->setGetReward(CurGet);
			Player::getInstance()->SavePlayInfo();
             
		}
	}
	CloseReward(nullptr);
}