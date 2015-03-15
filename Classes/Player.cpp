#include "Player.h"
#include "TipWin.h"
#include "GameScene.h"

USING_NS_CC;

Player* Player::m_pInstance = nullptr;
int Player::GoldLevel[11]={
	3800,5800,8800,
	12800,19300,27300,
	37300,51300,67300,
	85300,105300
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
Player::Player():m_level(1),m_gold(150),
	m_totalgold(0),m_PopGold(0),m_getReward(0),m_loginGet(false)
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
		m_gold = ts->gold;
		m_totalgold = ts->hadGold;
		m_getReward = ts->GetReward;
		delete ts;
		ts = NULL;
	}
}

Player::~Player()
{
	
}

void Player::AddGold(int Increse)
{
	int newGold = this->getCurGold()+Increse;
	this->setCurGold(newGold);
	this->m_totalgold += Increse;
	for (int i=0;i<sizeof(GoldLevel) / sizeof(GoldLevel[0]);i++)
	{
		if(this->m_totalgold > GoldLevel[i])
		{
			m_level = i+1;
		}
	}
	SavePlayInfo();
	if(m_callBack)
	{
		m_callBack();
	}
	m_PopGold+=Increse;

	if(m_PopGold > 1500)
	{
		m_PopGold = 0;
	//	TipWin::ShowTip(0);
	}
}

void Player::SavePlayInfo()
{
	PPlayInfo ts = new PlayInfo();
	ts->gold = this->m_gold;
	ts->hadGold = this->m_totalgold;
	ts->level = this->m_level;
	ts->GetReward = this->m_getReward;
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
	layer->setPosition(120,visibleSize.height * 0.9f);
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
	m_levelLab->setString(numStr);
	float lv = m_total * curExp/Max;
	return Rect(0,0,lv ,m_exp->getContentSize().height);
}
