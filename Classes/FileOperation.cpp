#include "FileOperation.h"
#include <stdlib.h>
using namespace std;

USING_NS_CC;


void FileOperation::SaveRoleInfo(PPlayInfo sRoleInfo)
{
	string path = GetFilePath()+"/play.dat";
	FILE *fp = fopen(path.c_str(), "w");
	if(fp)
	{
		fwrite((char*)sRoleInfo,sizeof(PlayInfo),1,fp);
		fclose(fp);
	}
	return;
}

void FileOperation::ReadPlayInfo(std::string filePath,PPlayInfo RoleInfo)
{
	FILE *fp = fopen(filePath.c_str(), "r");
	if(fp&&!feof(fp))
	{
		fread(RoleInfo,sizeof(PlayInfo),1,fp);
	}
	else
	{
		CCLOG("can not open file %s", filePath.c_str());
		return;
	}
	fclose(fp);
}

string FileOperation::GetFilePath()
{
	return FileUtils::getInstance()->getWritablePath();
}