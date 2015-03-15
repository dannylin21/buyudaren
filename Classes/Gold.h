#ifndef __GOLD_H__
#define __GOLD_H__
#include "cocos2d.h"

USING_NS_CC;

class Gold : public cocos2d::Node
{
public:
	Gold(void);
	~Gold(void);

	void ShowGold(Vec2 spos, Vec2 epos, float tm);
	void DeleteMe();
public:
	Vec3 targetPos;
	Vec3 oriPos;
private:
	Sprite* mGoldSprite;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_array;
};


#endif __GOLD_H__
