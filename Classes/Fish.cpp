#include "Fish.h"
#include "FishPlayer.h"
#include "Player.h"
#include "Gold.h"
#include "GameScene.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

fishConf Fish::fishCOnfMap[26]={
	{2,4,4,100,65,30,50},{1,4,4,100,65,30,50},{4,6,8,200,65,60,150},{3,4,8,200,65,65,150},
	{18,5,7,200,65,160,250},{11,4,4,400,65,260,350},{6,6,7,400,65,260,350},{7,4,7,400,65,260,350},
	{5,6,7,400,65,260,350},{15,4,5,400,65,260,350},{17,6,8,400,65,260,350},{9,4,8,400,65,260,350},
	{12,4,8,600,65,360,450},{26,6,8,600,65,360,450},{13,4,8,800,65,460,650},{8,6,8,800,65,460,650},
	{23,5,8,1200,65,660,850},{20,4,7,1200,65,660,850},{22,8,8,1200,65,660,850},{27,6,8,2000,65,1300,2500},
	{25,5,8,2000,65,1300,2500},{28,4,6,2000,65,3500,3500},{29,6,8,2500,65,4500,4500},{31,6,7,3000,65,5500,5500},
	{30,9,15,4000,70,8000,8000},{32,9,15,5000,80,10000,10000}
};



Fish *Fish::createWithFishType(int sIndex,FishPlayer *Player)
{
	Fish* fish = new Fish();
	fish->m_palyer = Player;
	char pngName[50]={0};
	sprintf(pngName,"fish%03d_swim_001.png",Fish::fishCOnfMap[sIndex-1].m_type);
	SpriteFrame* Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
	
	fish->_fishSprite = Sprite::createWithSpriteFrame(Frame);
	fish->addChild(fish->_fishSprite);
	int swimCount = Fish::fishCOnfMap[sIndex-1].m_swim;
	for (int i=1;i<swimCount;i++)
	{
		sprintf(pngName,"fish%03d_swim_%03d.png",Fish::fishCOnfMap[sIndex-1].m_type,i);
		SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
		if(tempFrame != NULL)
		{
			fish->m_array.pushBack(tempFrame);
		}		
	}	
	fish->_fishState = 0;
	fish->setFishIndex(sIndex);
	fish->BornFish(Player);
	return fish;
}

void Fish::BornFish(FishPlayer *gameLayer)
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
	this->m_palyer->addChild(this);
	this->getPath();
}

Fish::~Fish()
{

}



void Fish::getAutoPath()
{
	Size fishSize = _fishSprite->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	Point ptStart, ptEnd;
	float radius = (fishSize.width>fishSize.height?fishSize.width:fishSize.height) / 2;
	switch (rand() % 2) {
	case 0://×ó±ß
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
	/*case 2:
		ptStart.x = rand() % (int)winSize.width;
		ptStart.y = - radius;
		ptEnd.x = rand() % (int)winSize.width;
		ptEnd.y = winSize.height + radius;
		break;
	case 3:
		ptStart.x = rand() % (int)winSize.width;
		ptStart.y = winSize.height + radius;
		ptEnd.x = rand() % (int)winSize.width;
		ptEnd.y = - radius;
		break;*/
	default:
		break;
	}
	float angle = atan2f(ptEnd.y - ptStart.y, ptEnd.x - ptStart.x);
	float rotation = 180.0f - angle * 180.0f / M_PI;
	float duration = rand() % 10 + 4.0f;
	_fishSprite->setPosition(ptStart);
	_fishSprite->setRotation(rotation);
	if(ptEnd.x > ptStart.x)
	{
		_fishSprite->setFlipY(true);
	}
	else
	{
		_fishSprite->setFlipY(false);
	}
	auto *moveto = MoveTo::create(duration, ptEnd);
	CallFunc *call = CallFunc::create(std::bind(&Fish::removeSelf,this));
	auto *sq= Sequence::create(moveto,call,NULL);	
	_fishSprite->runAction(sq);
}

void Fish::getPath()
{
	static int i = 0;
	i ++;
	srand(i);
	if(rand() % 2 == 0)
	{
		this->getAutoPath();
	}
#if 1
	else
	{
		switch(rand() % 7)
		{
		case 0:
			this->movePath(Vec2(1200, 200), Vec2(-500, 700), 0.0f, 20.0f, 15);
			break;
		case 1:
			this->movePath(Vec2(-200, 300), Vec2(1300, 400), 180.0f, 170.0f, 18);
			break;
		case 2:
			this->movePath(Vec2(-200, 300), Vec2(1000, -200), 190.0f, 200.0f, 18);
			break;
		case 3:
			this->movePath(Vec2(1300, 400), Vec2(-200, 300), 10.0f, 5.0f, 18);//Ö±Ïß
			break;
		case 4:
			this->movePath(Vec2(400, -1200), Vec2(600, 1000), 90.0f, 93.0f, 18);
			break;
		case 5:
			this->movePath(Vec2(600, 1000), Vec2(400, -200), -70.0f, -80.0f, 18);
			break;
		case 6:
			this->movePath(Vec2(1200, -400), Vec2(-200, 300), 30.0f, -30.0f, 18);
			break;
		}
	}
#endif
}

void Fish::movePath(Vec2 start,Vec2 endp,float startAngle,float endAngle,int stime)
{
	int time=rand()%10+stime;
	float sx = start.x;
	float sy = start.y;
	float ex = endp.x+rand() %50;
	float ey = endp.y+rand() %150;	
	_fishSprite->setPosition(sx-200+rand()%400,sy-200+rand()%400);	
	CallFunc *call = CallFunc::create(std::bind(&Fish::removeSelf,this));
	_fishSprite->setRotation(startAngle);
	if(fabs(startAngle) > 90 && fabs(startAngle) < 270)
	{
		_fishSprite->setFlipY(true);
	}
	else
	{
		_fishSprite->setFlipY(false);
	}
	float h = _fishSprite->getContentSize().height * 0.5f;
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(sx+100,sy+100);
	bezier.controlPoint_2 = Vec2(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+rand()%300);
	bezier.endPosition = Vec2(endp.x-30,endp.y+h);
	BezierTo *actionMove = BezierTo::create(time,bezier);
	RotateTo *actionRotate = RotateTo::create(time,endAngle);
	auto *action = Spawn::create(actionMove,actionRotate,NULL);		
	auto *sq= Sequence::create(action,call,NULL);		
	_fishSprite->runAction(sq);
}

void Fish::removeSelf()
{
	this->_fishState = 2;
	this->removeFromParent();
	this->m_palyer->fishDead(this);
}

void Fish::showCaught(int DesHp)
{
	CCLOG("kakak:%d",DesHp);
	if(rand()%100 < this->getFishMiss())
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
			gold->ShowGold(_fishSprite->getPosition() + Vec2(-30,0), Vec3(200,-10,0), 0.3);
			gold = new Gold();
			GameScene::m_GameMain->addChild(gold);
			gold->ShowGold(_fishSprite->getPosition() + Vec2(30,0), Vec3(200,-10,0), 0.5);
			AudioEngine::play2d("music/eft_coinanimate.mp3");
			Player::getInstance()->AddGold(this->getFishGold());
			this->_fishState = 3;
			this->_fishSprite->stopAllActions();
			int fishIndex = this->getFishIndex();	
			char pngName[50]={0};
			int swimCount = Fish::fishCOnfMap[fishIndex-1].m_catch;
			Vector<SpriteFrame *> veccatch;
			for (int i=1;i<swimCount;i++)
			{
				sprintf(pngName,"fish%03d_swim_%03d.png",Fish::fishCOnfMap[fishIndex-1].m_type,i);
				SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
				if(tempFrame != NULL)
				{
					veccatch.pushBack(tempFrame);
				}		
			}	
			if(veccatch.size() > 0)
			{
				Animation* animation = Animation::createWithSpriteFrames(veccatch,0.3f);
				animation->setRestoreOriginalFrame(false);
				Animate* animat = Animate::create(animation);
				CallFunc *call = CallFunc::create(std::bind(&Fish::removeSelf,this));		
				auto *sq= Sequence::create(RepeatForever::create(animat),call,NULL);
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