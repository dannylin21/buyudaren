#include "FishPlayer.h"
#include "GameScene.h"

USING_NS_CC;

int FishPlayer::m_beziefishtype[3]=
{
    1,2,3
};

int FishPlayer::m_beziefishcount[3] =
{
    5,6,7
};

FishPlayer* FishPlayer::createFishPlayer()
{
	FishPlayer *fishPlayer = FishPlayer::create();
	return fishPlayer;
}

bool FishPlayer::init()
{
	m_GameState = 0;
    m_fishIndex = 0;
    m_baziefcount = 0;
    m_bazieftype = -1;
    m_bornReward = false;
	m_duration = DOORONE_DURTIME;
	if ( !Layer::init() )
    {
        return false;
    }
	m_curType = 1;
	m_curfishnum=0;
	
    m_waveindex = 0;
    return true;
}

void FishPlayer::AddFish(int fishtype,int Count)
{
	int sType = fishtype;
    int index = 0;
	for(int i =0;i<Count; i++)
	{
		if (fishtype == 0)
		{
			int x = rand() % 100+1;
			int step = 0;
			static long lastGoldBeaute = 0;

			if (x == 100)
			{
				if (GameScene::GetTimeNow() - lastGoldBeaute < 180)
				{
					x = 30;
				}
				else
				{
					lastGoldBeaute = GameScene::GetTimeNow();
				}
			}

			if(x == 100)
				sType = 26;//E
			else if(x > 97)
				sType = 22 + rand() % 4;//D
			else if(x > 87)
				sType = 17 + rand() % 5;//C
			else if(x > 75)
				sType = 6 + rand() % 11;//B
			else 
				sType = 1 + rand() % 5;//A
		}
        if(sType < 5)
        {
            if(m_baziefcount == 0 && rand()%100 > 80)
            {
                BornBazie();
            }
            else
            {
                m_curfishnum ++;
                index = GetMaxFishIndex();
                Fish *fish = Fish::createWithFishType(sType);
                fish->setIndex(index);
                G_MainGame->m_pFishes.insert(index, fish);
            }
        }
        else
        {
            m_curfishnum ++;
            index = GetMaxFishIndex();
            Fish *fish = Fish::createWithFishType(sType);
            fish->setIndex(index);
            G_MainGame->m_pFishes.insert(index, fish);
        }
	}
}


void FishPlayer::WavePicStart()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_wavepic = Sprite::create("images/Scene/GameScene/waveCome.png");
    m_wavepic->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 20));
    this->addChild(m_wavepic);
    m_wavepic->setScale(0.3,0.3);
    auto Effects = ScaleTo::create(3,1.2,1.2);
    auto Effects1=FadeOut::create(0.3);
    CallFunc *call = CallFunc::create(std::bind(&FishPlayer::hideWave,this));
    auto seq = Sequence::create(Effects,Effects1,call,NULL);
    m_wavepic->runAction(seq);
}

void FishPlayer::hideWave()
{
    m_wavepic->removeAllChildrenWithCleanup(true);

}

void FishPlayer::NormalBorn()
{
    if(m_duration > 0)
    {
        reset_fish();
        AddFish(0,4);
    }
    else
    {
        m_duration = DOORWAVE_DURTIME;
        m_GameState = 1;
        this->m_waveindex = rand()%18;
        this->m_waveBornEnd = 0;
        this->m_waveEnd = 0;
        m_waveinit = 0;
        WavePicStart();
    }
}

void FishPlayer::WaveBorn()
{
    
}

void FishPlayer::FishTick(float dt)
{
    switch (m_GameState)
    {
        case 0:
            NormalBorn();
            break;
        case 1:
            waveStart(m_duration);
            break;
        default:
            break;
    }
    
}

void FishPlayer::reset_fish()
{
    if(m_duration > 0)
    {
        m_duration--;
    }
}

int FishPlayer::GetMaxFishIndex()
{
    return this->m_fishIndex++;
}

void FishPlayer::fishDead(int FishIndex,int BornType)
{
    G_MainGame->m_pFishes.erase(FishIndex);
    if(m_curfishnum > 0)
    {
        m_curfishnum--;
    }
    if(BornType == NORMALBAZIE)
    {
        DeCreaseBezia();
    }
}

void FishPlayer::start()
{
	AddFish(12,1);
}

void FishPlayer::waveStart(int CountDown)
{
    if(CountDown == DOORWAVE_DURTIME && m_curfishnum == 0)
    {
        reset_fish();
        clearWave();
        PFishPath item = nullptr;
        for(int i = Fish::WaveExe[m_waveindex].startindex;i<Fish::WaveExe[m_waveindex].endIndex;i++)
        {
            item = new FishPath();
            item->m_type = Fish::m_wavePath[i].m_type;
            item->curtm = Fish::m_wavePath[i].curtm;
            item->goType = Fish::m_wavePath[i].goType;
            item->interal = Fish::m_wavePath[i].interal;
            item->num = Fish::m_wavePath[i].num;
            item->delay = Fish::m_wavePath[i].delay;
            item->curtm = 1;
            item->lastborn = 0;
            item->Path =Fish::m_wavePath[i].Path;
            item->pathov =Fish::m_wavePath[i].pathov;
            m_waveData.push_back(item);
            m_waveinit = 1;
        }
    }
    if(m_waveinit == 1)
    {
        reset_fish();
        waveBornFish();
    }
    if(m_waveBornEnd == 1 &&m_curfishnum == 0)
    {
        clearWave();
        m_GameState = 0;
        m_duration = DOORONE_DURTIME;
    }

}

void FishPlayer::clearWave()
{
    for(PFishPath item : m_waveData)
    {
        delete item;
    }
    m_waveData.clear();
}

void FishPlayer::waveBornFish()
{
    bool BornEnd = true;
	for(PFishPath item : m_waveData)
	{
		if(item->num > 0)
		{
            BornEnd = false;
			item->curtm += 1;
			if(item->curtm > item->delay)
			{
				if(item->lastborn == 0)
				{
					item->lastborn = item->interal;
					item->num --;
					Born(item);
				}
				else
				{
					item->lastborn --;
				}
			}
		}
	}
    this->m_waveBornEnd = BornEnd?1:0;
}

void FishPlayer::Born(PFishPath item)
{
    m_curfishnum++;
    int index = GetMaxFishIndex();
	Fish *curfish = Fish::createWithFishtType(item->m_type,item->Path,item->goType,item->pathov,WAVESTATE);
    curfish->setIndex(index);
    G_MainGame->m_pFishes.insert(index, curfish);
}

void FishPlayer::BornBazie()
{
        //1 2 4
    m_bazieftype = rand() % 3+1;
    m_baziefcount = rand()%4+4;
    m_bazieBornNum = m_baziefcount;
    m_baziePath = rand()%6;
    this->schedule(schedule_selector(FishPlayer::BornBazie),0.8);
}

void FishPlayer::BornBazie(float dt)
{
    if(m_bazieBornNum > 0)
    {
        m_bazieBornNum--;
       int index = GetMaxFishIndex();
        m_curfishnum ++;
        Fish *curfish= Fish::createWithFishtType(m_bazieftype,m_baziePath,0,0,NORMALBAZIE);
        curfish->setIndex(index);
        G_MainGame->m_pFishes.insert(index, curfish);
    }
    else if(m_bazieBornNum == 0)
    {
        m_bazieBornNum--;
        this->unschedule(schedule_selector(FishPlayer::BornBazie));
    }
}

void FishPlayer::DeCreaseBezia()
{
    if(m_baziefcount > 0)
    {
        m_baziefcount--;
    }
}
