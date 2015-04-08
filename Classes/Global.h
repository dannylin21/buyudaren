#ifndef __H_GLOBAL_H__
#define __H_GLOBAL_H__
#include "cocos2d.h"
#include <string>
#include "publicAudio.h"
using namespace std;
typedef struct 
{
	std::string m_Name;
	int NeedGold;
	int m_hurt;
	int m_bulletNum;
	std::string m_bullet;
	std::string m_taileffect;
	int tailnum;
	int radio;
	float speed;
}CanTypeConf;

typedef std::function<void(void)> SampleCallBack;
#define UI_INDEX 99
#define MAP_INDEX 0
#define FISH_INDEX 1
#define MAKE_INDEX 100
#define MAX_INDEX 10000

class GameScene;
extern GameScene*			G_MainGame;

#define WAVESTATE		1
#define NORMALSTATE		0
#define NORMALBAZIE     3
#endif