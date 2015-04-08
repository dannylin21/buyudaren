#ifndef __TIP_WIN__
#define __TIP_WIN__
#include "cocos2d.h"


class TipWin : public cocos2d::Node
{
public:
	static void ShowTip(int stype, bool GlobalOpen);
	static void ShowTip(int stype);
	void CLosePop();
	bool Init(bool GlobalOpen);
private:
	CC_SYNTHESIZE(int,m_type,PopType);
	int m_curGold;
	void Get();
	void AddFlash();
	void LoadGift();
	void Show12();
	void CloseAnimation();
};
#endif