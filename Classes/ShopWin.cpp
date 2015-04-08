#include "ShopWin.h"
#include "GameScene.h"
#include "LoadScene.h"
USING_NS_CC;

ShopItem ShopWin::m_config[6] ={
	{"images/Scene/ShopScene/money/coin1.png","3800","2",-320,10,-353,-85,-320,-157},
	{"images/Scene/ShopScene/money/coin2.png","9000","4",-190,10,-233,-85,-190,-157},
	{"images/Scene/ShopScene/money/coin3.png","12000","6",-60,10,-103,-85,-60,-157},
	{"images/Scene/ShopScene/money/coin4.png","18000","8",70,10,27,-85,70,-157},
	{"images/Scene/ShopScene/money/coin5.png","26000","10",200,10,157,-85,195,-157},
	{"images/Scene/ShopScene/money/coin6.png","38000","12",330,10,287,-85,325,-157},
};

void ShopWin::ShowShop()
{
	BUBBLE;
	ShopWin *m_shop = new ShopWin();
	if(m_shop && m_shop->Init())
	{
		m_shop->autorelease();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		m_shop->setPosition(Vec2(visibleSize.width * 0.5f,visibleSize.height * 0.5f));
        if(GameScene::m_GameMain)
        {
            GameScene::m_GameMain->addChild(m_shop,100);
        }
        else
        {
            LoadScene::m_loadScene->addChild(m_shop,100);
        }
	}
	else
	{
		delete m_shop;
		m_shop = nullptr;
	}
}

bool ShopWin::Init()
{
	auto bg = Sprite::create("images/Scene/ShopScene/bg.png");
	this->addChild(bg);
	Vector<MenuItem*> m_items;
	MenuItem *Item = nullptr;
	Sprite *Icon = nullptr;
	Sprite *Price = nullptr;
	LabelAtlas* goldLab,*rmblb;
	int startx = -320;
	for (int i = 0;i<6;i++)
	{
		Item = MenuItemImage::create("images/Scene/ShopScene/itembg.png","images/Scene/ShopScene/itembg2.png",[&](Object* Sender)
		{
			this->BtnClick(i);
		});
		Item->setPosition(startx+i*130,-30);
		Icon = Sprite::create(m_config[i].pic);
		this->addChild(Icon,2);
		Icon->setPosition(m_config[i].m_ix,m_config[i].m_iy);
		Price=Sprite::create("images/Scene/ShopScene/pricebg.png");
		this->addChild(Price,2);
		Price->setPosition(startx + i * 130,-145);
		m_items.pushBack(Item);
		goldLab = LabelAtlas::create(m_config[i].m_gold.c_str(),"images/Number/shop_coinnum.png",19,26,'0');
		this->addChild(goldLab,2);
		goldLab->setPosition(m_config[i].m_gx,m_config[i].m_gy);
		rmblb = LabelAtlas::create(m_config[i].m_rmb.c_str(),"images/Number/shop_price_num.png",17,22,'0');
		rmblb->setPosition(m_config[i].m_px,m_config[i].m_py);
		this->addChild(rmblb,2);
	}
	auto CloseBtn = MenuItemImage::create("images/Common/btn_close3.png","images/Common/btn_close3.png",[&](Object* Sender)
	{
		BUBBLE;
		this->removeFromParentAndCleanup(true);
	});
	m_items.pushBack(CloseBtn);
	auto m_menu = Menu::createWithArray(m_items);
	this->addChild(m_menu);
	m_menu->setPosition(0,0);
	CloseBtn->setPosition(360,160);
	return true;
}

void ShopWin::BtnClick(int sindex)
{
	BUBBLE;
}