#ifndef __H_PLAYER_H_
#define __H_PLAYER_H_
#include "cocos2d.h"
#include "FileOperation.h"
#include "Global.h"

class Player:public cocos2d::Ref
{
public:
	static int GoldLevel[11];
	static Player* getInstance();
	virtual ~Player();
	void Init();
	void AddGold(int Increse);
	CC_SYNTHESIZE(int, m_gold, CurGold);
	CC_SYNTHESIZE(int, m_totalgold, TotalGold);
	CC_SYNTHESIZE(int, m_level, CLevel);
	CC_SYNTHESIZE(int,m_getReward,GetReward);
	void SavePlayInfo();
	SampleCallBack m_callBack;
private:
	cocos2d::ValueMapIntKey m_Canbullet;
	int m_PopGold;
	static Player* m_pInstance;
	Player();

};

class PlayerExp
{
private:
	cocos2d::Sprite *m_exp,*m_title;
	cocos2d::LabelAtlas* m_levelLab;
	cocos2d::Rect GetExpDis();
	float m_total;
public:
	void init(cocos2d::Layer *GameScene);
	void ChangeExp();
};

#endif

