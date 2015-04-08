#ifndef _CANNON_H
#define _CANNON_H
#include "cocos2d.h"
#include "bomb.h"

class Cannon : public cocos2d::Node
{
public:
	static Cannon* createWithCannonType(int cannonType);
	void RotatePoint(cocos2d::Vec2 ptTo);
	void ChangeType(int cannonType);
	void fire();
	virtual ~Cannon();
public:
	void AddBulletNum(int InCrease);
	void BombCallBack();
	int GetCanFee();
	CC_SYNTHESIZE(int, m_BulletCount, BulletCount);
	cocos2d::Size getCanSize();
private:
	float m_roteangle;
	cocos2d::Layer *m_layer;
	cocos2d::Vector<Bomb*> m_bullets;
	cocos2d::Vector<cocos2d::SpriteFrame *> m_startReady;
	//1----6
	CC_SYNTHESIZE(int, m_cannonType, CanType);
	float m_fRotation;
public:
	cocos2d::Sprite *m_pSpirte,*m_effect;
	cocos2d::Vec2 m_dirPos;
	int m_nCachType;
	float m_rd;
	int laserWaitingMusicId;
	cocos2d::LabelAtlas *m_label;
	void Rotation(float rotate);
	bool initWithCannonType();	
	void RefreshCanType();
private:
	Cannon(int cannonType);
	
};

#endif