#include "taskMgr.h"
#include "GameScene.h"
#include "extensions/cocos-ext.h"



USING_NS_CC_EXT;

Mission taskMgr::m_mission[6] =
{
    //任务id，任务类型(0:主线级别任务 1:支线击杀任务) 任务时限 任务状态 任务描述 下个任务  奖励类型 奖励现实图片
    //奖励显示数字图片，奖励数量,附带参数
    {1,0,7200,10,"两小时升级到十级",2,0,"images/Scene/ShopScene/money/coin4.png",
        "images/Number/shop_coin_num.png",20000,0,"",10},
    {2,1,18,5,"在3分钟内捕获5条乌贼",0,7,"images/Scene/GameScene/prop007.png"
    ,"images/Number/shop_coin_num.png",1,0,"taskfish008.png",8},
    {3,1,18,5,"在3分钟内捕获5条灯笼鱼",0,1,"images/Scene/ShopScene/money/coin6.png"
        ,"images/Number/shop_coin_num.png",5000,0,"taskfish022.png",22},
    {4,1,18,20,"在3分钟内捕获20条孔雀鱼",0,1,"images/Scene/ShopScene/money/coin6.png"
        ,"images/Number/shop_coin_num.png",5000,0,"taskfish004.png",4},
    {5,1,18,20,"在3分钟内捕获20条小丑鱼",0,1,"images/Scene/ShopScene/money/coin6.png"
        ,"images/Number/shop_coin_num.png",5000,0,"taskfish006.png",6},
    {6,1,3,3,"在5分钟内捕获3条魔鬼鱼",0,7,"images/Scene/GameScene/prop007.png"
        ,"images/Number/shop_coin_num.png",1,0,"taskfish025.png",25}
    
};

int taskMgr::m_saml[5] =
{
  2,3,4,5,6
};

taskMgr* taskMgr::m_pInstance = nullptr;
taskMgr* taskMgr::getInstance()
{
    if(m_pInstance == nullptr)
	{
		m_pInstance =  new taskMgr();
        if(m_pInstance && m_pInstance->init())
        {
            m_pInstance->autorelease();
            G_MainGame->m_UILayer->addChild(m_pInstance);
        }
        else
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
	}
	return m_pInstance;
}

taskMgr::~taskMgr()
{
    m_pInstance = nullptr;
}

taskMgr::taskMgr()
{

}

void taskMgr::GetReward()
{
}

void taskMgr::GetMissInfo(int missid,PMission mission)
{
    for(Mission item : m_mission)
    {
        if(item.missionid == missid)
        {
            mission->missionid = item.missionid;
            mission->missiontm = item.missiontm;
            mission->nextmissid = item.nextmissid;
            mission->missdes = item.missdes;
            mission->numpic = item.numpic;
            mission->rewardnum=item.rewardnum;
            mission->RewardPic=item.RewardPic;
            mission->rewardType = item.rewardType;
            mission->nextmissid = item.nextmissid;
            mission->missNeed = item.missNeed;
            mission->missState = 0;
            mission->missType = item.missType;
            mission->ico = item.ico;
            mission->missCondit = item.missCondit;
            break;
        }
    }
    mission->missionid = 0;
}

void taskMgr::initdata()
{
    m_firstsml = 0;
    PTask task=new Task();
    task->mainID=0;
    FileOperation::ReadTask(task);
    PMission MainMiss = new Mission();
    if(task->mainID == 0)
    {
        GetMissInfo(1,MainMiss);
        m_misslist.insert(make_pair(0,MainMiss));
    }
    else
    {
        GetMissInfo(task->mainID,MainMiss);
        MainMiss->missiontm = task->MainTm;
        MainMiss->missState = task->MainState;
        MainMiss->missType = 0;//主线
        m_misslist.insert(make_pair(0,MainMiss));
    }
    if(task->SamlID != 0)
    {
        PMission SamlMiss = new Mission();
        GetMissInfo(task->SamlID,SamlMiss);
        SamlMiss->missiontm = task->SamlTm;
        SamlMiss->missState = task->SamlState;
        SamlMiss->missType = 1;//支线
        m_misslist.insert(make_pair(1,MainMiss));
    }
    delete task;
    task = nullptr;
}

PMission taskMgr::GetMissCur(int missType)
{
    auto it = m_misslist.find(missType);
    if(it == m_misslist.end())
    {
        return nullptr;
    }
    else
    {
        return it->second;
    }
}

std::string taskMgr::GetMissTm(int curtm)
{
    string msec = StringUtils::format("%.2d:%.2d:%.2d",curtm/3600, (curtm-(curtm/3600*3600))/60, curtm-(curtm/3600*3600)-(curtm-(curtm/3600*3600))/60*60);
    return msec;
}

void taskMgr::SaveData()
{
    PTask task=new Task();
    for (auto item : m_misslist)
    {
        if(item.second->missType == 0)
        {
            task->mainID = item.second->missionid;
            task->MainState = item.second->missState;
            task->MainTm = item.second->missiontm;
        }
        else
        {
            task->SamlID = item.second->missionid;
            task->SamlState = item.second->missState;
            task->SamlTm = item.second->missiontm;
        }
    }
    FileOperation::SaveTask(task);
}

void taskMgr::Tick()
{
    savetm++;
    bool havesaml = false;
    for(auto item : m_misslist)
    {
        if(item.second->missiontm > 0 && item.second->missState != 999999)
        {
            if(item.second->missType == 0)//主线
            {
                if(item.second->missState < item.second->missNeed) //进行中
                {
                    item.second->missiontm -= 1;
                    string sec = GetMissTm(item.second->missiontm);
                    m_maintmlab->setString(sec);
                }
            }
            else
            {
                //支线
                if(item.second->missState < item.second->missNeed) //进行中
                {
                    havesaml = true;
                    item.second->missiontm -= 1;
                    string strDes = StringUtils::format("%d/%d\n",item.second->missState,item.second->missNeed);
                    string sec = strDes + GetMissTm(item.second->missiontm);
                    m_samllab->setString(sec);
                }
                else
                {
                    havesaml = (item.second->missState == 888888||item.second->missState == item.second->missNeed);
                }
            }   
        }
        else if(item.second->missState != 999999)
        {
            tasktimeout(item.second);
        }
    }
    if(!havesaml)
    {
        long now = GameScene::GetTimeNow();
        long tm;
        if(m_firstsml == 0)
        {
            tm = Player::getInstance()->getLoginTime();
            if(now - tm > 5)
            {
                popsaml();
            }
        }
        else
        {
            if(now - m_firstsml > 3)
            {
                popsaml();
            }
        }
    }
    
    if(savetm%5 == 0)
    {
        SaveData();
    }
}

void taskMgr::tasktimeout(PMission task)
{
    if(task->missType == 1)
    {
       m_firstsml = GameScene::GetTimeNow(); 
    }
    task->missState = 999999;
    LoseMission(task->missType);
}

void taskMgr::popsaml()
{
    static bool bFirst = true;
    ShowSmlGet();
    if(bFirst)
    {
        auto tips = Sprite::create("images/Scene/OptionalGuide/dialog_left.png");
        auto lab = Label::createWithSystemFont("点击可查看更多任务内容", "Arial",18);
        tips->addChild(lab);
        lab->setPosition(150,40);
        lab->setColor(Color3B(253,248,170));
        tips->setPosition(325, 413);
        this->addChild(tips);
        tips->setOpacity(0);
        lab->setOpacity(0);
        auto seq = Sequence::create(MoveBy::create(2, Vec3(0, 0, 0)), CallFunc::create([=]{
            tips->setOpacity(255);
            lab->setOpacity(255);
        }),nullptr);
        tips->runAction(seq);
        m_popsaml->runAction(Sequence::create(MoveBy::create(1, Vec2(200, 0)), CallFunc::create([=]{
            m_popsaml->activate();
            ShowWin(1);
            tips->runAction(Sequence::create(MoveBy::create(5, Vec3(0, 0, 0)), CallFunc::create([=]{
                tips->removeFromParentAndCleanup(true);
            }), NULL));
        }), NULL));
        
        m_samltask->runAction(Sequence::create(MoveBy::create(0, Vec2(-200, 0)), MoveBy::create(1, Vec2(200,0)), NULL));
        m_samlinfo->runAction(Sequence::create(MoveBy::create(0, Vec2(-200, 0)), MoveBy::create(1, Vec2(200,0)), NULL));
        bFirst = false;
    }
    else
    {
        m_popsaml->runAction(MoveBy::create(1, Vec2(200, 0)));
        m_samltask->runAction(Sequence::create(MoveBy::create(0, Vec2(-200, 0)), MoveBy::create(1, Vec2(200,0)), NULL));
        m_samlinfo->runAction(Sequence::create(MoveBy::create(0, Vec2(-200, 0)), MoveBy::create(1, Vec2(200,0)), NULL));
    }
}

void taskMgr::ShowSmlGet()
{
    int id = rand() % 5;
    int samlID = m_saml[id];
    PMission SamlMiss = new Mission();
    GetMissInfo(samlID,SamlMiss);
    m_misslist.erase(1);
    SamlMiss->missState = 888888;//未接
    m_misslist.insert(make_pair(1,SamlMiss));
    m_samlinfo->setVisible(true);
    m_samlinfo->setEnabled(false);
    m_samltask->setVisible(true);
}

void taskMgr::ShowSmlSample()
{
    m_popsaml->setPosition(-200,100);
    ShowSml(true);
    PMission SamlMiss = GetMissCur(1);
    SamlMiss->missState=0;
    string strDes = StringUtils::format("%d/%d",SamlMiss->missState,SamlMiss->missNeed);
    string sec = strDes +"\n"+ GetMissTm(SamlMiss->missiontm);
    m_samllab->setString(sec);
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(SamlMiss->ico);
    m_smlico->setSpriteFrame(frame);
    
}

void taskMgr::addSamlMiss()
{
	
}
/*
 behavoir   什么行为
 behParam   附加参数
 0:升级
 1:击杀
 */
void taskMgr::Hook(int behavior,int behParam)
{
    PMission item = GetMissCur(behavior);
    if(item == nullptr)
    {
        return;
    }
    if(behavior == 0)
    {
        if(behParam >=item->missCondit)
        {
            item->missState=item->missNeed;
            taskComplete(item);
        }
    }
    else if(item&&item->missState < item->missNeed&&item->missCondit == behParam&&item->missiontm > 0)
    {
        item->missState += 1;
        if(item->missState == item->missNeed)
        {
            taskComplete(item);
        }
    }
}

void taskMgr::taskComplete(PMission task)
{
    if(task->missType == 0)
    {
        m_maintmlab->setString("点击领取");
    }
    else
    {
        m_firstsml = GameScene::GetTimeNow(); 
        ShowSml(false);
        m_smlget->setVisible(true);
    }
}

void taskMgr::ShowSml(bool isShow)
{
    if(!isShow)
    {
        m_samlinfo->setVisible(!isShow);
        m_samltask->setVisible(!isShow);
    }
    else
    {
        m_samlinfo->setVisible(isShow);
        m_samltask->setVisible(isShow);
    }
    m_samlinfo->setEnabled(true);
    m_samllab->setVisible(isShow);
    
    m_smlico->setVisible(isShow);
}

bool taskMgr::init()
{
    m_openSaml=false;
    m_openMain = false;
    initdata();
    PMission MainTask = GetMissCur(0);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_MainTaskICO = MenuItemImage::create("images/Scene/TaskScene/task_rookie_bg.png","images/Scene/TaskScene/task_rookie_bg.png",[&](Ref* Sender){
        ShowWin(0);
	
	 });
    m_samlinfo =MenuItemImage::create("images/Scene/TaskScene/task_bg.png","",[&](Ref* Sender){
        ShowWin(1);
    });
    
    m_popsaml =MenuItemImage::create("images/Scene/TaskScene/word_new.png","",[&](Ref* Sender){
        ShowSmlSample();
    });
    
    m_smlget = MenuItemImage::create("images/Scene/TaskScene/word_success.png","",[&](Ref* Sender){
        ShowWin(1);
    });
    
    
    
    m_samltask = Sprite::create("images/Scene/TaskScene/task_light.png");
    this->addChild(m_samltask);
    m_samltask->setPosition(100,450);
    m_samltask->setVisible(false);
	m_samltask->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL)));
    m_smlico = Sprite::create();
    this->addChild(m_smlico,10);
    m_smlico->setVisible(false);
    m_smlico->setPosition(50,460);
    
    Vec2 Pos(100,350);
    auto Menu = Menu::create(m_MainTaskICO,m_samlinfo,m_popsaml,m_smlget,nullptr);
    this->addChild(Menu);
    Menu->setPosition(Pos);
    m_samlinfo->setPosition(0,100);
    m_popsaml->setPosition(-200,100);
    m_smlget->setPosition(0,100);
    
    m_smlget->setVisible(false);
    m_samlinfo->setVisible(false);
    
    m_samllab = Label::create("", "Arial", 20);
    this->addChild(m_samllab);
    m_samllab->setPosition(120,450);
    m_samllab->setVisible(false);
    
    m_MainTaskICO->setVisible(false);
    
    if(MainTask->missState != 999999)
    {
        m_MainTaskICO->setVisible(true);
        m_MainTaskLab = LabelAtlas::create("20000","images/Number/shop_coin_num.png",22,28,'0');
        this->addChild(m_MainTaskLab,1);
        m_MainTaskLab->setPosition(Vec2(80,320));
        m_maintmlab = Label::create("", "Arial", 24);
        this->addChild(m_maintmlab);
        m_maintmlab->setPosition(100,305);
        float r = 60;

        
        m_Partic=ParticleSystemQuad::create("particles/taskAward.plist");
        m_Partic->setPositionType(ParticleSystem::PositionType::FREE);
        m_Partic->setAutoRemoveOnFinish(true);
        this->addChild(m_Partic,1000);
        auto array2 = PointArray::create(360);
        
        for(int i = 0; i < 360; ++i)
        {
            Vec2 l(0,r);
            l.rotate(Vec2(0,0), i * 10);
            array2->addControlPoint(Pos + l);
        }
        auto action = CatmullRomTo::create(240, array2);
        m_Partic->setPosition(Pos);
        
        m_Partic->runAction(RepeatForever::create(action));
        
        m_taskfail = Sprite::create("images/Scene/TaskScene/word_fail.png");
        this->addChild(m_taskfail);
        m_taskfail->setPosition(100,450);
        m_taskfail->setVisible(false);
    }
    
	return true;
}

void taskMgr::LoseMission(int MissType)
{
    
    if(MissType == 0)
    {
        m_Partic->removeFromParentAndCleanup(true);
        auto scla = ScaleTo::create(0.3f,0,0);
        m_MainTaskICO->runAction(scla);
        m_maintmlab->setVisible(false);
        m_MainTaskLab->setVisible(false);
    }
    else
    {
        ShowSml(false);
        m_taskfail->setVisible(true);
        auto fun = CallFunc::create([=]{
            m_samlinfo->setVisible(false);
            m_samltask->setVisible(false);
			m_taskfail->setVisible(false);
        });
        m_taskfail->runAction(Sequence::create(MoveBy::create(5, Vec3(0, 0, 0)),fun,nullptr));

    }
}

void taskMgr::ShowWin(int flag)
{
    PMission item = GetMissCur(flag);
    if(item->missState == 999999)
    {
        return;
    }
    switch(flag)
    {
        case 0:
            ShowMainTask(item);
            break;
        case 1:
            ShowMainUI(item);
            break;
    }
}


Sprite* t = NULL;
void taskMgr::ShowMainUI(PMission miss)
{
    if(m_openMain||m_openSaml)
    {
        return;
    }
    m_openSaml = true;
	maskLayer = DrawNode::create();
	maskLayer->drawSolidRect(Vec2(-7000, -7000), Vec2(7000, 7000), Color4F(0, 0, 0, 0.6));
	G_MainGame->m_UILayer->addChild(maskLayer, 99);

    AddBg(1,miss);
    auto btnClose = MenuItemImage::create("ccb/ccbResources/common/close.png","ccb/ccbResources/common/close.png",[=](Ref* Sender){
		BUBBLE;
        this->CloseMissInfo();
	});
    Menu *menu;
    Sprite *getBtnPic=Sprite::create();
    Sprite *resetBtnPic = Sprite::create();
    MenuItemImage *m_btn,*m_btn2;
    if(miss->missState != miss->missNeed)
    {
        //no com
        m_btn =MenuItemImage::create("ccb/ccbResources/common/lButton_down.png","",[=](Ref* Sender){

        });
        m_btn2 = MenuItemImage::create("ccb/ccbResources/common/lButton_up.png","",[&](Ref* Sender){
            //sdk
            //reset
            ResetMiss(1);
            this->CloseMissInfo();
            
        });
        resetBtnPic->setTexture("images/Word/task_reset.png");
        getBtnPic->setTexture("images/Word/get_award_gray.png");
    }
    else
    {
        //ok
        m_btn =MenuItemImage::create("ccb/ccbResources/common/lButton_up.png","",[=](Ref* Sender){
            taskReward(miss->rewardType,miss->rewardnum);
            miss->missState = 999999;
            m_smlget->setVisible(false);
            m_samlinfo->setVisible(false);
            m_samltask->setVisible(false);
            CloseMissInfo();
        });
        m_btn2 = MenuItemImage::create("ccb/ccbResources/common/lButton_up.png","",[&](Ref* Sender){
            //sdk double get
        });
        resetBtnPic->setTexture("images/Word/double_get.png");
        getBtnPic->setTexture("images/Word/get_award.png");
    }
    menu=Menu::create(btnClose,m_btn,m_btn2,nullptr);
    m_ui->addChild(menu);
    m_ui->addChild(getBtnPic);
    menu->setPosition(0,0);
    
    m_ui->addChild(resetBtnPic,1);
    resetBtnPic->setPosition(100,-150);
    getBtnPic->setPosition(-100,-150);
    
    btnClose->setPosition(Vec2(210, 180));
    m_btn->setPosition(Vec2(-100, -150));
    m_btn2->setPosition(Vec2(100, -150));
    
    auto rmb = LabelTTF::create("仅需2元", "Arial", 17);
    rmb->setColor(Color3B(140, 71, 25));
    rmb->setOpacity(255);
    rmb->setPosition(96, -112);
    m_ui->addChild(rmb, 10001);
}


void taskMgr::taskReward(int rewardType,int RewardNum)
{
    switch (rewardType) {
        case 1:
            Player::getInstance()->AddGold(RewardNum);
            break;
        case 7:
            GameScene::m_GameMain->m_thrCan->addPropNum(1);
            break;
        default:
            break;
    }
}

void taskMgr::ShowMainTask(PMission task)
{
    if(m_openMain||m_openSaml)
    {
        return;
    }
    m_openMain = true;
    maskLayer = DrawNode::create();
    maskLayer->drawSolidRect(Vec2(-7000, -7000), Vec2(7000, 7000), Color4F(0, 0, 0, 0.6));
    G_MainGame->m_UILayer->addChild(maskLayer, 99);
    AddBg(0,task);

    auto btnClose = MenuItemImage::create("ccb/ccbResources/common/close.png","ccb/ccbResources/common/close.png",[&](Ref* Sender){
		BUBBLE;
		this->CloseMissInfo();
	});
    Menu *menu;
    MenuItemImage *m_btn;
    Sprite* getBtnPic=Sprite::create();
    if(task->missState != task->missNeed)
    {
        // no com
        m_btn = MenuItemImage::create("ccb/ccbResources/common/lButton_down.png","",[&](Ref* Sender){
        });
        getBtnPic->setTexture("images/Word/get_award_gray.png");
    }
    else
    {
        m_btn = MenuItemImage::create("ccb/ccbResources/common/lButton_up.png","",[=](Ref* Sender){
            LoseMission(0);
            if(task->rewardType == 0)
            {
                Player::getInstance()->AddGold(task->rewardnum);
            }
            task->missState = 999999;
            this->CloseMissInfo();
        });
        getBtnPic->setTexture("images/Word/get_award.png");
    }
    menu = Menu::create(btnClose,m_btn,nullptr);
    m_ui->addChild(menu);
    m_ui->addChild(getBtnPic);
    menu->setPosition(0,0);
    btnClose->setPosition(Vec2(210, 180));
    m_btn->setPosition(Vec2(0, -150));
    getBtnPic->setPosition(Vec2(0, -150));
    
    
}

void taskMgr::AddBg(int Flag,PMission miss)
{
	m_ui = Node::create();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto bg = Scale9Sprite::create("ccb/ccbResources/common/9Box.png");
    m_ui->addChild(bg);
    bg->setContentSize(Size(500,400));
    Sprite *title;
    if(Flag == 0)
    {
        title = Sprite::create("images/Word/task_rookie.png");
    }
    else
    {
        title = Sprite::create("images/Word/task.png");
    }
    title->setPosition(0,130);
    m_ui->addChild(title,1);
    
    auto m_cont = Sprite::create("images/Word/task_content.png");
    m_ui->addChild(m_cont);
    m_cont->setPosition(-150,70);
    auto m_rewad = Sprite::create("images/Word/task_award.png");
    m_ui->addChild(m_rewad);
    m_rewad->setPosition(-150,-10);
    
    auto label = Label::create(miss->missdes, "Arial", 24);
    m_ui->addChild(label);
    label->setPosition(-70,60);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    auto reward = Sprite::create(miss->RewardPic);
	auto shadow = Sprite::create("images/Scene/ShopScene/shadow.png");
    m_ui->addChild(reward,2);
	m_ui->addChild(shadow, 1);
	shadow->setPosition(-7, -70);
    reward->setPosition(-10,-30);
    auto labNum = LabelAtlas::create(StringUtils::format("%d",miss->rewardnum),miss->numpic,22,28,'0');
    m_ui->addChild(labNum,2);
    labNum->setPosition(-10,-70);
    
    auto plashbg = Sprite::create("images/Scene/TaskScene/award_light.png");
	 plashbg->setPosition(-10,-30);
    auto fad = FadeOut::create(2);
    auto fadin = fad->reverse();
    auto seq = Sequence::create(fad,fadin, NULL);
	 plashbg->runAction(RepeatForever::create(seq));
    m_ui->addChild(plashbg,1);
	m_ui->setAnchorPoint(Vec2(0.5, 0.5));
	G_MainGame->m_UILayer->addChild(m_ui,100);
	m_ui->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_ui->runAction(Sequence::create(CallFunc::create([=]{m_ui->setScale(0.4); })
		, ScaleTo::create(0.2, 1.2, 1.2, 1)
		, ScaleTo::create(0.1, 1, 1, 1)
		, NULL));
}

void taskMgr::ResetMiss(int sType)
{
    ShowSmlGet();
    ShowSmlSample();
}

void taskMgr::CloseMissInfo()
{
    if(m_openMain)
    {
        m_openMain = false;
    }
    if(m_openSaml)
    {
        m_openSaml = false;
    }
    maskLayer->removeFromParentAndCleanup(true);
    m_ui->removeFromParentAndCleanup(true);
}
