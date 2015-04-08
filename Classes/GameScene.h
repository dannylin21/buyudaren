#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "cocos2d.h"
#include "FishPlayer.h"
#include "Cannon.h"
#include "Player.h"
#include "audio/include/AudioEngine.h"
#include "PropButton.h"

#include "base/CCEventKeyboard.h"
#include "base/CCEvent.h"
using namespace cocos2d::experimental;
class GameScene : public cocos2d::Layer
{
private:
	cocos2d::Sprite *m_exp,*m_Rollbg;
	cocos2d::LabelAtlas *m_levelLab,*m_countdown;
    cocos2d::Label *m_scrotext;
    int m_rolltm;
	void LoadPlayerInfo();
	void InitBackGroud();
	void initFishLayer();
	void LoadCannon();
	cocos2d::Rect cacleRect(cocos2d::Rect rc,float xr,float yr);
	void ChangeCanno(int tag);
	void BottomGold();
	void fire(float);
	void BackMusicOn();
	void InitTask();
	bool CheckFire();
	bool onContactBegin(cocos2d::PhysicsContact& contact);
    void RocallMsg();
    void CountDownReward();
public:
	bool m_tipOpen;
    bool m_ShowBuyMoney;
	CC_SYNTHESIZE(FishPlayer *,m_fishLayer,FishLayer);
	Cannon *m_pCannon;
	cocos2d::Vector<Bomb *> m_pBullets;
	cocos2d::Map<int,Fish *> m_pFishes;
	cocos2d::LabelAtlas *m_bottomgold;
    cocos2d::Label *m_btnbuy;
	cocos2d::MenuItemImage *m_bottomSprie,*m_bottomBuy;
	PropButton *m_oneCan,*m_secCan,*m_thrCan;
	bool specialReady;
	void setCannon(int stype);
	void MusicOn();
	virtual void onEnter();
	virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void ShowBuyMoney(bool IsShow);
public:
    
	static cocos2d::Scene* createScene();
	static GameScene* m_GameMain;
	static long GetTimeNow();
	cocos2d::Layer *m_UILayer,*m_mapLayer;
	virtual bool init();
	static void ShowGoldTip(int gold);
	void update(float dt);
	void updateGame(float dt);
	cocos2d::Layer *m_bottom;
	CREATE_FUNC(GameScene);
	void MainMenuCallBack(int Flag);
	void Explord(Bomb* bomb);
	void ExplordLight(Fish* fish);
	void ShowMenu();
	void rotMenu(int sFlag);
	void switchState(cocos2d::Sprite*, int flag);
	void ShowTask();
	void LaserExplord(Bomb* bomb);
	void FlashProgress();
	void SetProgress(float pro, float tm = 0.1);
	void InitProgress();
	void CheckCountNode();
	void InitCountDown();
	void ShowRmbWindow();
	cocos2d::Sprite* CreateLight();
	int goldTipTotal;
	cocos2d::MenuItemImage* settingMenu;
	cocos2d::MenuItemImage* homeMenu;
	cocos2d::MenuItemImage* BackMusicMenu;
	cocos2d::MenuItemImage* DuangMusicMenu;
	int currentGoldGet;
	int backMusic;
	bool flashingProgress;
	cocos2d::Sprite* flashProgress;
	cocos2d::Sprite* duangDis;
	cocos2d::Sprite* backDis;
	cocos2d::ProgressTimer* progressSprite;
	cocos2d::Node* CountNode;
	cocos2d::Node* RMBTipsNode;
	bool specialCanno;
    void RollText(float dt);
	void BombFishExplored(cocos2d::Vec2 pos);
};

#endif // __GAMESCENE_H__