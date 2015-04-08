#ifndef __TASK_MGR_H
#define __TASK_MGR_H
#include "cocos2d.h"
USING_NS_CC;

typedef struct
{
    int missionid;
    int missType;
    int missiontm;
    int missNeed;
    std::string missdes;
    int nextmissid;
    int rewardType;
    std::string RewardPic;
    std::string numpic;
    int rewardnum;
    int missState;
    std::string ico;
    int missCondit;
}Mission,*PMission;
class taskMgr : public cocos2d::Node
{
public:
    static taskMgr* getInstance();
    void GetReward();
    void Tick();
    void Hook(int behavior,int behParam);
    virtual ~taskMgr();
private:
    bool m_openMain,m_openSaml;
    cocos2d::ParticleSystemQuad *m_Partic;
    cocos2d::MenuItemImage *m_MainTaskICO;
    cocos2d::LabelAtlas *m_MainTaskLab;
    int savetm;
    long m_firstsml;
    std::map<int ,PMission> m_misslist;
    cocos2d::Label *m_maintmlab,*m_samllab;
    cocos2d::MenuItemImage *m_popsaml,*m_samlinfo,*m_smlget;
    cocos2d::Sprite *m_samltask,*m_smlico,*m_taskfail;
    //主线
    CC_SYNTHESIZE(int, m_curmissid, CurMissID);
    CC_SYNTHESIZE(int, m_curmisstm, CurMissOveTm);
    //支线
    CC_SYNTHESIZE(int, m_othermissid, OtherMissID);
     CC_SYNTHESIZE(int, m_othermisstm, OtherMisstm);
    cocos2d::Node *m_ui;
    cocos2d::DrawNode *maskLayer;
    static taskMgr* m_pInstance;
    static Mission m_mission[6];
    static int m_saml[5];
	bool init();
    void initdata();
    void ShowWin(int flag);
    void ShowMainUI(PMission miss);
    void GetMissInfo(int missid,PMission mission);
    PMission GetMissCur(int missType);
    std::string GetMissTm(int tm);
    void SaveData();
    taskMgr();
    void popsaml();
    void addSamlMiss();
    void taskComplete(PMission task);
    void tasktimeout(PMission task);
    void taskReward(int rewardType,int RewardNum);
    
    void LoseMission(int MissType);
    void ShowMainTask(PMission task);
    void AddBg(int Flag,PMission miss);
    void ResetMiss(int sType);
    void CloseMissInfo();
    void ShowSml(bool isShow);
    void ShowSmlGet();
    void ShowSmlSample();
};
#endif