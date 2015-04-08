#include "Player.h"
#include "TipWin.h"
#include "GameScene.h"
#include "taskMgr.h"
#include "LoadScene.h"

USING_NS_CC;

Player* Player::m_pInstance = nullptr;
int Player::GoldLevel[11]={
	3800,5800,8800,
	17800,29300,45300,
	60300,80300,100300,
	155300,205300
};

Player* Player::getInstance()
{
	if(m_pInstance == nullptr)
	{	
		m_pInstance =  new Player();
		m_pInstance->Init();
		return m_pInstance;
	}
	return m_pInstance;
}
Player::Player():m_level(1),m_gold(8000),m_canone(5),m_cansec(5),m_canthr(5),m_mainmissid(1),m_mainmisstm(1000),	m_totalgold(0),m_PopfreeGold(0),m_getReward(0),m_loginGet(false),m_poprmb(0),m_othermissid(0),m_luonum(0)
{
	
}

void Player::Init()
{
	std::string sFilePath = FileOperation::GetFilePath()+"/play.dat";
	if (FileUtils::getInstance()->isFileExist(sFilePath))
	{
		PPlayInfo ts = new PlayInfo();
		FileOperation::ReadPlayInfo(sFilePath,ts);
		m_level = ts->level;
        m_gold = ts->gold < 1000?1000:ts->gold;
		m_totalgold = ts->hadGold;
		m_getReward = ts->GetReward;
		m_canone = ts->CanOne;
		m_cansec = ts->CanSec;
		m_canthr = ts->CanThr;
        m_luonum = ts->m_luonum;
		delete ts;
		ts = NULL;
	}
}

Player::~Player()
{
	
}

void Player::decreaseGold(int decrease)
{
	int newGold = this->getCurGold()-decrease;
	this->setCurGold(newGold);
    if(newGold < 500)
    {
        G_MainGame->ShowBuyMoney(true);
    }
	G_MainGame->m_bottomgold->setString(StringUtils::format("%d",newGold));
}

void Player::AddGold(int Increse)
{
	AddGold(Increse,0);
}

//addType 0:额外获得 1:捕获获得
void Player::AddGold(int Increse,int AddType)
{
	int newGold = this->getCurGold()+Increse;
	this->setCurGold(newGold);
	this->m_totalgold += Increse;
	for (int i=0;i<sizeof(GoldLevel) / sizeof(GoldLevel[0]);i++)
	{
		if(this->m_totalgold > GoldLevel[i])
		{
			m_level = i+1;
            if(G_MainGame != nullptr)
            {
                taskMgr::getInstance()->Hook(0, m_level);
            }
		}
	}
	SavePlayInfo();
	if(m_callBack)
	{
		m_callBack();
	}
	if(AddType == 1)
	{
		m_PopfreeGold+=Increse;
		m_poprmb += Increse;

		if(m_PopfreeGold > 1500)
		{
			m_PopfreeGold = 0;
			TipWin::ShowTip(0);
		}
		if(m_poprmb > 5500)
		{
			m_poprmb = 0;
			TipWin::ShowTip(1);
		}
	}
    if(G_MainGame)
    {
        G_MainGame->m_bottomgold->setString(StringUtils::format("%d",newGold));
        
        if(G_MainGame->m_ShowBuyMoney && newGold >= 500)
        {
            G_MainGame->ShowBuyMoney(false);
        }
    }
    if(LoadScene::m_loadScene)
    {
        LoadScene::m_loadScene->labelatlas->setString(StringUtils::format("%d",newGold));
    }
}

void Player::SavePlayInfo()
{
	PPlayInfo ts = new PlayInfo();
	ts->gold = this->m_gold;
	ts->hadGold = this->m_totalgold;
	ts->level = this->m_level;
	ts->GetReward = this->m_getReward;
	ts->CanOne = this->m_canone;
	ts->CanSec = this->m_cansec;
	ts->CanThr = this->m_canthr;
    ts->m_mainmissid = this->m_mainmissid;
    ts->m_mainmissiontm = this->m_mainmisstm;
    ts->m_luonum = this->m_luonum;
    ts->m_smallmisstime = this->m_othermisstm;
	FileOperation::SaveRoleInfo(ts);
	delete ts;
	ts = nullptr;
}


void PlayerExp::init(Layer *GameScene)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/Plist/head/head.plist");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto layer = Layer::create();	
	GameScene::m_GameMain->m_UILayer->addChild(layer);
	layer->setPosition(120,visibleSize.height-10);
	auto head = Sprite::create("images/Scene/GameScene/headbg.png");
	layer->addChild(head);
	m_levelLab = LabelAtlas::create("1","images/Number/num_gold.png",14,22,'0');
	m_levelLab->setPosition(-90,-10);
	layer->addChild(m_levelLab);
	m_title = Sprite::create();
	layer->addChild(m_title,2);
	m_title->setPosition(10,0);
	m_exp = Sprite::create("images/Scene/GameScene/exp_progress.png");
	m_total = m_exp->getContentSize().width;
	m_exp->setAnchorPoint(Vec2(0.0f,0.5f));
	Rect srec = GetExpDis();
	m_exp->setTextureRect(srec);
	layer->addChild(m_exp);
	m_exp->setPosition(-55,0);	
	Player::getInstance()->m_callBack = std::bind(&PlayerExp::ChangeExp,this);
}

void PlayerExp::ChangeExp()
{
	Rect srec = GetExpDis();
	m_exp->setTextureRect(srec);
}


Rect PlayerExp::GetExpDis()
{
	int curExp = Player::getInstance()->getTotalGold();
	int Levels =  Player::getInstance()->getCLevel();
	int Max = Player::GoldLevel[Levels];
	string numStr = StringUtils::format("%i", Levels);
	if(Levels == 0)
	{
		Levels = 1;
	}
	string FrameName = StringUtils::format("head%03d.png", Levels);
	SpriteFrame* Frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(FrameName.c_str());
	m_title->setSpriteFrame(Frame1);

	string lvStr = m_levelLab->getString();
	if (lvStr.compare(numStr) != 0 && lvStr.compare("1") != 0)
	{
		//ShowExpTip(9999);
	}

	m_levelLab->setString(numStr);
	float lv = m_total * curExp/Max;
	return Rect(0,0,lv ,m_exp->getContentSize().height);
}
