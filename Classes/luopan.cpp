#include "luopan.h"
#include "GameScene.h"
#include "Player.h"
USING_NS_CC;

LpWConf CLuoPan::m_luopic[9] =
{
	{"images/Scene/LotteryScene/item/lottery_item_001.png"},
	{"images/Scene/LotteryScene/item/lottery_item_002.png"},
	{"images/Scene/LotteryScene/item/lottery_item_003.png"},
	{"images/Scene/LotteryScene/item/lottery_item_004.png"},
	{"images/Scene/LotteryScene/item/lottery_item_005.png"},
	{"images/Scene/LotteryScene/item/lottery_item_006.png"},
	{"images/Scene/LotteryScene/item/lottery_item_014.png"},
	{"images/Scene/LotteryScene/item/lottery_item_013.png"},
	{"images/Scene/LotteryScene/item/lottery_item_012.png"}
};

LpNConf CLuoPan::m_itemnum[9] = {
	{"1"},{"2"},{"3"},{"5"},{"8"},{"10"},{"15"},{"20"},{"30"}};

LpPos CLuoPan::LpWpos[9] = {
	{0,130,0},
	{80,100,30.0f},
	{125,25,80.0f},
	{110,-60,115.0f},
	{48,-115,160.0f},
	{-45,-120,195.0f},
	{-110,-65,240.0f},
	{-122,25,-75.f},
	{-80,95,-45.0f}
};
LpPos CLuoPan::LpNpos[9] = {
	{5,65,0},
	{43,48,30.0f},
	{60,10,80.0f},
	{52,-33,115.0f},
	{22,-61,145.0f},
	{-20,-60,195.0f},
	{-52,-37,240.0f},
	{-65,5,290.f},
	{-48,51,-45.0f}
};

LpRote CLuoPan::LpResult[10]={
	{400.f,360.f},{400.f,400.f},{440.f,360.f},
	{360.f,560.f},{360.f,600.f},{360.f,680.f},
	{320.f,160.f},{640.f,440.f},{600.f,360.f},
	{560.f,360.f},
};

void CLuoPan::ShowLuoPan()
{
    if (Player::getInstance()->getLuoPanNum()==0)
    {
        ShowLuoPan(999);
    }
    else
    {
        ShowLuoPan(-1);
    }
}

void CLuoPan::ShowLuoPan(int FreeNum)
{
    CLuoPan *luopan = new CLuoPan();
	if(luopan && luopan->Init(FreeNum))
	{
		luopan->autorelease();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		luopan->setPosition(Vec2(visibleSize.width * 0.5f,visibleSize.height * 0.5f));
        luopan->setScale(0.5);
        auto action = ScaleTo::create(0.2, 1.3,1.3,1);
		auto raction = ScaleTo::create(0.1, 1.5,1.5,1);
		auto q = Sequence::create(action, raction, NULL);
        luopan->runAction(q);
		GameScene::m_GameMain->addChild(luopan,MAX_INDEX);
	}
	else
	{
		delete luopan;
		luopan = nullptr;
	}
}

void CLuoPan::calResult()
{
    if(m_freecount == 999)
    {
        CurGetIndex = 0;
        Player::getInstance()->setLuoPanNum(1);
        Player::getInstance()->SavePlayInfo();
    }
    else
    {
        CurGetIndex = rand() % 10;
    }
}

bool CLuoPan::Init(int FreeNum)
{
    m_freecount = FreeNum;
	calResult();
	make = Sprite::create("images/Scene/DailyScene/bgm.png");
	GameScene::m_GameMain->addChild(make,MAKE_INDEX);
	make->setOpacity(120);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	make->setPosition(visibleSize.width * 0.5f,visibleSize.height * 0.5f);

	m_outbg = Node::create();
	auto bg = Sprite::create("images/Scene/LotteryScene/lunpan/mid_out.png");
	m_outbg->addChild(bg);
	this->addChild(m_outbg);
	m_inBg = Node::create();
	auto nbg = Sprite::create("images/Scene/LotteryScene/lunpan/mid_in.png");
	m_inBg->addChild(nbg);
	this->addChild(m_inBg);
	auto upPic = Sprite::create("images/Scene/LotteryScene/lunpan/up.png");
	this->addChild(upPic);
	upPic->setPosition(0,10);
	auto btnClose = MenuItemImage::create("images/Common/btn_close1.png","images/Common/btn_close1.png",[&](Object* Sender){
		BUBBLE;
		make->removeFromParentAndCleanup(true);
		this->removeFromParentAndCleanup(true);
	});
	auto btnok = MenuItemImage::create("images/Scene/LotteryScene/lunpan/btn_ok.png","",[&](Object* Sender){
		((MenuItemImage*)Sender)->setVisible(false);
		this->ClickBtn();
	});
	auto Effects = ScaleTo::create(0.3f,1.2f,1.2f);
	auto Effects1=ScaleTo::create(0.3f,1.0f,1.f);
	auto seq = Sequence::create(Effects,Effects1,NULL);
	btnok->runAction(RepeatForever::create(seq));
	auto menu = Menu::create(btnClose,btnok,nullptr);
	this->addChild(menu,10);
	menu->setPosition(0,0);
	btnClose->setPosition(150,150);
    if(m_freecount==-1)
    {
        auto rmb = LabelTTF::create("4元3次", "Arial", 20);
        rmb->setColor(Color3B(57,58,64));
        rmb->setPosition(200, -144);
        rmb->setOpacity(255);
        this->addChild(rmb,300);
    }
	initLuow();
	return true;
}

void CLuoPan::AddResult(int index)
{
	if(index == 1)
	{
		auto bg = Sprite::create("images/Scene/LotteryScene/lunpan/light_out.png");
		bg->setPosition(0,130);
		this->addChild(bg,1);
		auto bg1 = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
		m_fly = Node::create();
		m_fly->addChild(bg1);
		m_fly->setPosition(0,0);
		Sprite *icon = nullptr; 
		Vec2 pos;
		switch(CurGetIndex)
		{
		case 0:
		case 1:
			pos=Vec2(80.f,280.f);
			icon = Sprite::create("images/Scene/GameScene/prop006.png");
			break;
		case 2:
			pos=Vec2(10.f,280.f);
			icon = Sprite::create("images/Scene/GameScene/prop007.png");
			break;
		default:
			pos=Vec2(-240.f,-280.f);
			icon = Sprite::create("images/Scene/ShopScene/money/coin6.png");
			break;
		}
		if(icon)
		{
			m_fly->addChild(icon);
		}
		m_fly->setScale(0.1f,0.1f);
		auto ac2 = ScaleTo::create(0.4f,0.8f,0.8f);
		auto slp = MoveBy::create(1, Vec3(0,0,0));
		auto slp2 = MoveBy::create(0.7, Vec3(0, 0, 0));
		auto ac3 = MoveTo::create(1.f,pos);
		auto sc = ScaleTo::create(0.3, 0.1, 0.1, 0.1);
		auto sc1 = ScaleTo::create(0.4, 0.8, 0.8, 1);
		CallFunc *call = CallFunc::create(std::bind(&CLuoPan::AddResult,this,2));
		auto seq = Sequence::create(slp,ac3, call, nullptr);
		this->addChild(m_fly,100);
		m_fly->runAction(Sequence::create(ac2, slp2,sc1, sc, nullptr));
		m_fly->runAction(seq);
	}
	else
	{
		GiveItem(CurGetIndex);
		make->removeFromParentAndCleanup(true);
        if(m_freecount == -1)
        {
            //sdk
            ShowLuoPan(2);
        }
        if(this->m_freecount != 999 && this->m_freecount >1)
        {
            this->m_freecount--;
            ShowLuoPan(this->m_freecount);
        }
		this->removeFromParentAndCleanup(true);

	}
}

void CLuoPan::ClickBtn()
{
	CallFunc *call = CallFunc::create(std::bind(&CLuoPan::AddResult,this,1));
	auto rote = RotateBy::create(2.f,2160.0f);
	auto rote1 = RotateBy::create(2.f,LpResult[CurGetIndex].w_angle);
	auto seq = Sequence::create(rote,rote1,call,nullptr);

	m_outbg->runAction(seq);
	auto rote2 = RotateBy::create(2.f,-2160.0f);
	auto rote3 = RotateBy::create(2.f,-LpResult[CurGetIndex].n_angle);
	auto seq1 = Sequence::create(rote2,rote3,nullptr);
	m_inBg->runAction(seq1);
	BUBBLE;
}

void CLuoPan:: initLuow()
{
	Sprite *item = NULL;
	Node *inNo = nullptr;
	Sprite* ico = nullptr;
	LabelAtlas *num = nullptr;
	for (int i = 0;i<9;i++)
	{
		item = Sprite::create(m_luopic[i].pic);
		m_outbg->addChild(item,2);
		item->setPosition(LpWpos[i].x,LpWpos[i].y);
		item->setRotation(LpWpos[i].rote);

		inNo=Node::create();
		ico=Sprite::create("images/Number/x_lunpan.png");
		num = LabelAtlas::create(m_itemnum[i].num,"images/Number/num_lunpan.png",12,15,'0');
		inNo->addChild(ico);
		inNo->addChild(num);
		ico->setPosition(-7,5);
		num->setPosition(0,0);
		m_inBg->addChild(inNo,2);
		inNo->setPosition(LpNpos[i].x,LpNpos[i].y);
		inNo->setRotation(LpNpos[i].rote);
	}

}
void CLuoPan::GiveItem(int Result)
{
	switch(Result)
	{
	case 0:
		GameScene::m_GameMain->m_thrCan->addPropNum(1);
		break;
	case 1:
		GameScene::m_GameMain->m_thrCan->addPropNum(2);
		break;
	case 2:
		GameScene::m_GameMain->m_secCan->addPropNum(1);
		break;
	default:
		break;
	}
}