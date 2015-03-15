#ifndef __H_PROPBUTTON_H_
#define __H_PROPBUTTON_H_
#include "cocos2d.h"
#include <string>

class PropButton : public cocos2d::Node
{
public:
	static PropButton* CreateButtonWidthPNG(std::string bg,int sType);
	virtual ~PropButton();
	void AddEffect();
private:
	cocos2d::Sprite *m_proppic;
	cocos2d::LabelAtlas* m_countLab;
	bool init(std::string bg,int sType);
	bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	bool CheckTouchMe(cocos2d::Touch *touch);
};

#endif