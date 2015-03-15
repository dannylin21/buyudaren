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
	void initBackGroud();
	void iniLoadIng();
	void update(float dt);
	void LoadMenu();
	void LoadRewardDaly();
public:
	static cocos2d::Scene* createLoadScene();
	virtual bool init();
	CREATE_FUNC(LoadScene);
};
#endif