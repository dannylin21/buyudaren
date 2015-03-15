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
}PlayInfo,*PPlayInfo;
#pragma pack(pop)

class FileOperation 
{
public:
	static void ReadPlayInfo(std::string filePath,PPlayInfo RoleInfo);
	static std::string GetFilePath();
	static void SaveRoleInfo(PPlayInfo RoleInfo);
};

#endif