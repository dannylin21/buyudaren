#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "cocos2d.h"
#include "FishPlayer.h"
#include "Cannon.h"
#include "Player.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
class GameScene : public cocos2d::Layer
{
private:
	Cannon *m_pCannon;
	CC_SYNTHESIZE_RETAIN(FishPlayer*,m_FishPlayer,FishLayer);
private:
	cocos2d::Sprite *m_exp;
	cocos2d::LabelAtlas *m_levelLab;
	void LoadPlayerInfo();
	void InitBackGroud();
	void initFishLayer();
	void LoadCannon();
	cocos2d::Rect cacleRect(cocos2d::Rect rc,float xr,float yr);
	void ChangeCanno(int tag);
	void BottomGold();
	void fire(float);
	void BackMusicOn();
public:
	cocos2d::Vector<Bomb *> m_pBullets;
	cocos2d::Vector<Fish *> m_pFishes;
	cocos2d::LabelAtlas *m_bottomgold;
	cocos2d::MenuItemImage *m_bottomSprie;
	void setCannon(int stype);
	void MusicOn();
	virtual void onEnter();
	virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
public:
	static cocos2d::Scene* createScene();
	static bool duangOpen;
	static GameScene* m_GameMain;
	cocos2d::Layer *m_UILayer,*m_mapLayer;
	virtual bool init();
	void update(float dt);
	void updateGame(float dt);
	cocos2d::Layer *m_bottom;
	CREATE_FUNC(GameScene);
	void MainMenuCallBack(int Flag);
};

#endif // __GAMESCENE_H__