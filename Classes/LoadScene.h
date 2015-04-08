#ifndef __H_LOADSCENE_H
#define __H_LOADSCENE_H
#include "cocos2d.h"

class LoadScene : public cocos2d::Layer
{
private:
	cocos2d::ProgressTimer *progresBar;
	cocos2d::Sprite *procebg;
	cocos2d::Sprite *progress;
	cocos2d::Layer *m_rewardLayer;
	cocos2d::Menu *m_menus;
	int m_musicid;
	void initBackGroud();
	void iniLoadIng();
	void update(float dt);
	void LoadMenu();
	void LoadRewardDaly();
	void switchState(cocos2d::Sprite* sp, int flag);
public:
    cocos2d::LabelAtlas *labelatlas;
	static cocos2d::Scene* createLoadScene();
	virtual bool init();
	CREATE_FUNC(LoadScene);
	static LoadScene *m_loadScene;
	static bool duangOpen;
	static bool backOpen;
	cocos2d::Sprite* duangDis;
	cocos2d::Sprite* backDis;
};
#endif