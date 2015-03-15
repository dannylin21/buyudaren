#ifndef __BOMB_H__
#define __BOMB_H__
#include "cocos2d.h"

#include "Global.h"

class GameScene;
class Bomb : public cocos2d::Object
{
public:
	static Bomb *createWithBombType(CanTypeConf &canno, GameScene *gameScene,float seq,cocos2d::Node *pCannon);
	CC_SYNTHESIZE(int, m_nBulletType, BulletType);
	CC_SYNTHESIZE_READONLY(bool, m_bCaught, Caught);

	void shootTo(cocos2d::Vec2 ptTo);
	void explode();
	int getHurt();
	virtual ~Bomb();
private:
	cocos2d::Node *m_cannoobj;
	cocos2d::Vector<cocos2d::SpriteFrame *> taileff;
	cocos2d::Vector<cocos2d::SpriteFrame *> pengVec;
	CC_SYNTHESIZE(GameScene *, m_pGameLayer, GameLayer);
	CC_SYNTHESIZE(cocos2d::Sprite *, m_pSpriteBullet, SpriteBullet);
	CC_SYNTHESIZE(cocos2d::Sprite *,m_pSpritePeng, SpritePeng);
	CC_SYNTHESIZE(CanTypeConf,m_canno,Canno);
	CC_SYNTHESIZE(cocos2d::ParticleSystem *,m_pariticle,Pariticle);
	void removeSelf();
	bool initWithBulletType(GameScene *gameLayer,float seq);
};
#endif