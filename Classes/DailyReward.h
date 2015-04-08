#ifndef __DAILY_REWARD__H
#define __DAILY_REWARD__H
#include "cocos2d.h"
typedef struct 
{
	int x;
	int y;
} HasGet;
class RewardDialog : public cocos2d::Node
{
public:
	static void PopReward(cocos2d::Layer* Parent,cocos2d::Sprite *Make);
	cocos2d::Sprite *m_make;
	static HasGet m_HaveGet[7];//*m_Had1,*m_Had2,*m_Had3,*m_Had4,*m_Had5,*m_Had6,*m_Had7;

	~RewardDialog();
private:
	virtual bool init() override;
	void CloseReward(Ref *sender);
	void LoadItem();
	void GetItem();
};
#endif