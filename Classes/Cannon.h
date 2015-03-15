#ifndef _CANNON_H
#define _CANNON_H
#include "cocos2d.h"
#include "bomb.h"
#include "Global.h"

class GameScene;
class Cannon : public cocos2d::Node
{
public:
	static Cannon* createWithCannonType(int cannonType,GameScene *fishLayer);
	void RotatePoint(cocos2d::Vec2 ptTo);
	void ChangeType(int cannonType);
	void fire();
	virtual ~Cannon();
public:
	void AddBulletNum(int InCrease);
	void BombCallBack();
	CC_SYNTHESIZE(int, m_BulletCount, BulletCount);
private:
	cocos2d::Layer *m_layer;
	static CanTypeConf CanConf[9];
	cocos2d::Vector<Bomb*> m_bullets;
	cocos2d::Vector<cocos2d::SpriteFrame *> m_startReady;
	GameScene* m_pGameLayer;
	//1----6
	CC_SYNTHESIZE(int, m_cannonType, CanType);
	float m_fRotation;
	cocos2d::Sprite *m_pSpirte,*m_effect;
	cocos2d::Vec2 m_dirPos;
	cocos2d::LabelAtlas *m_label;
	void Rotation(float rotate);
	bool initWithCannonType();	
	void RefreshCanType();
private:
	Cannon(int cannonType,GameScene *gameLayer);
	
};

#endif