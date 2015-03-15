#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"

class FishPlayer;
struct fishConf
{
	int m_type;
	int m_catch;
	int m_swim;
	int m_hp;
	int m_miss;
	int m_mingold;
	int m_maxgold;
};
 class Fish : public cocos2d::Node
 {
 private:
	 FishPlayer *m_palyer;
	 void Resetborn();
	 static fishConf fishCOnfMap[26];
 public:
	cocos2d::Vector<cocos2d::SpriteFrame*> m_array;
 	virtual ~Fish();
 	static Fish * createWithFishType(int sIndex,FishPlayer *Player);

 	void BornFish(FishPlayer *gameLayer);

	void getAutoPath();
	void getPath();
	void movePath(cocos2d::Vec2 start,cocos2d::Vec2 endp,float startAngle,float endAngle,int time);

	void removeSelf();
	void showCaught(int DesHp);

 public:	 
	 CC_SYNTHESIZE(int,m_fishhp,Hp);
	 CC_SYNTHESIZE(int,m_fishMiss,FishMiss);
	 CC_SYNTHESIZE(int,m_fishGold,FishGold);
	 CC_SYNTHESIZE(int,_fishState,FishState);
	 CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, _fishSprite, FishSprite);//0 出生 1:活着 2：消失3：被抓
	 CC_SYNTHESIZE(int, m_fishIndex, FishIndex);
 };
#endif // __FISH_H__