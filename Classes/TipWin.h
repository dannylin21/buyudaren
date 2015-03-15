#ifndef __TIP_WIN__
#define __TIP_WIN__
#include "cocos2d.h"
#include "2d/CCParticleSystemQuad.h"

USING_NS_CC;

class TipWin : public cocos2d::Node
{
public:
	static void ShowTip();
	void CLosePop();
	bool Init();
private:
	void Get();
	void AddFlash();
	
};
#endif