#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"


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

typedef struct 
{
	int m_type;
	int num;
	int Path;
	int goType;
	int interal;
	int curtm;
	int delay;
	int lastborn;
    int pathov;
}FishPath,*PFishPath;

typedef struct
{
	cocos2d::Vec2 pStart;
	cocos2d::Vec2 pEnd;
}SetPath;

typedef struct
{
    int startindex;
    int endIndex;
}WaveExemple;


enum ExRewardType
{
	ExTNone,
	ExTLight,
	ExTBomb,
	ExTDown,
	ExTRocket,
    EXLUOPAN,
    EXREWARD
};

typedef struct
{
    cocos2d::Vec2 start;
    cocos2d::Vec2 endp;
    cocos2d::Vec2 stcntrl;
    cocos2d::Vec2 endcntrl;
    float startangle;
    float endangle;
    float times;
}BezierPath;

class Fish : public cocos2d::Node
 {
 private:
     cocos2d::Node *m_fly;
     ExRewardType m_rewardtype;
     int m_childReward;
	 void Resetborn();
	 static fishConf fishCOnfMap[26];
	 static SetPath PathArray[20];
	 void createFish(int sType);
 public:
    static WaveExemple WaveExe[20];
	static FishPath m_wavePath[110];
     static BezierPath m_beziePath[6];
	cocos2d::Vector<cocos2d::SpriteFrame*> m_array;
 	virtual ~Fish();
 	static Fish * createWithFishType(int sIndex);
	static Fish* createWithFishtType(int sType,int PathIndex,int GoType,int pathov,int BornType);
 	void BornFish();

	void getAutoPath();
	void getPath(int PathIndex=-1);
	void GoBezierPath(cocos2d::Vec2 start,cocos2d::Vec2 endp,cocos2d::Vec2 cntr1,cocos2d::Vec2 cntr2,float startAngle,float endAngle,int stime);

	void removeSelf();
	void showCaught(int DesHp);
	cocos2d::Vec2 GetPos();
	void ShowLighting();
	void TestPath();
	void GoDirPath(cocos2d::Vec2 ptStart,cocos2d::Vec2 ptEnd);
	void AddExReward(ExRewardType t);
	void ReCheckAllPosition();
     void initBubble(int flag);
     void GiveReward();
     void RewardLose(int flag);
 public:	 
	 CC_SYNTHESIZE(int,m_fishhp,Hp);
	 CC_SYNTHESIZE(int,m_fishMiss,FishMiss);
	 CC_SYNTHESIZE(int,m_fishGold,FishGold);
	 CC_SYNTHESIZE(int,_fishState,FishState);
	 CC_SYNTHESIZE(int,m_bornType,BornType);
	 CC_SYNTHESIZE(int,m_PathIndex,PathIndex);
     CC_SYNTHESIZE(int,m_goType,GoType);
     CC_SYNTHESIZE(int,m_pathov,Pathov);
     CC_SYNTHESIZE(int,m_index,Index);
	 CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, _fishSprite, FishSprite);//0 出生 1:活着 2：消失3：被抓
	 CC_SYNTHESIZE(int, m_fishIndex, FishIndex);
	 ExRewardType m_eRewardType;
	 Node*	m_pRewardNode;
 };
#endif // __FISH_H__