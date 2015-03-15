#ifndef __FISHPLAYER_H__
#define __FISHPLAYER_H__
#include "cocos2d.h"
#include "Fish.h"
class GameScene;
class FishPlayer : public cocos2d::Layer
{
private:
	int m_GameState;
	int m_duration;
private:
	int m_curfishnum;
	int m_curType;
	bool AllDead;
	GameScene* m_sence;
	void ChangeState();
public:	
	virtual bool init();
	void FishTick(float dt);
public:
	void AddFish(int fishtype,int Count);
	void reset_fish();
	void fishDead(Fish *fish);
	void start();
	static FishPlayer* createFishPlayer(GameScene *Scene);
	CREATE_FUNC(FishPlayer);
};




#define DOORONE_DURTIME 20
#define DOORSEC_DURTIME 20
#endif // __FISHPLAYER_H__