#ifndef __H_GLOBAL_H__
#define __H_GLOBAL_H__
#include <string>
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
}CanTypeConf;

typedef std::function<void(void)> SampleCallBack;
#endif