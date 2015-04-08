#include "bomb.h"
#include "GameScene.h"
#include "Cannon.h"
#include "LoadScene.h"

USING_NS_CC;
using namespace std;

CanTypeConf Bomb::G_CanInfo[9] = {
	{"cannon001.png" , 50 , 100 ,1,"bullet001.png","Laser_prepare%03d.png",0,0,0.1f},
	{ "cannon002.png", 100, 100 ,2, "bullet001.png", "Torpedo_launch%03d.png", 0, 0, 0.15f },
	{ "cannon003.png", 150, 200 ,1, "bullet002.png", "Torpedo_launch%03d.png", 0, 60, 0.2f },
	{ "cannon004.png", 250, 300 ,1, "bullet002.png", "Lightning_launch%03d.png", 0, 60, 0.2f },
	{ "cannon005.png", 400, 450 ,1, "bullet003.png", "Lightning_catch%03d.png", 0, 85, 0.3f },
	{ "cannon006.png", 500, 600 ,1, "bullet003.png", "Lightning_catch%03d.png", 0, 85, 0.3f },
	{ "laster001.png", 0  , 10000, 1, "bullet003.png", "Laser_launch%03d.png", 2, 0, 0 },
	{ "lightning001.png", 0, 10000, 1, "bullet003.png", "Lightning_catch%03d.png", 4, 0, 0},
	{ "torpedoDown.png", 0, 10000, 1, "bullet013.png", "Torpedo_launch%03d.png", 2, 0, 0 }
};


 Bomb* Bomb::createWithBombType(int CanType,int sIndex)
 {
	 Bomb* pbombBullet = new Bomb();
	 if(pbombBullet && pbombBullet->initWithBulletType(CanType,sIndex))
	 {			
		 pbombBullet->autorelease();
		 return pbombBullet;
	 }
	 else
	 {
		 CC_SAFE_DELETE(pbombBullet);
		 return NULL;
	 }
 }


 bool Bomb::initWithBulletType(int CanType,int sIndex)
 {
	 m_bCaught = false;
	 cannoType = CanType;
	 if(CanType == 8)
	 {
		 SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Lighting_prepare001.png");
		 this->setSpriteBullet(Sprite::createWithSpriteFrame(Frame));
	 }
	 else if(CanType == 7)
	 {
		 SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Laser_launch001.png");
		 this->setSpriteBullet(Sprite::createWithSpriteFrame(Frame));
	 }
	 else
	 {
		 string bulletPng = "images/Bullets/"+G_CanInfo[CanType-1].m_bullet;
		 Texture2D *texture = TextureCache::getInstance()->addImage(bulletPng.c_str());
		 this->setSpriteBullet(Sprite::createWithTexture(texture));
	 }
	 G_MainGame->addChild(this,15);
	 this->setPosition(-5,25);
	 switch(sIndex)
	 {
	 case 0:
		 m_pSpriteBullet->setPosition(10,49);
		 break;
	 case 1:
		 m_pSpriteBullet->setPosition(-2,49);
		 break;
	 case 2:
		 m_pSpriteBullet->setPosition(15,49);
		 break;
	 }

	 char TailName[50]={0};
	 for (int i=1;i<=G_CanInfo[CanType-1].tailnum;i++)
	 {
		 sprintf(TailName,G_CanInfo[CanType-1].m_taileffect.c_str(),i);		 
		 SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(TailName);
		 if(tempFrame != NULL)
		 {
			 taileff.pushBack(tempFrame);
		 }		
	 }	
	 if(taileff.size() > 0)
	 {
		 Animation* animation = Animation::createWithSpriteFrames(taileff,0.3f);
		 animation->setDelayPerUnit(0.2f);
		 animation->setRestoreOriginalFrame(true);
		 Animate* animat = Animate::create(animation);
	 }
	 G_MainGame->m_pBullets.pushBack(this);
	 char FramePng[50] = {};
	 if(G_MainGame->m_pCannon->getCanType() == 8)
	 {
		 SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Lightning_catch001.png");
		 for (int i=1;i < 5;i++)
		 {
			 sprintf(FramePng,"Lightning_catch%03d.png",i);
			 SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(FramePng);
			 if(tempFrame != nullptr)
			 {
				 pengVec.pushBack(tempFrame);
			 }
		 }
	 }
	 else
	 {
		 SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Cannon_03bomb001.png");
		 for (int i=1;i < 9;i++)
		 {
		 	 sprintf(FramePng,"Cannon_03bomb%03d.png",i);		 
		 	 SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(FramePng);
		 	 if(tempFrame != NULL)
		 	 {
		 		 pengVec.pushBack(tempFrame);
		 	 }	
		 } 
	 }
	 this->addChild(m_pSpriteBullet);
	 return true;
 }

void Bomb::removeSelf()
{
	G_MainGame->m_pCannon->BombCallBack();
	CCLOG("bullte:%d",G_MainGame->m_pBullets.size());
	G_MainGame->m_pBullets.eraseObject(this);
	if(this->m_pariticle)
	{
		this->removeChild(m_pariticle);
	}
	this->removeFromParentAndCleanup(true);	
}



int Bomb::getType()
{
	return cannoType;
}

void Bomb::LightDis()
{
	G_MainGame->specialCanno = false;
	G_MainGame->currentGoldGet += G_MainGame->goldTipTotal;
	G_MainGame->SetProgress(G_MainGame->currentGoldGet / 200,1.5);
	if (G_MainGame->goldTipTotal > 1000)
	{
		GameScene::ShowGoldTip(G_MainGame->goldTipTotal);
		G_MainGame->goldTipTotal = 0;
	}
	G_MainGame->m_pCannon->ChangeType(G_MainGame->m_pCannon->m_nCachType);
	
	removeSelf();
}

void Bomb::LaserDis()
{
	G_MainGame->flashingProgress = false;
	G_MainGame->currentGoldGet = 0;
	G_MainGame->SetProgress(0,  1.5);
	G_MainGame->specialCanno = false;
	if (G_MainGame->goldTipTotal > 1000)
	{
		GameScene::ShowGoldTip(G_MainGame->goldTipTotal);
		G_MainGame->goldTipTotal = 0;
	}
	G_MainGame->m_pCannon->ChangeType(G_MainGame->m_pCannon->m_nCachType);
	removeSelf();
}

void Bomb::rocketDis()
{
	G_MainGame->specialCanno = false;
	G_MainGame->Explord(this);
	G_MainGame->currentGoldGet += G_MainGame->goldTipTotal;
	G_MainGame->SetProgress(G_MainGame->currentGoldGet / 200,1.5);
	if (G_MainGame->goldTipTotal > 1000)
	{
		GameScene::ShowGoldTip(G_MainGame->goldTipTotal);
		G_MainGame->goldTipTotal = 0;
	}
	G_MainGame->m_pCannon->ChangeType(G_MainGame->m_pCannon->m_nCachType);
	removeSelf();
}

extern float offsetx, offsety;

void Bomb::shootTo(cocos2d::Vec2 ptFrom, cocos2d::Vec2 ptTo1,float dg, int d)
{
	this->setRotation(dg);
	Vec2 dir = ptTo1 - ptFrom;
	dir.normalize();
	MoveTo *moveto;
	Vec2 startPos = ptFrom + dir * 20;
	Vec3 z(0, 0, 1);
	Vec3 dd(dir.x, dir.y, 0);
	z.cross(dd);
	Vec2 dz(z.x, z.y);
	if (d != 0)
	{
		startPos = startPos + dz * (d * 20) + dz * 5;
		this->setPosition(startPos);
		moveto = MoveTo::create(1.5f, startPos + dir * 1000);
	}
	else
	{
		startPos = startPos + dz * 8;
		this->setPosition(startPos);
		moveto = MoveTo::create(1.5f, ptFrom + dir * 1000);
	}

#if 0
	auto dn = DrawNode::create();
	dn->drawPoint(Vec2(0,0), 10, Color4F(0,1,0,1));
	m_pSpriteBullet->addChild(dn);
	dn->setPosition(0,0);

	auto dn2 = DrawNode::create();
	auto bd = this->getBoundingBox();
	bd.origin = Vec2(0,0);
	dn2->drawRect(Vec2(bd.getMinX(), bd.getMinY()), Vec2(bd.getMinX(), bd.getMaxY()),Vec2(bd.getMaxX(), bd.getMaxY()),Vec2(bd.getMaxX(), bd.getMinY()), Color4F(1,1,0,1));
	m_pSpriteBullet->addChild(dn2);
#endif

	auto *callFunc = CallFunc::create([this]{this->removeSelf();});
	Sequence *sequence = nullptr;
	if(G_MainGame->m_pCannon->getCanType() == 7)
	{
		if(LoadScene::duangOpen)
			AudioEngine::play2d("music/eft_laser.mp3");
		char BullteHead[50]={0};
		Vector<SpriteFrame *> HeadVect;
		for(int i=1;i<3;i++)
		{
			sprintf(BullteHead,"Laser_launch%03d.png",i);
			SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(BullteHead);
			HeadVect.pushBack(tempFrame);
		}
		if(HeadVect.size() > 0)
		{
			Animation* headAni = Animation::createWithSpriteFrames(HeadVect,0.3f,2);
			headAni->setDelayPerUnit(0.2f);
			headAni->setRestoreOriginalFrame(true);
			Animate* headnit = Animate::create(headAni);
			m_pSpriteBullet->runAction(RepeatForever::create(headnit));
			this->setPosition(startPos + dir * 320);
			auto tt = MoveBy::create(2, Vec2(0, 0));
			auto *callFunc = CallFunc::create(std::bind(&Bomb::LaserDis, this));
			sequence = Sequence::create(tt, callFunc, NULL);
		}
	}
	else if (G_MainGame->m_pCannon->getCanType() == 9)
	{
		auto mt = MoveTo::create(1.2, ptTo1);
		auto *callFunc = CallFunc::create(std::bind(&Bomb::rocketDis, this));


		SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Torpedo_launch001.png");
		auto bb = Sprite::createWithSpriteFrame(Frame);
		Vector<SpriteFrame *> HeadVect;
		char pngName[1024];
		for (int i = 1; i <= 2; i++)
		{
			sprintf(pngName, "Torpedo_launch%03d.png", i);
			SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
			HeadVect.pushBack(tempFrame);
		}
		if (HeadVect.size() > 0)
		{
			Animation* headAni = Animation::createWithSpriteFrames(HeadVect, 0.3f);
			headAni->setDelayPerUnit(0.2f);
			headAni->setRestoreOriginalFrame(true);
			Animate* headnit = Animate::create(headAni);
			bb->runAction(RepeatForever::create(headnit));
			bb->setPosition(Vec2(10, -50));
			this->addChild(bb);
		}
		sequence = Sequence::create(mt, callFunc, NULL);
	}
	else if(G_MainGame->m_pCannon->getCanType() == 8)
	{
		auto *callFunc = CallFunc::create(std::bind(&Bomb::LightDis, this));
		sequence = Sequence::create(moveto, callFunc, NULL);
	}
	else
	{
		sequence = Sequence::create(moveto,callFunc,NULL);
		char bombPar[100];
		sprintf(bombPar, "particles/fire%02d.plist", G_MainGame->m_pCannon->getCanType());
		ParticleSystem *m_pariticle1=ParticleSystemQuad::create(bombPar);
		m_pariticle1->setPosition(Vec2(8,17) + dz * -7 * d);
		m_pariticle1->setPositionType(ParticleSystem::PositionType::FREE);
		m_pariticle1->setAutoRemoveOnFinish(true);
		this->addChild(m_pariticle1);
	}
	this->runAction(sequence);
}


void Bomb::explode()
{
	m_bCaught = true;
	if(G_MainGame->m_pCannon->getCanType() >= 7 )
	{

	}
	else
	{
		this->stopAllActions();
		if(pengVec.size() > 0)
		{
			CCLOG("frame:%d",pengVec.size());
			Animation* animation = Animation::createWithSpriteFrames(pengVec,0.f);
			animation->setDelayPerUnit(0.04f);
			animation->setRestoreOriginalFrame(true);
			Animate* animat = Animate::create(animation);
			CallFunc *call = CallFunc::create(std::bind(&Bomb::removeSelf,this));		
			auto *sq= Sequence::create(animat,call,NULL);
			this->m_pSpriteBullet->runAction(sq);

		}
		//this->removeAllChildren();
		char bombPar[100];
		sprintf(bombPar, "particles/bomb%02d.plist", G_MainGame->m_pCannon->getCanType());
		ParticleSystem *m_pariticle1=ParticleSystemQuad::create(bombPar);
		m_pariticle1->setPosition(90,103);
		m_pariticle1->setPositionType(ParticleSystem::PositionType::FREE);
		m_pariticle1->setAutoRemoveOnFinish(true);
		m_pSpriteBullet->addChild(m_pariticle1);
		auto mv = MoveBy::create(0.3, Vec3(0,0,1));
		CallFunc *call = CallFunc::create([this]{this->removeSelf();});
		this->runAction(Sequence::create(mv,call,NULL));
		
	}
}
Bomb::~Bomb()
{
	CCLOG("des Bomb");
}

int Bomb::getHurt()
{
	return G_CanInfo[G_MainGame->m_pCannon->getCanType()-1].m_hurt;
}

Vec2 Bomb::getPos()
{
	Vec2 pos = this->getPosition();
	//CCLOG("%f______%f",pos.x,pos.y);
	return this->getPosition();
}


Rect Bomb::GetBox()
{
	return this->getBoundingBox();
}