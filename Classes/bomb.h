#ifndef __BOMB_H__
#define __BOMB_H__
#include "cocos2d.h"
#include "Global.h"

class Bomb : public cocos2d::Node
{
public:
	static CanTypeConf G_CanInfo[9];
	static Bomb *createWithBombType(int CanType,int sIndex);
	CC_SYNTHESIZE_READONLY(bool, m_bCaught, Caught);
	void shootTo(cocos2d::Vec2 ptFrom, cocos2d::Vec2 ptTo,float dg, int d = 0);
	void explode();
	int getHurt();
	int getType();
	virtual ~Bomb();
	cocos2d::Vec2 getPos();
	cocos2d::Rect GetBox();
	int cannoType;
private:
	cocos2d::Vector<cocos2d::SpriteFrame *> taileff;
	cocos2d::Vector<cocos2d::SpriteFrame *> pengVec;
	CC_SYNTHESIZE(cocos2d::Sprite *, m_pSpriteBullet, SpriteBullet);
	CC_SYNTHESIZE(cocos2d::Sprite *,m_pSpritePeng, SpritePeng);
	CC_SYNTHESIZE(cocos2d::ParticleSystem *,m_pariticle,Pariticle);
	void removeSelf();
	bool initWithBulletType(int CanType,int sIndex);
	void LaserDis();
	void rocketDis();
	void LightDis();
};
#endif