#include "Cannon.h"
#include "GameScene.h"


USING_NS_CC;

CanTypeConf Cannon::CanConf[9] = {
	{"cannon001.png",50,100,1,"bullet001.png","Laser_prepare%03d.png",3},
	{"cannon002.png",100,100,2,"bullet001.png","Torpedo_launch%03d.png",2},
	{"cannon003.png",150,200,1,"bullet002.png","Torpedo_launch%03d.png",2},
	{"cannon004.png",250,300,1,"bullet002.png","Lightning_launch%03d.png",3},
	{"cannon005.png",400,450,1,"bullet003.png","Lightning_catch%03d.png",4},
	{"cannon006.png",500,600,1,"bullet003.png","Lightning_catch%03d.png",4},
	{"laster001.png",0,5000,1,"bullet003.png","Laser_launch%03d.png",2},
	{"lightning001.png",0,4500,1,"bullet003.png","Lightning_catch%03d.png",5},
	{"torpedoDown.png",0,3500,1,"bullet013.png","Torpedo_launch%03d.png",2}
};


Cannon* Cannon::createWithCannonType(int cannonType,GameScene *fishLayer)
{
	Cannon* pCannon = new Cannon(cannonType,fishLayer);
	if(pCannon && pCannon->initWithCannonType())
	{
		pCannon->autorelease();
		return pCannon;
	}
	else
	{
		CC_SAFE_DELETE(pCannon);
		return NULL;
	}
}

Cannon::Cannon(int cannonType,GameScene *gameLayer):
	m_pGameLayer(gameLayer),m_cannonType(cannonType),
	m_fRotation(0.0f)
{

}

bool Cannon::initWithCannonType()
{
	m_pSpirte = Sprite::create();
	m_effect = Sprite::create();
	m_label = LabelAtlas::create("0","images/Number/cannonlNumber.png",13,17,'0');
	RefreshCanType();
	m_pSpirte->setAnchorPoint(Vec2(0.5f,0.5f));	
	m_pGameLayer->m_bottom->addChild(this,4);		
	m_pSpirte->setPosition(3,5);	
	this->addChild(m_pSpirte,1);	//
	this->addChild(m_effect,2);	
	this->addChild(m_label,3);
	this->setAnchorPoint(Vec2(0.4f,0.5f));
	return true;
}

void Cannon::ChangeType(int cannonType)
{
	CCLOG("haha:%d",cannonType) ;
	this->m_cannonType = cannonType;
	RefreshCanType();	
}

void Cannon::RefreshCanType()
{
	if(m_cannonType == 9)
	{
		m_label->setVisible(false);
		m_effect->setVisible(true);
		m_effect->stopAllActions();
		m_effect->setPosition(0,0);
		m_pSpirte->setTexture("cannonFrame/torpedoDown.png");
		m_effect->setTexture("images/Bullets/bullet013.png");
	}
	else if(m_cannonType == 7)
	{
		m_label->setVisible(false);
		m_effect->setVisible(true);
		m_effect->stopAllActions();
		SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(CanConf[m_cannonType-1].m_Name.c_str());
		SpriteFrame* Frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("Laser_begin001.png");
		m_pSpirte->setSpriteFrame(Frame);
		m_effect->setSpriteFrame(Frame1);
		m_effect->setPosition(0,90);
		char FramePng[50] = {0};
		for(int i = 1;i<4;i++)
		{
			sprintf(FramePng,"Laser_begin%03d.png",i);		 
			SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(FramePng);
			m_startReady.pushBack(tempFrame);
		}
		Animation* animation = Animation::createWithSpriteFrames(m_startReady,0.3f);
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		Animate* animat = Animate::create(animation);
		m_effect->runAction(RepeatForever::create(animat));
	}
	else
	{
		m_label->setVisible(true);
		SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(CanConf[m_cannonType-1].m_Name.c_str());
		m_pSpirte->setSpriteFrame(Frame);
		m_effect->setVisible(false);
		char LoseNum[10]={0};
		sprintf(LoseNum,"%d",CanConf[m_cannonType-1].NeedGold);
		m_label->setString(LoseNum);
		if(CanConf[m_cannonType-1].NeedGold >=100)
		{
			m_label->setPosition(-20,-5);
		}
		else
		{
			m_label->setPosition(-17,-5);
		}
	}
}

void Cannon::Rotation(float rotate)
{
	float absf_rotation=fabsf(m_fRotation-this->m_pSpirte->getRotation());
	float duration=absf_rotation/180.0f*0.2f;
	auto pAction = RotateTo::create(duration, rotate);
	this->runAction(pAction);
}

void Cannon::RotatePoint(Vec2 ptTo1)
{
	Vec2 ptTo = Director::getInstance()->convertToGL(this->getParent()->convertToNodeSpace(ptTo1));
	Vec2 ptFrom = this->getPosition();
	ptFrom=Vec2(ptFrom.x+10,ptFrom.y+10);
	float angle=atan2f(ptTo.y-ptFrom.y,ptTo.x-ptFrom.x)/M_PI * 180.0f;
	CCLOG("an:%f",angle);
	this->setRotation(90.0f-angle);
	this->m_dirPos= ptTo1;
}

void Cannon::fire()
{
	if(GameScene::duangOpen)
		AudioEngine::play2d("music/eft_fire.mp3");
	if(CanConf[m_cannonType-1].m_bulletNum == 2)
	{
		Bomb* pBullet1 = Bomb::createWithBombType(CanConf[m_cannonType-1],this->m_pGameLayer,0.48f,this);
		pBullet1->retain();
		pBullet1->shootTo(Vec2(this->m_dirPos.x-8,this->m_dirPos.y-8));
		Bomb* pBullet2 = Bomb::createWithBombType(CanConf[m_cannonType-1],this->m_pGameLayer,0.52f,this);
		pBullet2->retain();
		pBullet2->shootTo(Vec2(this->m_dirPos.x+8,this->m_dirPos.y+8));
	}
	else
	{
		if(m_cannonType == 9 || m_cannonType == 7)
		{
			m_effect->setVisible(false);
		}
		Bomb* pBullet = Bomb::createWithBombType(CanConf[m_cannonType-1],this->m_pGameLayer,0.5f,this);
		pBullet->retain();
		pBullet->shootTo(this->m_dirPos);
	}
}

void Cannon::BombCallBack()
{
	if(m_cannonType == 9|| m_cannonType == 7)
	{
		m_effect->setVisible(true);
	}
}

Cannon::~Cannon()
{
	CCLOG("des cannoo");
}

void Cannon::AddBulletNum(int InCrease)
{
	int OldNum = this->getBulletCount();
	this->setBulletCount(OldNum+InCrease);
}
