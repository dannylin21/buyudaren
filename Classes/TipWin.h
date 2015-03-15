#ifndef __TIP_WIN__
#define __TIP_WIN__
#include "cocos2d.h"
#include "2d/CCParticleSystemQuad.h"

USING_NS_CC;

class TipWin : public cocos2d::Node
{
public:
	static void ShowTip(int stype);
	void CLosePop();
	bool Init();
private:
	CC_SYNTHESIZE(int,m_type,PopType);
	int m_curGold;
	void Get();
	void AddFlash();
	void LoadGift();
};
#endif