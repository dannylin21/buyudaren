#include "bomb.h"
#include "GameScene.h"
#include "Cannon.h"

USING_NS_CC;
using namespace std;

 Bomb* Bomb::createWithBombType(CanTypeConf &canno, GameScene *gameScene,float seq,cocos2d::Node *pCannon)
 {
	 Bomb* pbombBullet = new Bomb();
	 pbombBullet->setCanno(canno);
	 pbombBullet->m_cannoobj = pCannon;
	 if(pbombBullet && pbombBullet->initWithBulletType(gameScene,seq))
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


 bool Bomb::initWithBulletType(GameScene* gameLayer,float seq)
 {
	 m_bCaught = false;
	 this->setGameLayer(gameLayer);
	 string bulletPng = "images/Bullets/"+m_canno.m_bullet;
	 Texture2D *texture = TextureCache::getInstance()->addImage(bulletPng.c_str());
	 this->setSpriteBullet(Sprite::createWithTexture(texture));
	 m_pGameLayer->getFishLayer()->addChild(m_pSpriteBullet,3);
	 m_pSpriteBullet->setAnchorPoint(Vec2(0.5f,0));
	 m_pSpriteBullet->setPosition(m_pGameLayer->getFishLayer()->getContentSize().width * 0.5+5,46);

	 char TailName[50]={0};
	 for (int i=1;i<=m_canno.tailnum;i++)
	 {
		 sprintf(TailName,m_canno.m_taileffect.c_str(),i);		 
		 SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(TailName);
		 if(tempFrame != NULL)
		 {
			 taileff.pushBack(tempFrame);
		 }		
	 }	

	 //Animation* animation = Animation::createWithSpriteFrames(taileff,0.3f);
	 //animation->setDelayPerUnit(0.2f);
	 //animation->setRestoreOriginalFrame(true);
	 //Animate* animat = Animate::create(animation);
	 //m_pSpriteBullet->runAction(animat);

	 m_pGameLayer->m_pBullets.pushBack(this);
	 char FramePng[50] = {};
	 SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Cannon_03bomb001.png");
	 this->m_pSpritePeng = Sprite::createWithSpriteFrame(Frame);
	 for (int i=1;i < 9;i++)
	 {
		 sprintf(FramePng,"Cannon_03bomb%03d.png",i);		 
		 SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(FramePng);
		 if(tempFrame != NULL)
		 {
			 pengVec.pushBack(tempFrame);
		 }	
	 }
	 m_pGameLayer->getFishLayer()->addChild(this->m_pSpritePeng,3);
	 
	 this->m_pSpritePeng->setVisible(false);
	
	 return true;
 }

void Bomb::removeSelf()
{
	((Cannon*)m_cannoobj)->BombCallBack();
	CCLOG("bullte:%d",this->getGameLayer()->m_pBullets.size());
	this->getGameLayer()->m_pBullets.eraseObject(this);
	m_pSpriteBullet->removeFromParentAndCleanup(true);
	this->m_pSpritePeng->removeFromParentAndCleanup(true);
	if(this->m_pariticle)
	{
		this->getGameLayer()->removeChild(m_pariticle);
		//this->m_pariticle->removeFromParentAndCleanup(true);
	}
	this->release();	
}

void Bomb::shootTo(cocos2d::Vec2 ptTo1)
{
	Vec2 ptTo = Director::getInstance()->convertToGL(ptTo1);
	Vec2 ptFrom = m_pSpriteBullet->getPosition();
	float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x);
	float rotation = angle / M_PI * 180.0f;
	m_pSpriteBullet->setRotation(90.0f - rotation);
	Size size = Director::getInstance()->getWinSize(); 
	Vec2 tar = Vec2(ptFrom.x + size.width * cosf(angle), ptFrom.y + size.width * sinf(angle)); 
	auto *moveto = MoveTo::create(1.0f,tar);
	auto *callFunc = CallFunc::create(std::bind(&Bomb::removeSelf,this));	
	auto *sequence = Sequence::create(moveto,callFunc,NULL);
	m_pSpriteBullet->runAction(sequence);
}

void Bomb::explode()
{
	m_bCaught = true;
	this->m_pSpriteBullet->stopAllActions();
	this->m_pSpriteBullet->setVisible(false);
	this->m_pSpritePeng->setVisible(true);
	this->m_pSpritePeng->setPosition(m_pSpriteBullet->getPosition());
	if(pengVec.size() > 0)
	{
		CCLOG("frame:%d",pengVec.size());
		Animation* animation = Animation::createWithSpriteFrames(pengVec,0.3f);
		animation->setDelayPerUnit(0.04f);
		animation->setRestoreOriginalFrame(true);
		//ScaleTo *scale = ScaleTo::create(0.3f, 1.25f);
		Animate* animat = Animate::create(animation);
		CallFunc *call = CallFunc::create(std::bind(&Bomb::removeSelf,this));		
		auto *sq= Sequence::create(animat,call,NULL);
		this->m_pSpritePeng->runAction(sq);
		
	}
	CCLOG("____________papapapap_________________");
}
Bomb::~Bomb()
{
	CCLOG("des Bomb");
}

int Bomb::getHurt()
{
	return this->m_canno.m_hurt;
}