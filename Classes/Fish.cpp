#include "Fish.h"
#include "FishPlayer.h"
#include "Player.h"
#include "Gold.h"
#include "GameScene.h"
#include "audio/include/AudioEngine.h"
#include "taskMgr.h"
#include "luopan.h"
using namespace cocos2d::experimental;
USING_NS_CC;

fishConf Fish::fishCOnfMap[26]={
    {2 ,4,4 ,100 ,65,30   ,50   },
    {1 ,4,4 ,100 ,65,30   ,50   },
    {4 ,6,8 ,200 ,65,60   ,150  },
    {3 ,4,8 ,200 ,65,65   ,150  },
    {18,5,7 ,200 ,65,160  ,250  },
    {11,4,4 ,200 ,65,160  ,250  },
    {6 ,6,7 ,400 ,65,260  ,350  },
    {7 ,4,7 ,400 ,65,260  ,350  },
    {5 ,6,7 ,400 ,65,260  ,350  },
    {15,4,5 ,400 ,65,260  ,350  },
    {17,6,8 ,500 ,65,260  ,350  },
    {9 ,4,8 ,500 ,65,260  ,350  },
    {12,4,8 ,500 ,75,260  ,350  },
    {26,6,8 ,700 ,75,360  ,450  },
    {13,4,8 ,700 ,75,360  ,450  },
    {8 ,6,8 ,1000 ,75,460  ,650  },
    {23,5,8 ,1000,75,460  ,650  },
    {20,4,7 ,1400,75,660  ,850  },
    {22,8,8 ,1400,75,660  ,850  },
    {27,6,8 ,1400,80,1300 ,2500 },
    {25,5,8 ,2500,80,1300 ,2500 },
    {28,4,6 ,2500,80,3500 ,3500 },
    {29,6,8 ,3800,80,4500 ,4500 },
    {31,6,7 ,5000,80,5500 ,5500 },
    {30,9,15,6000,80,8000 ,8000 },
    {32,9,15,7000,90,10000,10000}
};
//｛鱼编号，鱼数量，游动路径（下面数组索引），直线还是转弯(1直线)，出鱼间隔，当前时间(0)，延迟秒数，最后出生时间(0)}
FishPath Fish::m_wavePath[110]={
    //阵型1
    {2,20,0,1,0,0,0,0},
    {10,20,1,1,0,0,1,0},
    {23,6,2,1,2,0,3,0},
    {10,20,3,1,0,0,1,0},
    {2,20,4,1,0,0,0,0},
   
   //阵型2
    {8,18,0,1,0,0,0,0},
    {20,6,1,1,2,0,2,0},
    {25,5,2,1,2,0,3,0},
    {20,6,3,1,2,0,2,0},
    {8,18,4,1,0,0,0,0},
    
    //阵型3
    {3,19,0,1,0,0,0,0},
    {15,19,1,1,0,0,0,0},
    {21,9,2,1,1,0,2,0},
    {15,19,3,1,0,0,0,0},
    {3,19,4,1,0,0,0,0},
    
    //阵型4
    {9,16,0,1,0,0,0,0},
    {19,16,1,1,0,0,0,0},
    {22,5,2,1,2,0,2,0},
    {19,16,3,1,0,0,0,0},
    {9,16,4,1,0,0,0,0},
    
    //阵型5
    {2,20,0,1,0,0,0,0},
    {4,20,1,1,0,0,0,0},
    {25,5,2,1,3,0,2,0},
    {4,20,3,1,0,0,0,0},
    {2,20,4,1,0,0,0,0},
    //阵型6
	{6,20,0,1,0,0,0,0},
	{14,20,1,1,0,0,0,0},
    {24,5,2,1,3,0,3,0},
	{14,20,3,1,0,0,0,0},
	{6,20,4,1,0,0,0,0},
    
    //阵型7
    {2,20,5,1,0,0,0,0},
    {10,20,6,1,0,0,1,0},
    {23,6,7,1,2,0,3,0},
    {10,20,8,1,0,0,1,0},
    {2,20,9,1,0,0,0,0},
    
    //阵型8
    {8,18,5,1,0,0,0,0},
    {20,6,6,1,2,0,2,0},
    {25,5,7,1,2,0,3,0},
    {20,6,8,1,2,0,2,0},
    {8,18,9,1,0,0,0,0},
    
    //阵型9
    {3,19,5,1,0,0,0,0},
    {15,19,6,1,0,0,0,0},
    {21,9,7,1,1,0,2,0},
    {15,19,8,1,0,0,0,0},
    {3,19,9,1,0,0,0,0},
    
    //阵型10
    {9,16,5,1,0,0,0,0},
    {19,16,6,1,0,0,0,0},
    {22,5,7,1,2,0,2,0},
    {19,16,8,1,0,0,0,0},
    {9,16,9,1,0,0,0,0},
    
    //阵型11
    {2,20,5,1,0,0,0,0},
    {4,20,6,1,0,0,0,0},
    {25,5,7,1,3,0,2,0},
    {4,20,8,1,0,0,0,0},
    {2,20,9,1,0,0,0,0},
    //阵型12
	{6,20,5,1,0,0,0,0},
	{14,20,6,1,0,0,0,0},
    {24,5,7,1,3,0,3,0},
	{14,20,8,1,0,0,0,0},
	{6,20,9,1,0,0,0,0},
    
    //阵型13
    {2,20,10,1,0,0,0,0},
    {10,20,11,1,0,0,1,0},
    {23,6,12,1,2,0,3,0},
    {10,20,13,1,0,0,1,0},
    {2,20,14,1,0,0,0,0},
    
    //阵型14
    {8,18,10,1,0,0,0,0},
    {20,6,11,1,2,0,2,0},
    {25,5,12,1,2,0,3,0},
    {20,6,13,1,2,0,2,0},
    {8,18,14,1,0,0,0,0},
    
    //阵型15
    {3,19,10,1,0,0,0,0},
    {15,19,11,1,0,0,0,0},
    {21,9,12,1,1,0,2,0},
    {15,19,13,1,0,0,0,0},
    {3,19,14,1,0,0,0,0},
    
    //阵型16
    {9,16,10,1,0,0,0,0},
    {19,16,11,1,0,0,0,0},
    {22,5,12,1,2,0,2,0},
    {19,16,13,1,0,0,0,0},
    {9,16,14,1,0,0,0,0},
    
    //阵型17
    {2,20,10,1,0,0,0,0},
    {4,20,11,1,0,0,0,0},
    {25,5,12,1,3,0,2,0},
    {4,20,13,1,0,0,0,0},
    {2,20,14,1,0,0,0,0},
    //阵型18
	{6,20,10,1,0,0,0,0},
	{14,20,11,1,0,0,0,0},
    {24,5,12,1,3,0,3,0},
	{14,20,13,1,0,0,0,0},
	{6,20,14,1,0,0,0,0},
    //阵型19
    {6,20,15,1,0,0,0,0},
	{14,20,16,1,0,0,0,0},
    {24,5,17,1,3,0,3,0},
	{14,20,18,1,0,0,0,0},
	{6,20,19,1,0,0,0,0},
    
    {6,20,5,1,0,0,0,0,1},
	{14,20,6,1,0,0,0,0,1},
    {24,5,7,1,3,0,3,0,1},
	{14,20,8,1,0,0,0,0,1},
	{6,20,9,1,0,0,0,0,1},
    //阵型20
    {6,20,15,1,0,0,0,0,1},
	{14,20,16,1,0,0,0,0,1},
    {24,5,17,1,3,0,3,0,1},
	{14,20,18,1,0,0,0,0,1},
	{6,20,19,1,0,0,0,0,1},
    
    {6,20,5,1,0,0,0,0,0},
	{14,20,6,1,0,0,0,0,0},
    {24,5,7,1,3,0,3,0,0},
	{14,20,8,1,0,0,0,0,0},
	{6,20,9,1,0,0,0,0,0},
    
	

};

//路径索引（从0开始）
SetPath Fish::PathArray[20] = {
	{Vec2(1440.,480.),Vec2(-480.,480.)},
    {Vec2(1440.,400.),Vec2(-480.,400.)},
	{Vec2(1440.,330.),Vec2(-480.,330.)},
	{Vec2(1440.,200.),Vec2(-480.,200.)},
	{Vec2(1440.,120.),Vec2(-480.,120.)},
    
    {Vec2(-475.,282.),Vec2(1110.,957.)},
    {Vec2(-475.,193.),Vec2(1224.,957.)},
    {Vec2(-475.,66.),Vec2(1435.,931.)},
    {Vec2(-475.,-62),Vec2(1435.,766.)},
    {Vec2(-475.,-139.),Vec2(1435.,702.)},
    
    {Vec2(1110.,957.),Vec2(-475.,282.)},
    {Vec2(1224.,957.),Vec2(-475.,193.)},
    {Vec2(1435.,931.),Vec2(-475.,66.)},
    {Vec2(1435.,766.),Vec2(-475.,-62)},
    {Vec2(1435.,702.),Vec2(-475.,-139.)},
    
    {Vec2(-150,957.),Vec2(1435.,282.)},
    {Vec2(-264.,957.),Vec2(1435.,193.)},
    {Vec2(-475.,928.),Vec2(1435.,66.)},
    {Vec2(-475.,766.),Vec2(1435.,-62)},
    {Vec2(-475.,702.),Vec2(1435.,-139.)}

};

//潮汐方案，目前两套，第一套选取m_wavePath中的0-－－5个配置，第二套用5到10，前半闭区间
WaveExemple Fish::WaveExe[20] = {
    {0,5},{5,10},{10,15},{15,20},{20,25},{25,30},
    {30,35},{35,40},{40,45},{45,50},{50,55},{55,60},
    {60,65},{65,70},{70,75},{75,80},{80,85},{85,90},{90,100},{100,110}
};

//偶然的曲线运动鱼
BezierPath Fish::m_beziePath[6] = {
    {Vec2(1115,-8),Vec2(88,765),Vec2(115,-8),Vec2(88,-84),0,90,18},
    {Vec2(88,765),Vec2(1115,-8),Vec2(88,-84),Vec2(1115,-8),-90.,-180,18},
    {Vec2(-175,364),Vec2(1137,291),Vec2(6,-248),Vec2(893,872),-195,-180,18},
    {Vec2(1137,291),Vec2(-175,364),Vec2(893,872),Vec2(6,-248),-15,0,18},
    {Vec2(-17,404),Vec2(811,-60),Vec2(-174,404),Vec2(686,387),140,270,18},
    {Vec2(811,-122),Vec2(-174,404),Vec2(686,387),Vec2(-174,404),70,-10,18}
};


Fish *Fish::createWithFishType(int sIndex)
{
	Fish* fish = new Fish();
	fish->createFish(sIndex);
	fish->setBornType(NORMALSTATE);
	fish->BornFish();
	return fish;
}

extern float offsetx, offsety;

void Fish::createFish(int sType)
{
    //sType = 7;
    m_rewardtype = ExTNone;
    m_childReward = 0;
	char pngName[50]={0};
	sprintf(pngName,"fish%03d_swim_001.png",Fish::fishCOnfMap[sType-1].m_type);
	SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
	
	this->_fishSprite = Sprite::createWithSpriteFrame(Frame);
	this->addChild(this->_fishSprite);
	int swimCount = Fish::fishCOnfMap[sType-1].m_swim;
	for (int i=1;i<swimCount;i++)
	{
		sprintf(pngName,"fish%03d_swim_%03d.png",Fish::fishCOnfMap[sType-1].m_type,i);
		SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
		if(tempFrame != NULL)
		{
			this->m_array.pushBack(tempFrame);
		}		
	}	
	m_pRewardNode = Node::create();
	this->_fishSprite->addChild(m_pRewardNode, 200);
	this->_fishState = 0;
	m_pRewardNode->setPosition(54,73);
	this->setFishIndex(sType);
}

Fish* Fish::createWithFishtType(int sType,int PathIndex,int GoType,int pathov,int BornType)
{
	Fish* fish = new Fish();
	fish->createFish(sType);
	fish->setBornType(BornType);
    fish->setPathIndex(PathIndex);
    fish->setPathov(pathov);

	fish->setGoType(GoType);
	fish->BornFish();
	return fish;
}

void Fish::BornFish()
{
	switch (this->_fishState)
	{
	case 0:
	case 2:
		Resetborn();
		break;
	default:
		break;
	}
}

void Fish::Resetborn()
{
    if(!G_MainGame)
    {
        return;
    }
    m_rewardtype = ExTNone;
	m_pRewardNode->removeAllChildren();
	this->_fishState = 1;
	int Golds = 0;
	if(fishCOnfMap[m_fishIndex-1].m_mingold != fishCOnfMap[m_fishIndex-1].m_maxgold)
	{
		Golds = fishCOnfMap[m_fishIndex-1].m_mingold+rand()%(fishCOnfMap[m_fishIndex-1].m_maxgold-fishCOnfMap[m_fishIndex-1].m_mingold);
	}
	else
	{
		Golds = fishCOnfMap[m_fishIndex-1].m_mingold;
	}
	this->setFishGold(Golds);
	this->setHp(fishCOnfMap[m_fishIndex-1].m_hp);
	this->setFishMiss(fishCOnfMap[m_fishIndex-1].m_miss);
	Animation* animation = Animation::createWithSpriteFrames(m_array,0.1f);
	animation->setRestoreOriginalFrame(false);
	Animate* animat = Animate::create(animation);
	this->_fishSprite->runAction(RepeatForever::create(animat));
	G_MainGame->getFishLayer()->addChild(this);
 

#if 0
	auto b = DrawNode::create();
	_fishSprite->removeChildByTag(1234);
	b->setTag(1234);
	auto bd = _fishSprite->getBoundingBox();
	bd.origin = Vec2(0,0);
	b->drawRect(Vec2(bd.getMinX(), bd.getMinY()), Vec2(bd.getMinX(), bd.getMaxY()),Vec2(bd.getMaxX(), bd.getMaxY()),Vec2(bd.getMaxX(), bd.getMinY()), Color4F(1,0,0,1));
	_fishSprite->addChild(b);
	b->setPosition(0,0);
#endif
    if(fishCOnfMap[m_fishIndex-1].m_type == 6)
    {
        if(rand()%100 < 50)
        {
            m_rewardtype =EXLUOPAN;
        }
        //罗盘
    }
    else if (fishCOnfMap[m_fishIndex-1].m_type == 12)
    {
        //炸弹
        if(rand()%100 < 50)
        {
            m_rewardtype =ExTBomb;
        }
    }
    else if (fishCOnfMap[m_fishIndex-1].m_type == 25 || fishCOnfMap[m_fishIndex-1].m_type == 29 || fishCOnfMap[m_fishIndex-1].m_type == 31 || fishCOnfMap[m_fishIndex-1].m_type == 28)
    {
        //奖励特殊炮
        if(rand()%100 < 10 && !G_MainGame->getFishLayer()->m_bornReward)
        {
            G_MainGame->getFishLayer()->m_bornReward = true;
            m_rewardtype =EXREWARD;
        }
    }
    AddExReward(m_rewardtype);
  

	if(this->m_bornType == WAVESTATE)
	{
		if(this->m_goType == 1)
		{
            CCLOG("hhhh:%f___%f___%d",PathArray[m_PathIndex].pStart.x,PathArray[m_PathIndex].pStart.y,m_pathov);
            if(m_pathov == 0)
            {
                GoDirPath(PathArray[m_PathIndex].pStart,PathArray[m_PathIndex].pEnd);
            }
            else
            {
                GoDirPath(PathArray[m_PathIndex].pEnd,PathArray[m_PathIndex].pStart);
            }
		}
	}
	else if(this->m_bornType == NORMALBAZIE)
	{
		this->getPath(this->m_PathIndex);
	}
    else
    {
        this->getPath(-1);
    }
}

void Fish::TestPath()
{
	GoDirPath(Vec2(0,0),Vec2(500,500));
}

void Fish::GoDirPath(cocos2d::Vec2 ptStart,cocos2d::Vec2 ptEnd)
{
	float angle = atan2f(ptEnd.y - ptStart.y, ptEnd.x - ptStart.x);
	float rotation = 180.0f - angle * 180.0f / M_PI;
	float duration = rand() % 10 + 4.0f;
	if(m_bornType == WAVESTATE)
	{
		duration = 14.f;
	}
	_fishSprite->setPosition(ptStart);
	_fishSprite->setRotation(rotation);
	ReCheckAllPosition();

	// 乌龟的动作
	if(getFishIndex() == 17)
	{
		auto getTm = []{
			struct timeval tim;
			gettimeofday(&tim, NULL);
			return tim.tv_usec * 1000;
		};
		int totalAction = 3;
		long lastTm = getTm();
		float perDuration = duration / totalAction;
		Vec2 n = (ptEnd - ptStart);
		float perMoveLen = n.length() / totalAction;
		n.normalize();
		Animation* animation = Animation::createWithSpriteFrames(m_array,0.1f);
		animation->setRestoreOriginalFrame(false);
		Animate* animat = Animate::create(animation);
		_fishSprite->stopAllActions();
		_fishSprite->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.7, n * (perMoveLen / 10)), MoveBy::create(perDuration, n * perMoveLen), NULL)));
		CallFunc *call = CallFunc::create([=]{this->removeSelf();});
		_fishSprite->runAction(RepeatForever::create(Sequence::create(animat, MoveBy::create(perDuration, Vec2(0,0)), NULL)));
        auto *moveto = MoveBy::create(duration + 2, Vec2(0,0));
        auto *sq= Sequence::create(moveto,call,NULL);
        _fishSprite->runAction(sq);
	}
	else
	{
		auto *moveto = MoveTo::create(duration, ptEnd);
		CallFunc *call = CallFunc::create(std::bind(&Fish::removeSelf,this));
		auto *sq= Sequence::create(moveto,call,NULL);	
		_fishSprite->runAction(sq);
	}

	
}

Fish::~Fish()
{

}

void Fish::getAutoPath()
{
	Size fishSize = _fishSprite->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 ptStart, ptEnd;
	float radius = (fishSize.width>fishSize.height?fishSize.width:fishSize.height) / 2;
    
	switch (rand() % 2) {
	case 0://
		ptStart.x = - radius;
		ptStart.y = rand() % (int)winSize.height;
		ptEnd.x = winSize.width + radius;
		ptEnd.y = rand() % (int)winSize.height;
		break;
	case 1:
		ptStart.x = winSize.width + radius;
		ptStart.y = rand() % (int)winSize.height;
		ptEnd.x = - radius;
		ptEnd.y = rand() % (int)winSize.height;
		break;
	default:
		break;
	}
	GoDirPath(ptStart,ptEnd);
}

void Fish::getPath(int PathIndex/*=-1*/)
{
    if(PathIndex == -1)
    {
        this->getAutoPath();
    }
    else
    {
        BezierPath item = m_beziePath[PathIndex];
        GoBezierPath(item.start, item.endp, item.stcntrl, item.endcntrl, item.startangle, item.endangle, item.times);
    }
    
}

void Fish::ReCheckAllPosition()
{
 	float d = _fishSprite->getRotation();

	if(fabs(d) >= 90 && fabs(d) < 270)
	{
		_fishSprite->setFlipY(true);
		m_pRewardNode->setRotation(180);
		switch (m_eRewardType)
		{
		case ExTBomb:
			{
				m_pRewardNode->setPosition(50, -13);
			}break;
		case ExTRocket:
			{
				m_pRewardNode->setPosition(-31,-9);
				((Sprite*)m_pRewardNode->getChildByName("bubble"))->setFlippedX(true);
			}
                break;
            case EXLUOPAN:
                m_pRewardNode->setPosition(-31,-9);
                ((Sprite*)m_pRewardNode->getChildByName("reward"))->setFlippedX(true);
                break;
            case EXREWARD:
            {
                Vec2 pos;
                switch (fishCOnfMap[m_fishIndex-1].m_type) {
                    case 29:
                        pos =Vec2(-30,120);
                        break;
                    case 28:
                        pos =Vec2(-30,30);
                        break;
                    case 25:
                        pos =Vec2(-30,70);
                        break;
                    case 31:
                        pos =Vec2(-30,50);
                        break;
                }
                m_pRewardNode->setPosition(pos);
                ((Sprite*)m_pRewardNode->getChildByName("reward"))->setFlippedX(true);
            }
                break;
		default:
			break;
		}
	}
	else
	{
		_fishSprite->setFlipY(false);
		m_pRewardNode->setRotation(0);

		switch (m_eRewardType)
		{
		case ExTBomb:
			{
				m_pRewardNode->setPosition(54,73);
			}break;
		case ExTRocket:
			{
				m_pRewardNode->setPosition(-14,74);
				((Sprite*)m_pRewardNode->getChildByName("bubble"))->setFlippedX(false);
			}
                break;
            case EXLUOPAN:
                m_pRewardNode->setPosition(-31,60);
                ((Sprite*)m_pRewardNode->getChildByName("reward"))->setFlippedX(false);
                break;
            case EXREWARD:
            {
                Vec2 pos;
                switch (fishCOnfMap[m_fishIndex-1].m_type) {
                    case 29:
                        pos = Vec2(-20,90);
                        break;
                    case 28:
                        pos = Vec2(-20,100);
                        break;
                    case 25:
                        pos = Vec2(-20,160);
                        break;
                    case 31:
                        pos = Vec2(-20,140);
                        break;
                }
                m_pRewardNode->setPosition(pos);
                ((Sprite*)m_pRewardNode->getChildByName("reward"))->setFlippedX(false);
            }
                break;
		default:
			break;
		}
	}
}

void Fish::GoBezierPath(Vec2 start,Vec2 endp,Vec2 cntr1,Vec2 cntr2,float startAngle,float endAngle,int stime)
{
    _fishSprite->setPosition(start);
	CallFunc *call = CallFunc::create(std::bind(&Fish::removeSelf,this));
	_fishSprite->setRotation(startAngle);
	ReCheckAllPosition();
	//float h = _fishSprite->getContentSize().height * 0.5f;
	ccBezierConfig bezier;
    bezier.controlPoint_1 = cntr1;
    bezier.controlPoint_2 = cntr2;
	bezier.endPosition = endp;
	BezierTo *actionMove = BezierTo::create(stime,bezier);
	RotateTo *actionRotate = RotateTo::create(stime,endAngle);
	auto *action = Spawn::create(actionMove,actionRotate,NULL);		
	auto *sq= Sequence::create(action,call,NULL);		
	_fishSprite->runAction(sq);
}

void Fish::removeSelf()
{
    if(this->_fishState == 3)
    {
        Player::getInstance()->AddGold(this->getFishGold(),1);
        taskMgr::getInstance()->Hook(1,Fish::fishCOnfMap[this->getFishIndex()-1].m_type);
        switch (m_rewardtype) {
            case EXLUOPAN:
                CLuoPan::ShowLuoPan();                
                break;
            case EXREWARD:
                GiveReward();
                break;
            default:
                break;
        }
    }
    if(m_rewardtype == EXREWARD)
    {
       G_MainGame->getFishLayer()->m_bornReward = false;
    }
    G_MainGame->getFishLayer()->fishDead(this->getIndex(),this->m_bornType);
   
	this->removeFromParentAndCleanup(true);
	
}

void Fish::AddExReward(ExRewardType t)
{
	m_pRewardNode->removeAllChildren();
	m_pRewardNode->stopAllActions();
	m_eRewardType = t;
	switch (t)
	{
	case ExTBomb:
		{
			auto bombSprite = Sprite::create("images/Scene/GameScene/fishbomb_bomb.png");
			auto bombCircleSprite = Sprite::create("images/Scene/GameScene/fishbomb_bomblight.png");
			auto bombRopeSprite = Sprite::create("images/Scene/GameScene/fishbomb_rope.png");
			auto ttt3=ParticleSystemQuad::create("particles/fish_bomb.plist");
			ttt3->setPositionType(ParticleSystem::PositionType::FREE);
			ttt3->setAutoRemoveOnFinish(true);
			m_pRewardNode->addChild(bombRopeSprite, 1);
			m_pRewardNode->addChild(bombSprite,2);
			m_pRewardNode->addChild(bombCircleSprite, 3);
			m_pRewardNode->addChild(ttt3, 4);
			bombRopeSprite->setPosition(-1, -39);
			ttt3->setPosition(22,33);

			auto scaleAction = ScaleTo::create(1.4, 1.3,1.3);
			auto scaleR = ScaleTo::create(0.001, 1,1);
			auto fdout = FadeOut::create(1.1);
			auto fdin = FadeIn::create(0.301);
			bombCircleSprite->setOpacity(0);
			bombCircleSprite->runAction(RepeatForever::create(Sequence::create(scaleAction, scaleR, NULL)));
			bombCircleSprite->runAction(RepeatForever::create(Sequence::create(fdin, fdout, NULL)));

			auto scaleAction2 = ScaleTo::create(0.3, 1.1,1.1);
			auto scaleR2 = ScaleTo::create(0.1, 1,1);
			auto mv = MoveBy::create(1.001, Vec3(0,0,0.01));
			bombSprite->runAction(RepeatForever::create(Sequence::create(scaleAction2,scaleR2, mv, NULL)));

		}break;
	case ExTDown:
		{
			
		}break;
	case ExTLight:
		{

		}break;
	case ExTRocket:
		{
			auto bubble = Sprite::create("images/Scene/GameScene/bubble.png");
			auto bullet = Sprite::create("images/Bullets/bullet013.png");
			bullet->setScale(0.3);
			bubble->setScale(0.6);
			bubble->setName("bubble");
			m_pRewardNode->addChild(bubble, 3);
			m_pRewardNode->addChild(bullet, 2);

			auto scaleA = ScaleTo::create(1, 1.2,1.2);
			auto scaleR = ScaleTo::create(0.4, 1, 1);
			m_pRewardNode->runAction(RepeatForever::create(Sequence::create(scaleA,scaleR, NULL)));
		}break;
    case EXLUOPAN:
        initBubble(0);
        break;
    case EXREWARD:
        initBubble(1);
        break;
	default:
		break;
	}
}

void Fish::initBubble(int flag)
{
    auto bubble = Sprite::create("images/Scene/GameScene/bubble.png");
    bubble->setScale(0.8, 0.8);
    auto scaleA = ScaleTo::create(1, 0.6,0.6);
    auto scaleR = ScaleTo::create(0.4, 1, 1);
    Sprite* gifsprie;
    if(flag == 0)
    {
        gifsprie = Sprite::create("images/Scene/GameScene/btnLottery_down.png");
        gifsprie->setScale(0.8, 0.8);
    }
    else if(flag == 1)
    {
        if(rand()%2 == 0)
        {
            m_childReward = 1;
            gifsprie = Sprite::create("images/Scene/GameScene/prop006.png");
        }
        else
        {
            m_childReward = 2;
            gifsprie = Sprite::create("images/Scene/GameScene/prop007.png");
        }
        gifsprie->setScale(0.5, 0.5);
    }
    
    m_pRewardNode->addChild(gifsprie, 3);
    m_pRewardNode->addChild(bubble, 2);
    bubble->setName("reward");
    m_pRewardNode->runAction(RepeatForever::create(Sequence::create(scaleA,scaleR, NULL)));
    auto bd = _fishSprite->getBoundingBox();
    m_pRewardNode->setPosition(Vec2(bd.getMaxX()-35,150));
}


void Fish::showCaught(int DesHp)
{
	CCLOG("kakak:%d",DesHp);
	if(rand()%100 < this->getFishMiss() || DesHp >= 10000)
	{
		if(DesHp < this->getHp())
		{
			this->setHp(this->getHp()-DesHp);
			return;
		}
		else
		{
			this->setHp(0);
			Gold* gold = new Gold();
			GameScene::m_GameMain->addChild(gold);
			gold->ShowGold(_fishSprite->getPosition() + Vec2(-30,0), Vec2(200,-10), 0.3);
			gold = new Gold();
			GameScene::m_GameMain->addChild(gold);
			gold->ShowGold(_fishSprite->getPosition() + Vec2(30,0), Vec2(200,-10), 0.5);
			PlayMusic("music/eft_coinanimate.mp3");			
			this->_fishState = 3;
			this->_fishSprite->stopAllActions();
			int fishIndex = this->getFishIndex();	
			char pngName[50]={0};
			int swimCount = Fish::fishCOnfMap[fishIndex-1].m_catch;

			{
				auto lGold = LabelAtlas::create(StringUtils::format("%d", this->getFishGold()), "images/Number/showup_gold.png", 36, 47, '0');
				G_MainGame->addChild(lGold, 1000);
				lGold->setPosition(this->convertToWorldSpace(_fishSprite->getPosition()));
				auto delay = MoveBy::create(1, Vec3(0,0,1));
				auto removeF = CallFunc::create([lGold]{lGold->removeFromParent();});
				lGold->runAction(Sequence::create(delay, removeF, NULL));
				auto mv = MoveBy::create(0.5, Vec3(0,0,1));
				auto fadout = FadeOut::create(0.5);
				lGold->runAction(Sequence::create(mv, fadout, NULL));
				lGold->runAction(MoveBy::create(1, Vec3(0,15,0)));
			}
			
			G_MainGame->currentGoldGet += getFishGold();
			G_MainGame->goldTipTotal += getFishGold();
			if (G_MainGame->m_pCannon->getCanType() < 7)
			{
				if (G_MainGame->goldTipTotal > 2500)
				{
					GameScene::ShowGoldTip(G_MainGame->goldTipTotal);
					G_MainGame->goldTipTotal = 0;
				}
				G_MainGame->SetProgress(G_MainGame->currentGoldGet / 200);
			}

			if (m_rewardtype == ExTBomb)
			{
				m_pRewardNode->removeAllChildren();
				G_MainGame->BombFishExplored(this->convertToWorldSpace(this->getFishSprite()->getPosition()));
			}

			

			Vector<SpriteFrame *> veccatch;
			for (int i=1;i<swimCount;i++)
			{
				sprintf(pngName,"fish%03d_catch_%03d.png",Fish::fishCOnfMap[fishIndex-1].m_type,i);
				SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
				if(tempFrame != NULL)
				{
					veccatch.pushBack(tempFrame);
				}		
			}	
			if(veccatch.size() > 0)
			{
				Animation* animation = Animation::createWithSpriteFrames(veccatch,0.3f);
				animation->setRestoreOriginalFrame(true);
				Animate* animat = Animate::create(animation);
				CallFunc *call = CallFunc::create(std::bind(&Fish::removeSelf,this));		
				auto fadeOut = FadeOut::create(1.5f);
				auto mv = MoveBy::create(1.5, Vec2(0, 15));
				auto *sq= Sequence::create(mv,call,NULL);
				this->_fishSprite->runAction(RepeatForever::create(animat));
				this->_fishSprite->runAction(fadeOut);
				this->_fishSprite->runAction(sq);
			}
			else
			{
				this->removeSelf();
			}
		}
	}
	else
	{
		CCLOG("fish miss");
	}
	
}


Vec2 Fish::GetPos()
{

	return Vec2(0.f,0.f);
}

void Fish::ShowLighting()
{
	Vector<SpriteFrame *> LightList;
	char sName[40]={0};
	SpriteFrame* tempFrame=nullptr;
	for(int i = 1;i<4;i++)
	{
		sprintf(sName,"Lightning_launch%03d.png",i);
		tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sName);
		LightList.pushBack(tempFrame);
	}
	Animation* animation = Animation::createWithSpriteFrames(LightList,0.3f);
	animation->setRestoreOriginalFrame(true);
	Animate* animat = Animate::create(animation);
	this->_fishSprite->runAction(RepeatForever::create(animat));
}

void Fish::GiveReward()
{
    m_fly = Node::create();
    Sprite *prop;
    if(m_childReward == 1)
    {
       prop = Sprite::create("images/Scene/GameScene/prop006.png");
    }
    else
    {
       prop = Sprite::create("images/Scene/GameScene/prop007.png");
    }
	auto titleSp = Sprite::create("images/Scene/TipScene/itemGet/get_title.png");
	titleSp->setPosition(5, 121);
	m_fly->addChild(titleSp,3);
    auto bg = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
	bg->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1,1.4), ScaleTo::create(1,0.8), NULL)));
    m_fly->addChild(prop,2);
    m_fly->addChild(bg);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    G_MainGame->m_UILayer->addChild(m_fly);
    m_fly->setPosition(visibleSize.width / 2,visibleSize.height/2);
    m_fly->setScale(0.1f,0.1f);
    auto ac2 = ScaleTo::create(0.2f,0.8f,0.8f);
    auto sc1 = ScaleTo::create(2.8, 0.8, 0.8);
    CallFunc *call = CallFunc::create(std::bind(&Fish::RewardLose,this,0));
	m_fly->runAction(Sequence::create(ac2, sc1, CallFunc::create([=]{titleSp->removeFromParent(); }), call, nullptr));
    
}

void Fish::RewardLose(int flag)
{
    if(flag == 0)
    {
        auto sc = ScaleTo::create(0.3, 0.4, 0.4, 0.1);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        auto ac3 = MoveTo::create(1.f,Vec2(visibleSize.width / 2,0));
		CallFunc *call = CallFunc::create([=]{
			m_fly->removeFromParentAndCleanup(true);
			if (m_childReward == 1)
			{
				G_MainGame->m_pCannon->ChangeType(8);
			}
			else
			{
				G_MainGame->m_pCannon->ChangeType(9);
			}
		});
        auto seq = Sequence::create(ac3,call,nullptr);
        m_fly->runAction(sc);
        m_fly->runAction(seq);
    }
}

