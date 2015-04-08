#include "Cannon.h"
#include "LoadScene.h"
#include "GameScene.h"
USING_NS_CC;

Cannon* Cannon::createWithCannonType(int cannonType)
{
	Cannon* pCannon = new Cannon(cannonType);
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

Cannon::Cannon(int cannonType):
	m_cannonType(cannonType),m_fRotation(0.0f)
{

}

bool Cannon::initWithCannonType()
{
	m_pSpirte = Sprite::create();
	m_effect = Sprite::create();
	m_label = LabelAtlas::create("0","images/Number/cannonlNumber.png",13,17,'0');
	m_label->setTag(1111);
	RefreshCanType();
	m_pSpirte->setAnchorPoint(Vec2(0.52f,0.0f));	
	m_pSpirte->setName("CannoSprite");
	G_MainGame->m_bottom->addChild(this,4);		
	m_pSpirte->setPosition(4,-70);	
	m_pSpirte->addChild(m_label);
	this->addChild(m_pSpirte,2);	//
	this->addChild(m_effect,3);	
	this->setAnchorPoint(Vec2(0.5f,0.5f));
	laserWaitingMusicId = 0;
	return true;
}

void Cannon::ChangeType(int cannonType)
{
	if(cannonType < 7)
		BUBBLE;
	
	if (cannonType == 7)
	{
		G_MainGame->SetProgress(100);
	}

	if (m_cannonType >= 7 && cannonType >= 7)
		return;

	m_nCachType = m_cannonType;
	CCLOG("haha:%d",cannonType) ;
	this->m_cannonType = cannonType;
	RefreshCanType();	
}

void Cannon::RefreshCanType()
{

	if(m_cannonType >= 7)
	{
		G_MainGame->specialReady = true;
		setRotation(0);
		m_label->setVisible(false);
		m_effect->setVisible(true);
		m_effect->stopAllActions();
		m_effect->setZOrder(3);
	}


	if(m_cannonType == 9)
	{
		m_effect->setPosition(0,-40);
		m_pSpirte->setTexture("cannonFrame/torpedoDown.png");
		m_effect->setTexture("images/Bullets/bullet013.png");
		PlayMusic("music/yuleiLaunch.mp3");
		m_effect->runAction(Sequence::create(MoveBy::create(2, Vec3(0,40,0)), CallFunc::create([]{G_MainGame->specialReady = false;}), NULL));
	}
	else if(m_cannonType == 7)
	{
		
		SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(Bomb::G_CanInfo[m_cannonType-1].m_Name.c_str());
		SpriteFrame* Frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("Laser_begin001.png");
		m_pSpirte->setSpriteFrame(Frame);
		m_effect->setSpriteFrame(Frame1);
		m_effect->setZOrder(1);
		PlayMusic("music/laserLaunch.mp3");
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
		this->runAction(MoveBy::create(0.01, Vec3(0,-40,0)));
		Animate* animat = Animate::create(animation);
		m_effect->runAction(RepeatForever::create(animat));
		this->runAction(Sequence::create(MoveBy::create(2, Vec3(0, 40, 0)), CallFunc::create([this](){
			G_MainGame->specialReady = false;
			if (LoadScene::duangOpen)
				this->laserWaitingMusicId = AudioEngine::play2d("music/laserWaitting.mp3", true);
		}), NULL));

	}
	else if(m_cannonType == 8)
	{
		SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(Bomb::G_CanInfo[m_cannonType-1].m_Name.c_str());
		SpriteFrame* Frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("Lighting_prepare001.png");
		m_pSpirte->setSpriteFrame(Frame);
		m_effect->setSpriteFrame(Frame1);
		m_effect->setPosition(0,90);

		char FramePng[50] = {0};
		for(int i = 1;i<4;i++)
		{
			sprintf(FramePng,"Lighting_prepare%03d.png",i);		 
			SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(FramePng);
			m_startReady.pushBack(tempFrame);
		}
		Animation* animation = Animation::createWithSpriteFrames(m_startReady,0.3f);
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		if(LoadScene::duangOpen)
		{
			PlayMusic("music/lightningLaunch.mp3");
			//laserWaitingMusicId = AudioEngine::play2d("music/laserWaitting.mp3", true);
		}
		Animate* animat = Animate::create(animation);
		m_effect->runAction(RepeatForever::create(animat));

		this->runAction(MoveBy::create(0.01, Vec3(0,-40,0)));
		this->runAction(Sequence::create(MoveBy::create(2, Vec3(0,40,0)), CallFunc::create([]{G_MainGame->specialReady = false;}), NULL));

	}
	else
	{
		m_label->setVisible(true);
		SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(Bomb::G_CanInfo[m_cannonType-1].m_Name.c_str());
		m_pSpirte->setSpriteFrame(Frame);
		m_effect->setVisible(false);
		char LoseNum[10]={0};
		sprintf(LoseNum,"%d",Bomb::G_CanInfo[m_cannonType-1].NeedGold);
		m_label->setString(LoseNum);
		if(Bomb::G_CanInfo[m_cannonType-1].NeedGold >=100)
		{
			m_label->setPosition(50,55);
		}
		else
		{
			m_label->setPosition(54,55);
		}

		m_pSpirte->setScale(0.1f,0.1f);
		auto ac = ScaleTo::create(0.4f,1.f,1.f);
		m_pSpirte->runAction(ac);
		m_pSpirte->setAnchorPoint(Vec2(0.52f, 0.0f));
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
	auto p = this->convertToWorldSpace(this->getPosition());
	Vec2 dir = ptTo1 - p;
	dir.normalize();
	Vec2 l(-1, 0);
	float d = l.dot(dir);
	m_rd = acosf(d) / M_PI * 180 - 90;
	this->setRotation(acosf(d) / M_PI * 180 - 90);
	this->m_dirPos = ptTo1;
}

void Cannon::fire()
{
	if(laserWaitingMusicId != 0)
	{
		AudioEngine::stop(laserWaitingMusicId);
		laserWaitingMusicId = 0;
	}

	auto p = this->convertToWorldSpace(this->getPosition());

	if (Player::getInstance()->getCurGold() < GetCanFee())
	{
		G_MainGame->ShowRmbWindow();
	}

	if(Player::getInstance()->getCurGold() >= GetCanFee() && this->getRotation() < 75 && this->getRotation() > -75 )
	{
		Player::getInstance()->decreaseGold(GetCanFee());
		if(LoadScene::duangOpen)
			AudioEngine::play2d(m_cannonType == 9?"music/yuleiFire.mp3":m_cannonType == 8?"music/lightningLaunch.mp3":"music/eft_fire.mp3");
		if(Bomb::G_CanInfo[m_cannonType-1].m_bulletNum == 2)
		{
			Bomb* pBullet1 = Bomb::createWithBombType(m_cannonType,1);
			pBullet1->shootTo(p, m_dirPos, m_rd, -1);
			Bomb* pBullet2 = Bomb::createWithBombType(m_cannonType,2);
			pBullet2->shootTo(p, m_dirPos, m_rd, 1);
		}
		else
		{
			if(m_cannonType == 9 || m_cannonType == 7|| m_cannonType == 8)
			{
				m_effect->setVisible(false);
			}

			Bomb* pBullet = Bomb::createWithBombType(m_cannonType,0);
			pBullet->shootTo(p, m_dirPos, m_rd, 0);
		}
	}
	else
	{
		PlayMusic("music/eft_firefail.mp3");
	}

	float tm = Bomb::G_CanInfo[G_MainGame->m_pCannon->getCanType()-1].speed * 0.5;
	auto scaleAction = ScaleTo::create(tm , 1,0.9);
	auto scaleAction2 = ScaleTo::create(tm , 1,1);
	m_pSpirte->runAction(Sequence::create(scaleAction, scaleAction2, NULL));

	if(Player::getInstance()->getCurGold() < GetCanFee())
	{
		for(int i = 5; i >= 0; --i)
		{
			if(Bomb::G_CanInfo[i].NeedGold < Player::getInstance()->getCurGold())
			{
				ChangeType(i + 1);
				break;
			}
		}
	}

}

void Cannon::BombCallBack()
{
	if(m_cannonType == 9|| m_cannonType == 7 || m_cannonType == 8)
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

Size Cannon::getCanSize()
{
	return this->m_pSpirte->getContentSize();
}

int Cannon::GetCanFee()
{
	return Bomb::G_CanInfo[m_cannonType-1].NeedGold;
}