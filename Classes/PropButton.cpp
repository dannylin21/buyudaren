#include "PropButton.h"
#include "TipWin.h"
#include "Player.h"
#include "GameScene.h"

USING_NS_CC;

PropButton* PropButton::CreateButtonWidthPNG(std::string bg,int sType)
{
	PropButton* buttone = new PropButton();
	if(buttone && buttone->init(bg,sType))
	{
		buttone->autorelease();
		return buttone;
	}
	else
	{
		delete buttone;
		buttone = nullptr;
	}
}

bool PropButton::init(std::string bg,int sType)
{
    m_bgLayer = Node::create();
	m_plashtm = 30;
	m_flash = nullptr;
	m_proppic = Sprite::create("particles/bubblemenu.png");
	m_bgLayer->addChild(m_proppic,1);
	m_proppic->setScale(1.7f,1.7f);
	auto prop = Sprite::create(bg);
	prop->setScale(0.5f,0.5f);
	m_bgLayer->addChild(prop,2);
    
	std::string CanNum ;
	this->setBtnType(sType);
	switch (sType)
	{
	case 1:
	{
		m_propNum = Player::getInstance()->getCanOneNum();
		CanNum = StringUtils::format("%d", m_propNum);
        rmb = LabelTTF::create("8元3个", "Arial", 17);
		rmb->setColor(Color3B(88, 172, 176));
		rmb->setOpacity(m_propNum >0?0:255);
		rmb->setPosition(0, -52);
		this->addChild(rmb);
	}
		break;
	case 2:
	{
		m_propNum = Player::getInstance()->getCanSecNum();
		CanNum = StringUtils::format("%d", m_propNum);
        rmb = LabelTTF::create("6元3个", "Arial", 17);
		rmb->setColor(Color3B(88, 172, 176));
		rmb->setOpacity(m_propNum >0?0:255);
		rmb->setPosition(0, -52);
		this->addChild(rmb);
	}
		break;
	default:
	{
		m_propNum = Player::getInstance()->getCanThrNum();
		CanNum = StringUtils::format("%d", m_propNum);
		rmb = LabelTTF::create("4元3个", "Arial", 17);
		rmb->setColor(Color3B(88, 172, 176));
        rmb->setOpacity(m_propNum >0?0:255);
		rmb->setPosition(0, -52);
		this->addChild(rmb);
	}
		break;
	}
	m_countLab = LabelAtlas::create(CanNum,"images/Number/prop_num.png",16,21,'0');
	m_bgLayer->addChild(m_countLab,2);
	m_countLab->setPosition(10,-38);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	m_duihuan = Sprite::create("images/Word/prop_exchange.png");
	m_duihuan->setOpacity(m_propNum > 0 ? 0 : 255);
	m_bgLayer->addChild(m_duihuan,1000);


	listener->onTouchBegan = CC_CALLBACK_2(PropButton::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    this->addChild(m_bgLayer);
	return true;
}

bool PropButton::CheckTouchMe(Touch *touch)
{
	Vec2 touchLocation = touch->getLocation(); // Get the touch position
	Vec2 local = this->convertToNodeSpace(touchLocation);
	Rect bBox = m_proppic->getBoundingBox();
	return bBox.containsPoint(local);
}

bool PropButton::onTouchBegan(Touch *touch, Event *unused_event)
{
	if(CheckTouchMe(touch))
	{
		if(this->m_propNum > 0)
		{
			switch(this->getBtnType())
			{
			case 1:
				GameScene::m_GameMain->m_pCannon->ChangeType(7);
                addPropNum(-1);
				break;
			case 2:
				GameScene::m_GameMain->m_pCannon->ChangeType(9);
                addPropNum(-1);
				break;
			case 3:
				GameScene::m_GameMain->m_pCannon->ChangeType(8);
                addPropNum(-1);
				break;
			}	
		}
		else
		{
			switch(this->getBtnType())
			{
			case 1:
				BuyCan(6);
				break;
			case 2:
				BuyCan(7);
				break;
			case 3:
				BuyCan(8);
				break;
			}
		}
		return true;
	}
	return false;
}


PropButton::~PropButton()
{

}

void PropButton::AddEffect(bool add)
{
	if(add)
	{
		if(m_flash)
		{
			m_flash->setVisible(true);
		}
		else
		{
			m_flash = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
			m_flash->setScale(0.5f,0.5f);
			m_flash->setPosition(0,0);
			auto rote = RotateBy::create(2.f,360.0f);
			auto rote1 = RotateBy::create(2.f,360.0f);
			auto rote2 = RotateBy::create(2.f,360.0f);
			m_flash->runAction(RepeatForever::create(rote));
			m_bgLayer->addChild(m_flash);
		}
		auto Effects = ScaleTo::create(0.3f,1.2f,1.2f);
		auto Effects1=ScaleTo::create(0.3f,1.0f,1.f);
		auto seq = Sequence::create(Effects,Effects1,NULL);
		m_bgLayer->runAction(RepeatForever::create(seq));
	}
	else
	{
		if(m_flash)
		{
			m_flash->setVisible(false);
		}
		m_bgLayer->stopAllActions();
	}
}

int PropButton::GetPropNum()
{
	return this->m_propNum;
}

void PropButton::addPropNum(int increase)
{
	if(increase < 0 && m_propNum <= 0)
	{
		return;
	}
	m_propNum += increase;
	m_countLab->setString(StringUtils::format("%d",m_propNum));
	switch(this->getTag())
	{
	case 1:
		Player::getInstance()->setCanOneNum(m_propNum);
		break;
	case 2:
		Player::getInstance()->setCanSecNum(m_propNum);
		break;
	case 3:
		Player::getInstance()->setCanThrNum(m_propNum);
		break;
	}
	m_duihuan->setOpacity(m_propNum > 0 ? 0 : 255);
    rmb->setOpacity(m_propNum >0?0:255);
	Player::getInstance()->SavePlayInfo();
}

void PropButton::Tick()
{
	m_plashtm --;
	if(m_plashtm == 0)
	{
		m_plashtm = 30;
		AddEffect(true);
	}
	else if(m_plashtm == 20)
	{
		AddEffect(false);
	}

}

void PropButton::BuyCan(int Rmb)
{
	//sdk 7:8+3 8:4+3 9:6+3

}