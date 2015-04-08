#ifndef __H_LUOPAN_H_
#define __H_LUOPAN_H_
#include "cocos2d.h"
#include <string>
typedef struct 
{
	std::string pic;
}LpWConf;

typedef struct 
{
	std::string num;
}LpNConf;

typedef struct
{
	int x;
	int y;
	float rote;
}LpPos;

typedef struct 
{
	float w_angle;
	float n_angle;
}LpRote;

class CLuoPan:public cocos2d::Node
{
public:
    int m_freecount;
    bool m_first;
	static void ShowLuoPan();
    static void ShowLuoPan(int FreeNum);
private:
	bool Init(int FreeNum);
	cocos2d::Sprite *make;
	cocos2d::Node *m_outbg,*m_inBg,*m_fly;

	void ClickBtn();
	static LpWConf m_luopic[9];
	static LpNConf m_itemnum[9];
	static LpPos LpWpos[9];
	static LpPos LpNpos[9];
	static LpRote LpResult[10];
	void initLuow();
	int CurGetIndex;
	void calResult();
	void AddResult(int index);
	void GiveItem(int Result);
};



#endif