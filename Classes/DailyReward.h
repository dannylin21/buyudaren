#ifndef __DAILY_REWARD__H
#define __DAILY_REWARD__H
#include "cocos2d.h"
class RewardDialog : public cocos2d::Node
{
public:
	static void PopReward(cocos2d::Layer* Parent);
	~RewardDialog();
private:
	virtual bool init() override;
	void CloseReward(Ref *sender);
	void LoadItem();


};

#endif