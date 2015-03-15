#include "Gold.h"


Gold::Gold(void)
{
	SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("gold01.png");
	mGoldSprite = Sprite::createWithSpriteFrame(tempFrame);
	char pngName[100];
	for (int i=1;i<5;i++)
	{
		sprintf(pngName,"gold%02d.png",i);
		SpriteFrame* tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
		if(tempFrame != NULL)
		{
			m_array.pushBack(tempFrame);
		}		
	}	
	Animation* animation = Animation::createWithSpriteFrames(m_array,0.1f);
	animation->setRestoreOriginalFrame(false);
	Animate* animat = Animate::create(animation);
	mGoldSprite->runAction(RepeatForever::create(animat));  
	this->addChild(mGoldSprite);
}														   


Gold::~Gold(void)
{
}

void Gold::ShowGold(Vec2 spos, Vec3 epos, float tm)
{
	this->setPosition(spos);
	MoveBy* moveAction = MoveBy::create(tm, Vec3(0, 20, 0));
	MoveTo* moveToAction = MoveTo::create(1, epos);
	CallFunc *call = CallFunc::create(std::bind(&Gold::DeleteMe,this));	
	auto *sq= Sequence::create(moveAction,moveToAction,call ,NULL);
	this->runAction(sq);
}

void Gold::DeleteMe()
{
	this->removeFromParent();
	this->autorelease();
}
