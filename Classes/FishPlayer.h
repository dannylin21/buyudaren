#ifndef __FISHPLAYER_H__
#define __FISHPLAYER_H__
#include "cocos2d.h"
#include "Fish.h"



class FishPlayer : public cocos2d::Layer
{
private:
	int m_duration,m_bazieftype,m_baziefcount,m_bazieBornNum,m_baziePath;
    static int m_beziefishtype[3];
    static int m_beziefishcount[3];
	CC_SYNTHESIZE_READONLY(int, m_GameState, GameState);
private:
    int m_fishIndex;
	int m_curfishnum;
	int m_curType;
    int m_waveindex;
    int m_waveBornEnd,m_waveinit;
    bool m_waveEnd;
	std::vector<PFishPath> m_waveData;
	cocos2d::Sprite *m_wavepic;
	void hideWave();
	void waveStart(int CountDown);
	void waveBornFish();
	void Born(PFishPath Fish);
    void clearWave();
    int GetMaxFishIndex();
    void BornBazie();
    void BornBazie(float dt);
    void WavePicStart();
    
    void WaveBorn();
    
    void NormalBorn();
public:
    bool m_bornReward;
	virtual bool init();
	void FishTick(float dt);
public:
	void AddFish(int fishtype,int Count);
    void DeCreaseBezia();
	void reset_fish();
	void fishDead(int fishIndex,int BornType);
	void start();
	static FishPlayer* createFishPlayer();
	CREATE_FUNC(FishPlayer);
};
#define DOORONE_DURTIME 360
#define DOORWAVE_DURTIME 60
#endif // __FISHPLAYER_H__