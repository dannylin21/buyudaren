#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__
#include "cocos2d.h"

#include <string>

#pragma pack(push)
#pragma pack(1)
typedef struct 
{
	int gold;
	int level;
	int hadGold;
	int GetReward;
	int CanOne;
	int CanSec;
	int CanThr;
    int m_luonum;
    int m_smallmisstime;
    int m_mainmissiontm;
    int m_mainmissid;
}PlayInfo,*PPlayInfo;

typedef struct
{
    int mainID;
    int MainState;
    int MainTm;
    int SamlID;
    int SamlTm;
    int SamlState;
}Task,*PTask;

#pragma pack(pop)

class FileOperation 
{
public:
	static void ReadPlayInfo(std::string filePath,PPlayInfo RoleInfo);
	static std::string GetFilePath();
	static void SaveRoleInfo(PPlayInfo RoleInfo);
    static void ReadTask(PTask task);
    static void SaveTask(PTask task);
};

#endif