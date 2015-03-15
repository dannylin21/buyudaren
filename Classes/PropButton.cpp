#include "PropButton.h"

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
	if(sType == 1)
	{
		m_proppic = Sprite::create("particles/bubblemenu.png");
		this->addChild(m_proppic);
		auto prop = Sprite::create(bg);
		this->addChild(prop);
	}
	m_countLab = LabelAtlas::create("5","images/Number/prop_num.png",16,21,'0');
	this->addChild(m_countLab);
	m_countLab->setPosition(10,-38);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(PropButton::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
		AddEffect();
		CCLOG("wo shi %d",this->getTag());
		return true;
	}
	return false;
}


PropButton::~PropButton()
{

}

void PropButton::AddEffect()
{
	//ParticleSystem *m_pariticle=ParticleSystemQuad::create("particles/taskAward.plist");
	//m_pariticle->setPositionType(ParticleSystem::PositionType::GROUPED);
	//m_pariticle->setAutoRemoveOnFinish(true);
	//m_pariticle->setPosition(0.0f,0.0f);
	//this->addChild(m_pariticle,10);
}