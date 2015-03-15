#include "FishPlayer.h"
#include "GameScene.h"

USING_NS_CC;

FishPlayer* FishPlayer::createFishPlayer(GameScene *Scene)
{
	FishPlayer *fishPlayer = FishPlayer::create();
	fishPlayer->m_sence = Scene;
	return fishPlayer;
}

bool FishPlayer::init()
{
	m_GameState = 0;
	m_duration = DOORONE_DURTIME;
	AllDead = false;
	if ( !Layer::init() )
    {
        return false;
    }
	m_curType = 1;
	m_curfishnum=0;
    return true;
}

void FishPlayer::AddFish(int fishtype,int Count)
{
	CCLOG("have:%d",m_sence->m_pFishes.size());
	m_curfishnum += Count;
	int sType = fishtype;
	for(int i =0;i<Count; i++)
	{
		if (fishtype == 0)
		{
			static int k = 0;
			k ++;
			srand(k);
			int x = rand() % 100;
			if(x == 99)
				sType = 26;
			else if(x > 90)
				sType = 22 + rand() % 4;
			else if(x > 70)
				sType = 17 + rand() % 5;
			else if(x > 40)
				sType = 6 + rand() % 11;
			else 
				sType = 1 + rand() % 5;
		}
		Fish *fish = Fish::createWithFishType(sType,this);
		fish->BornFish(this);
		m_sence->m_pFishes.pushBack(fish);
	}
}

void FishPlayer::ChangeState()
{
	if(!AllDead)
	{
		return;
	}
	if(m_GameState == 0)
	{	
		CCLOG("_________*****************___________1");
		m_duration = DOORSEC_DURTIME;
		m_GameState = 1;
	}
	else
	{
		CCLOG("____________________0");
		m_duration = DOORONE_DURTIME;
		m_GameState = 0;
	}
}

void FishPlayer::FishTick(float dt)
{
	if(m_duration == 0)
	{
		ChangeState();
	}
	else
	{
		m_duration--;
		reset_fish();
	}
}

void FishPlayer::reset_fish()
{
	if(m_GameState == 0)
	{
		int EveryTotal = 4;
		for(Fish *fish : m_sence->m_pFishes)
		{
			if(EveryTotal == 0)
			{
				break;
			}
			if(fish->getFishState() == 2)
			{
				fish->BornFish(this);
				m_curfishnum++;
				EveryTotal--;
			}
		}
		if(EveryTotal > 0)
		{
			int fishtype = 1+rand()%(26-1);
			AddFish(0,EveryTotal);
		}
	}
	else
	{
		int EveryTotal = 4;
		for(Fish *fish : m_sence->m_pFishes)
		{
			if(EveryTotal == 0)
			{
				break;
			}
			if(fish->getFishState() == 2)
			{
				fish->BornFish(this);
				m_curfishnum++;
				EveryTotal--;
			}
		}
		if(EveryTotal > 0)
		{
			int fishtype = 1+rand()%(26-1);
			AddFish(0,EveryTotal);
		}
	}
}

void FishPlayer::fishDead(Fish *fish)
{
	m_curfishnum--;
	if(m_curfishnum == 0)
	{
		AllDead = true;
	}
}

void FishPlayer::start()
{
	AddFish(12,4);
}