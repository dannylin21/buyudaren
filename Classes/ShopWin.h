#ifndef __H_SHOPWIN_H_
#define __H_SHOPWIN_H_
#include "cocos2d.h"
#include <string>
typedef struct
{
	std::string pic;//ico
	std::string m_gold;//ÊýÁ¿
	std::string m_rmb;//
	int m_ix;
	int m_iy;
	int m_gx;
	int m_gy;
	int m_px;
	int m_py;
} ShopItem;
class ShopWin : public cocos2d::Node
{
public:
	static void ShowShop();
private:
	bool Init();
	static ShopItem m_config[6];
	void BtnClick(int sindex);
};

#endif