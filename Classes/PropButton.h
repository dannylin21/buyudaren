#ifndef __H_PROPBUTTON_H_
#define __H_PROPBUTTON_H_
#include "cocos2d.h"
#include <string>

class PropButton : public cocos2d::Node
{
public:
	static PropButton* CreateButtonWidthPNG(std::string bg,int sType);
	virtual ~PropButton();
	void AddEffect(bool add);
	int GetPropNum();
	void addPropNum(int increase);
	void Tick();
private:
    cocos2d::LabelTTF *rmb;
    cocos2d::Node *m_bgLayer;
	CC_SYNTHESIZE(int, m_type, BtnType);
	int m_propNum;
	int m_plashtm;
	void BuyCan(int Rmb);
	cocos2d::Sprite *m_flash;
	cocos2d::Sprite *m_proppic;
	cocos2d::Sprite *m_duihuan;
	cocos2d::LabelAtlas* m_countLab;
	bool init(std::string bg,int sType);
	bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	bool CheckTouchMe(cocos2d::Touch *touch);
};

#endif