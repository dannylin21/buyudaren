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
	void AddGold(int Increse,int AddType);
	void decreaseGold(int decrease);
	CC_SYNTHESIZE(int, m_gold, CurGold);
	CC_SYNTHESIZE(int, m_totalgold, TotalGold);
	CC_SYNTHESIZE(int, m_level, CLevel);
	CC_SYNTHESIZE(int,m_getReward,GetReward);

	void SavePlayInfo();
	SampleCallBack m_callBack;
	CC_SYNTHESIZE(bool, m_loginGet,LoginGet);
    CC_SYNTHESIZE(long, m_logintm, LoginTime);
    CC_SYNTHESIZE(int ,m_luonum,LuoPanNum);
private:

	CC_SYNTHESIZE(int, m_canone, CanOneNum);
	CC_SYNTHESIZE(int, m_cansec, CanSecNum);
	CC_SYNTHESIZE(int,m_canthr,CanThrNum);


    CC_SYNTHESIZE(int, m_mainmissid, MainMissID);
	CC_SYNTHESIZE(int, m_mainmisstm, MainMissTm);
	CC_SYNTHESIZE(int,m_othermissid,OtherMissID);
    CC_SYNTHESIZE(int,m_othermisstm,OtherMissTM);
    
	cocos2d::ValueMapIntKey m_Canbullet;
	int m_PopfreeGold,m_poprmb;
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

